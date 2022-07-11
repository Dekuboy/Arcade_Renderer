#include <cobebe/Cobebe.h>

class Cabinet : public cobebe::Component
{
public:

private:
	glm::vec2 m_camAngle;
	glm::mat3 m_rotationMatrix;
	glm::mat3 m_xRotation;
	glm::mat3 m_yRotation;
	std::weak_ptr<cobebe::Camera> m_camera;
	std::shared_ptr<cobebe::Shader> m_fxaa;

	void rotateHorizontal(float _angle);
	void rotateVertical(float _angle);
	float ClampAngle(float _angle, float _min, float _max);

	void onInit();
	void onTick();
	void onPostDisplay();

};

class CabRender : public cobebe::Renderer
{
public:


private:
	bool m_setUniforms = false;
	void onDisplay();
};