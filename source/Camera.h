#pragma once
#include "EMath.h"
#include <SDL.h>

class Camera
{
public:
	Camera(const Elite::FPoint4& pos);
	~Camera();
	void Update(float deltaTime);
	float CalculateFOV(float degrees=45.f)const;
	float GetFOV()const;
	Elite::FMatrix4 GetTranslation() const;	
	Elite::FMatrix4 GetXRotationMatrix() const;
	Elite::FMatrix4 GetYRotationMatrix() const;
	Elite::FMatrix4 GetONB();
private:
	float m_Fov;	
	float m_YAngle;
	float m_XAngle;
	Elite::FVector3 m_Forward;
	Elite::FPoint4 m_Position;
	Elite::FMatrix4 m_TransMat;
	Elite::FMatrix4 m_RotMatX;
	Elite::FMatrix4 m_RotMatY;
	Elite::IVector2 m_MousePos;
	const Elite::FVector3 m_Velocity{ 10.f,10.f,10.f };
	const float m_AngleSpeed{ 0.1f };
	
	//Calculation functions
	void CalculateTranslation();
	void CalculateXRotationMatrix();
	void CalculateYRotationMatrix();

	//Movement functions
	void MoveBackward(float deltaTime);
	void MoveForward(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void Rotate(float deltaTime);
};