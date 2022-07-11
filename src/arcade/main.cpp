#include <arcade/Cabinet.h>

std::shared_ptr<cobebe::Core> App;

#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#include <emscripten/html5.h>

EM_BOOL one_iter(double time, void* userData)
{
	App->run();

	return EM_TRUE;
}
#endif

int main()
{
	App = cobebe::Core::initialise();
	printf("Initialise me\n");
	{
		std::shared_ptr<cobebe::Entity> entity = App->addEntity();
		App->getLighting()->addPointLight(glm::vec3(5, 2, -5), glm::vec3(1.0f), 12.0f);
		App->getLighting()->setGlobalLightAmbient(glm::vec3(0.5f));

		std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<CabRender>();
		renderer->setGltfMesh("gltf\\cabinet.gltf");
		renderer->setShader("deferred_shaders\\renderGCab.shad");

		entity = App->addEntity();
		entity->getTransform()->m_position = glm::vec3(0.0f, -1.0f, -5.0f);
		entity->addComponent<Cabinet>();

	}

#if defined(__EMSCRIPTEN__)
	emscripten_request_animation_frame_loop(one_iter, 0);
#else
	App->run();
#endif

	return 0;
}