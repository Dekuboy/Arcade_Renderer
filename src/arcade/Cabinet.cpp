#include <arcade/Cabinet.h>

void Cabinet::rotateHorizontal(float _angle)
{
	if (_angle)
	{
		m_camAngle.x += _angle;
		m_camAngle.x = ClampAngle(m_camAngle.x, -360, 360);
		m_xRotation = glm::mat3(glm::rotate(glm::quat(), m_camAngle.x, glm::vec3(0, 1, 0)));
	}

	m_rotationMatrix = m_xRotation;
}

void Cabinet::rotateVertical(float _angle)
{
	if (_angle)
	{
		m_camAngle.y += _angle;
		m_camAngle.y = ClampAngle(m_camAngle.y, -90, 90);
		m_yRotation = glm::mat3(glm::rotate(glm::quat(), m_camAngle.y, glm::vec3(1, 0, 0)));
	}

	m_rotationMatrix *= m_yRotation;
}

float Cabinet::ClampAngle(float _angle, float _min, float _max)
{
	if (_angle > glm::radians(360.0f))
	{
		_angle -= glm::radians(360.0f);
	}
	if (_angle < glm::radians(-360.0f))
	{
		_angle += glm::radians(360.0f);
	}
	return glm::clamp(_angle, glm::radians(_min), glm::radians(_max));
}

void Cabinet::onInit()
{
	m_camAngle = glm::vec2(0);
	m_camera = getCore()->getCurrentCamera();
	//m_fxaa = getCore()->loadAsset<cobebe::Shader>("shaders\\fxaa.shad");
	//m_fxaa->getInternal()->setViewport(glm::vec4(0, 0,
	//	getCore()->getEnvironment()->getWidth(), getCore()->getEnvironment()->getHeight()));
}

void Cabinet::onTick()
{
	getCore()->getCanvas()->queryButton();
	glm::vec2 camMovement = glm::radians(-0.16f * getMouse()->getMovement());
#ifdef __EMSCRIPTEN__
	camMovement = glm::vec2(0);
#endif

	float moveX = 0, moveY = 0;
	if (getKeyboard()->isKey(cobebeInput::iKey))
	{
		moveY += 1;
	}
	if (getKeyboard()->isKey(cobebeInput::jKey))
	{
		moveX += 1;
	}
	if (getKeyboard()->isKey(cobebeInput::kKey))
	{
		moveY -= 1;
	}
	if (getKeyboard()->isKey(cobebeInput::lKey))
	{
		moveX -= 1;
	}
	if (camMovement.x || camMovement.y || moveX || moveY)
	{
		rotateHorizontal(camMovement.x + glm::radians(moveX));
		rotateVertical(camMovement.y + glm::radians(moveY));

		m_camera.lock()->m_rotation = m_rotationMatrix;
	}

	if (getKeyboard()->isKey(cobebeInput::wKey))
	{
		glm::vec3 z = m_camera.lock()->m_rotation[2];
		m_camera.lock()->m_position += -z;
	}
	if (getKeyboard()->isKey(cobebeInput::aKey))
	{
		glm::vec3 x = m_camera.lock()->m_rotation[0];
		m_camera.lock()->m_position += -x;
	}
	if (getKeyboard()->isKey(cobebeInput::sKey))
	{
		glm::vec3 z = m_camera.lock()->m_rotation[2];
		m_camera.lock()->m_position += z;
	}
	if (getKeyboard()->isKey(cobebeInput::dKey))
	{
		glm::vec3 x = m_camera.lock()->m_rotation[0];
		m_camera.lock()->m_position += x;
	}

	//getEntity()->getComponent<cobebe::ObjAnimationController>()->incrementAnimations(6.0 * getEnvironment()->getDeltaTime());
}

void Cabinet::onPostDisplay()
{
	//m_camera.lock()->setRtUniform("in_Texture", m_fxaa->getInternal());
	//m_fxaa->getInternal()->setUniform("in_FrameBufSize", glm::vec2((float)getEnvironment()->getWidth(), (float)getEnvironment()->getHeight()));
	//m_fxaa->getInternal()->draw();
}

void CabRender::onDisplay()
{
	if (m_shader && !m_setUniforms)
	{
		m_shader->getInternal()->setTextureUniformsType<glwrap::PBRUniforms>();
		m_setUniforms = true;
	}
	Renderer::onDisplay();
}