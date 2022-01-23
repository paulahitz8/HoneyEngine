#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib/Math/float3.h"
#include "MathGeoLib/Math/float4x4.h"
#include "MathGeoLib/Geometry/Frustum.h"
#include "glmath.h"

class GameObject;

class Camera3D : public Module
{
public:
	Camera3D(HoneyEngine* engine);
	~Camera3D();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void LookAt(const float3& Spot);
	void CalculateViewMatrix();
	void RecalculateProjection();
	void OnGui() override;
	//void OnSave(JSONWriter& writer) const override;
	//void OnLoad(const JSONReader& reader) override;

public:
	float3 right, up, front, position, reference;
	Frustum cameraFrustum;
	float4x4 viewMatrix;
	float aspectRatio = 1.f;
	float verticalFOV = 60.f;
	float nearPlaneDistance = 0.1f;
	float farPlaneDistance = 5000.f;
	float cameraSensitivity = .5f;
	float cameraSpeed = 90.f;
	bool projectionIsDirty = false;

private:
	float lastDeltaX = 0.f, lastDeltaY = 0.f;

	HoneyEngine* engine = nullptr;
};