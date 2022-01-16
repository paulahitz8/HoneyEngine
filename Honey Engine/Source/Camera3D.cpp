#include "Globals.h"
#include "Camera3D.h"
#include "Engine.h"
#include "Input.h"
#include "SceneManager.h"
#include "Editor.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "Renderer3D.h"

#include "SDL.h"
#include "Log.h"
#include "ImGuiAppLog.h"
#include "MathGeoLib/Geometry/LineSegment.h"

Camera3D::Camera3D(HoneyEngine* engine) : Module()
{
	name = "Camera";
	this->engine = engine;

	right = float3(1.0f, 0.0f, 0.0f);
	up = float3(0.0f, 1.0f, 0.0f);
	front = float3(0.0f, 0.0f, 1.0f);

	position = float3(0.0f, 5.0f, -15.0f);
	reference = float3(0.0f, 0.0f, 0.0f);

	CalculateViewMatrix();
}

Camera3D::~Camera3D()
{
}

bool Camera3D::Start()
{
	CONSOLE_LOG("Setting up the camera");
	appLog->AddLog("Setting up the camera\n");

	LookAt(float3::zero);

	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool Camera3D::CleanUp()
{
	CONSOLE_LOG("Cleaning camera");
	appLog->AddLog("Cleaning camera\n");

	return true;
}

// -----------------------------------------------------------------
bool Camera3D::Update(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movement frame rate independant!

	float3 newPos(0, 0, 0);
	float speed = cameraSpeed * dt;
	if (engine->GetInput()->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) speed *= 4.f;

	if (engine->GetInput()->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) newPos.y += speed;
	if (engine->GetInput()->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) newPos.y -= speed;

	// Focus --> NEEDS TO BE FIXED... SOME (MESH) FUNCTIONS DEPEND ON A PRIMITIVE LIBRARY WE STILL DON'T HAVE IMPLEMENTED.
	if (engine->GetInput()->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		// TO DO: Manage current object selection by the game object itself! Not by its index...
		if (/*engine->GetEditor()->gameobjectSelected != nullptr <-- Should be this way*/
			engine->GetEditor()->panelGameObjectInfo.selectedGameObjectID != -1)
		{
			// If we change the previous TO DO, this will be no longer needed...
			GameObject* gameObjectSelected =
				engine->GetSceneManager()->GetCurrentScene()->GetGameObject(engine->GetEditor()->panelGameObjectInfo.selectedGameObjectID);

			if (ComponentMesh* mesh = /*App->editor->gameobjectSelected->GetComponent<ComponentMesh>()*/
				gameObjectSelected->GetComponent<ComponentMesh>())
			{
				const float3 meshCenter = mesh->GetCenterPointInWorldCoords(); // FIX THIS FUNCTION
				LookAt(meshCenter);
				const float meshRadius = mesh->GetSphereRadius(); // FIX THIS FUNCTION
				const float currentDistance = meshCenter.Distance(position);
				const float desiredDistance = (meshRadius * 2) / atan(cameraFrustum.horizontalFov);
				position = position + front * (currentDistance - desiredDistance);
			}
			else
			{
				LookAt(gameObjectSelected->GetTransform()->GetPosition());
			}
		}
	}

	vec3 spot(0, 0, 0); // Spot where the current selected game object is located.
	if (engine->GetEditor()->panelGameObjectInfo.selectedGameObjectID != -1)
	{
		spot.x = (engine->GetSceneManager()->GetCurrentScene()->GetGameObject(engine->GetEditor()->panelGameObjectInfo.selectedGameObjectID)->GetTransform())->GetPosition().x;
		spot.y = (engine->GetSceneManager()->GetCurrentScene()->GetGameObject(engine->GetEditor()->panelGameObjectInfo.selectedGameObjectID)->GetTransform())->GetPosition().y;
		spot.z = (engine->GetSceneManager()->GetCurrentScene()->GetGameObject(engine->GetEditor()->panelGameObjectInfo.selectedGameObjectID)->GetTransform())->GetPosition().z;
	}
	if (engine->GetInput()->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		LookAt(float3(5, 5, 5));
	}

	if (engine->GetInput()->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos += front * speed;
	if (engine->GetInput()->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos -= front * speed;

	if (engine->GetInput()->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos += right * speed;
	if (engine->GetInput()->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos -= right * speed;

	if (engine->GetInput()->GetMouseZ() > 0) newPos += front * speed * 2;
	if (engine->GetInput()->GetMouseZ() < 0) newPos -= front * speed * 2;

	position += newPos; // MODULE CAMERA REVISION CHECKPOINT --> CHECK AND FIX ERRORS FIRST!

	// Mouse motion ----------------

	bool hasRotated = false;

	if (engine->GetInput()->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		int dx = -engine->GetInput()->GetMouseXMotion();
		int dy = -engine->GetInput()->GetMouseYMotion();

		if (engine->GetInput()->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT) {
			if (/*engine->GetEditor()->gameobjectSelected != nullptr*/
				engine->GetEditor()->panelGameObjectInfo.selectedGameObjectID != -1)
			{
				const float newDeltaX = (float)dx * cameraSensitivity;
				const float newDeltaY = (float)dy * cameraSensitivity;

				reference = /*engine->GetEditor()->gameobjectSelected->transform->GetPosition()*/
					engine->GetSceneManager()->GetCurrentScene()->GetGameObject(engine->GetEditor()
						->panelGameObjectInfo.selectedGameObjectID)->GetComponent<ComponentTransform>()->GetPosition();
				Quat orbitMat = Quat::RotateY(newDeltaX * .1f);

				if (abs(up.y) < 0.3f) // Avoid gimball lock on up & down apex
				{
					if (position.y > reference.y && newDeltaY < 0.f)
						orbitMat = orbitMat * math::Quat::RotateAxisAngle(right, newDeltaY * .1f);
					if (position.y < reference.y && newDeltaY > 0.f)
						orbitMat = orbitMat * math::Quat::RotateAxisAngle(right, newDeltaY * .1f);
				}
				else
				{
					orbitMat = orbitMat * math::Quat::RotateAxisAngle(right, newDeltaY * .1f);
				}

				position = orbitMat * (position - reference) + reference;

				CalculateViewMatrix();
				LookAt(reference);
			}
		}
		else
		{
			if (dx != 0)
			{
				const float newDeltaX = (float)dx * cameraSensitivity;
				float deltaX = newDeltaX + 0.95f * (lastDeltaX - newDeltaX); //lerp for smooth rotation acceleration to avoid jittering
				lastDeltaX = deltaX;
				Quat rotateY = Quat::RotateY(up.y >= 0.f ? deltaX * .1f : -deltaX * .1f);
				up = rotateY * up;
				front = rotateY * front;
				CalculateViewMatrix();
				hasRotated = true;
			}

			if (dy != 0)
			{
				const float newDeltaY = (float)dy * cameraSensitivity;
				float deltaY = newDeltaY + 0.95f * (lastDeltaY - newDeltaY); //lerp for smooth rotation acceleration to avoid jittering
				lastDeltaY = deltaY;
				Quat rotateX = Quat::RotateAxisAngle(right, -deltaY * .1f);
				up = rotateX * up;
				front = rotateX * front;
				CalculateViewMatrix();
				hasRotated = true;
			}
		}
	}

	!hasRotated ? lastDeltaX = lastDeltaY = 0.f : 0.f;

	CalculateViewMatrix();

	return true;
}

// -----------------------------------------------------------------
void Camera3D::LookAt(const float3& point)
{
	reference = point;

	front = (reference - position).Normalized();
	right = float3(0.0f, 1.0f, 0.0f).Cross(front).Normalized();
	up = front.Cross(right);

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void Camera3D::CalculateViewMatrix()
{
	if (projectionIsDirty)
		RecalculateProjection();

	cameraFrustum.pos = position;
	cameraFrustum.front = front.Normalized();
	cameraFrustum.up = up.Normalized();
	float3::Orthonormalize(cameraFrustum.front, cameraFrustum.up);
	right = up.Cross(front);
	viewMatrix = cameraFrustum.ViewMatrix();
}

void Camera3D::RecalculateProjection()
{
	cameraFrustum.type = FrustumType::PerspectiveFrustum;
	cameraFrustum.nearPlaneDistance = nearPlaneDistance;
	cameraFrustum.farPlaneDistance = farPlaneDistance;
	cameraFrustum.verticalFov = (verticalFOV * 3.141592 / 2) / 180.f;
	cameraFrustum.horizontalFov = 2.f * atanf(tanf(cameraFrustum.verticalFov * 0.5f) * aspectRatio);
}

void Camera3D::OnGui()
{
	if (ImGui::CollapsingHeader("Editor Camera"))
	{
		if (ImGui::DragFloat("Vertical fov", &verticalFOV))
		{
			projectionIsDirty = true;
		}
		if (ImGui::DragFloat("Near plane distance", &nearPlaneDistance))
		{
			projectionIsDirty = true;
		}
		if (ImGui::DragFloat("Far plane distance", &farPlaneDistance))
		{
			projectionIsDirty = true;
		}
	}
}

//void Camera3D::OnSave(JSONWriter& writer) const
//{
//	writer.String("camera");
//	writer.StartObject();
//	SAVE_JSON_FLOAT(verticalFOV)
//		SAVE_JSON_FLOAT(nearPlaneDistance)
//		SAVE_JSON_FLOAT(farPlaneDistance)
//		SAVE_JSON_FLOAT(cameraSpeed)
//		SAVE_JSON_FLOAT(cameraSensitivity)
//		writer.EndObject();
//}
//
//void Camera3D::OnLoad(const JSONReader& reader)
//{
//	if (reader.HasMember("camera"))
//	{
//		const auto& config = reader["camera"];
//		LOAD_JSON_FLOAT(verticalFOV);
//		LOAD_JSON_FLOAT(nearPlaneDistance);
//		LOAD_JSON_FLOAT(farPlaneDistance);
//		LOAD_JSON_FLOAT(cameraSpeed);
//		LOAD_JSON_FLOAT(cameraSensitivity);
//	}
//	RecalculateProjection();
//}
