#include "Camera.h"
Camera::Camera(const Elite::FPoint4& pos)
	: m_Position{ pos }
	, m_Fov{ CalculateFOV() }
	, m_YAngle{}
	, m_XAngle{}
	, m_Forward{ 0.f,0.f,1.f }
	, m_TransMat{ m_TransMat.Identity() }
	, m_RotMatX{ m_RotMatX.Identity() }
	, m_RotMatY{ m_RotMatY.Identity() }
{
	CalculateTranslation();
	CalculateXRotationMatrix();
	CalculateYRotationMatrix();
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{

	//Translation with keyboard
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_W])
	{
		MoveForward(deltaTime);
	}
	else if (pStates[SDL_SCANCODE_S])
	{
		MoveBackward(deltaTime);
	}

	if (pStates[SDL_SCANCODE_E])
	{
		MoveUp(deltaTime);
	}
	else if (pStates[SDL_SCANCODE_Q])
	{
		MoveDown(deltaTime);
	}

	if (pStates[SDL_SCANCODE_A])
	{
		MoveLeft(deltaTime);
	}
	else if (pStates[SDL_SCANCODE_D])
	{
		MoveRight(deltaTime);
	}

	//Rotation with mouse
	Uint32 mouseState=SDL_GetRelativeMouseState(&m_MousePos.x, &m_MousePos.y);

	if (mouseState & SDL_BUTTON_LMASK && mouseState & SDL_BUTTON_RMASK)
	{
		if (m_MousePos.y < 0)
		{
			MoveUp(deltaTime);
		}
		else if (m_MousePos.y > 0)
		{
			MoveDown(deltaTime);
		}
	}
	else if (mouseState & SDL_BUTTON_RMASK)
	{
		if (m_MousePos.x != 0)
		{
			Rotate(deltaTime);
			CalculateYRotationMatrix();
		}
		if (m_MousePos.y != 0)
		{
			Rotate(deltaTime);
			CalculateXRotationMatrix();
		}
	}
	//forward and backward translation with mouse
	else if (mouseState & SDL_BUTTON_LMASK)
	{
		if (m_MousePos.y < 0)
		{
			MoveForward(deltaTime);
		}
		else if (m_MousePos.y > 0)
		{
			MoveBackward(deltaTime);
		}
	}
	
}

float Camera::CalculateFOV(float degrees)const
{
	const float rad = Elite::ToRadians(degrees);
	return tanf(rad / 2);
}

float Camera::GetFOV() const
{
	return m_Fov;
}

void Camera::CalculateTranslation()
{
	const Elite::FVector3 worldUp{ 0.f,1.f,0.f };
	const Elite::FVector3 right{ Elite::GetNormalized(Elite::Cross(worldUp,m_Forward)) };
	const Elite::FVector3 up{ Elite::GetNormalized(Elite::Cross(m_Forward,right)) };
	m_TransMat[0] = Elite::FVector4{ right.x,right.y,right.z,0.f };
	m_TransMat[1] = Elite::FVector4{ up.x,up.y,up.z,0.f };
	m_TransMat[2] = Elite::FVector4{ m_Forward.x,m_Forward.y,m_Forward.z,0.f };
	m_TransMat[3] = Elite::FVector4{ m_Position.x,m_Position.y,m_Position.z,1.f };
}

Elite::FMatrix4 Camera::GetTranslation() const
{
	return m_TransMat;
}

void Camera::CalculateXRotationMatrix()
{
	m_RotMatX = Elite::MakeRotation(m_XAngle, Elite::FVector3(m_TransMat[0]));
	m_Forward = (m_RotMatX * Elite::FVector4(m_Forward)).xyz;
	m_XAngle = 0;
}
void Camera::CalculateYRotationMatrix()
{
	m_RotMatY = Elite::MakeRotation(m_YAngle, Elite::FVector3(m_TransMat[1]));
	m_Forward = (m_RotMatY * Elite::FVector4(m_Forward)).xyz;
	m_YAngle = 0;
}

Elite::FMatrix4 Camera::GetYRotationMatrix() const
{
	return m_RotMatY;
}
Elite::FMatrix4 Camera::GetXRotationMatrix() const
{
	return m_RotMatX;
}
Elite::FMatrix4 Camera::GetONB()
{
	CalculateTranslation();
	return m_TransMat;
}

//Private functions
void Camera::MoveBackward(float deltaTime)
{
	m_Position += m_Forward * m_Velocity.z * deltaTime;
	m_TransMat[3].xyz = Elite::FVector3(m_Position.xyz);
}

void Camera::MoveForward(float deltaTime)
{
	m_Position -= m_Forward * m_Velocity.z * deltaTime;
	m_TransMat[3].xyz = Elite::FVector3(m_Position.xyz);
}

void Camera::MoveUp(float deltaTime)
{
	const Elite::FVector3 up = m_TransMat[1].xyz;
	m_Position += up * m_Velocity.y * deltaTime;
	m_TransMat[3].xyz = Elite::FVector3(m_Position.xyz);
}

void Camera::MoveDown(float deltaTime)
{
	const Elite::FVector3 up = m_TransMat[1].xyz;
	m_Position -= up * m_Velocity.y * deltaTime;
	m_TransMat[3].xyz = Elite::FVector3(m_Position.xyz);
}

void Camera::MoveLeft(float deltaTime)
{
	const Elite::FVector3 right = m_TransMat[0].xyz;
	m_Position -= right * m_Velocity.x * deltaTime;
	m_TransMat[3].xyz = Elite::FVector3(m_Position.xyz);
}

void Camera::MoveRight(float deltaTime)
{
	const Elite::FVector3 right = m_TransMat[0].xyz;
	m_Position += right * m_Velocity.x * deltaTime;
	m_TransMat[3].xyz = Elite::FVector3(m_Position.xyz);
}

void Camera::Rotate(float deltaTime)
{
	m_YAngle -= m_MousePos.x*m_AngleSpeed * deltaTime;
	m_XAngle -= m_MousePos.y*m_AngleSpeed * deltaTime;
}