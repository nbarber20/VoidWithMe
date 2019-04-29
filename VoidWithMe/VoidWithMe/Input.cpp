#include "Input.h"



Input::Input()
{

}

void Input::Update(float dt, Display* display, Camera* camera, std::vector<BoxCollider*> Colliders)
{

	double Mousedx = 0;
	double Mousedy = 0;
	glfwGetCursorPos(display->GetWindow(), &Mousedx, &Mousedy);

	// Reset mouse position for next frame
	glfwSetCursorPos(display->GetWindow(), display->Width/2, display->Height/2);


	horizontalAngle += CameraSpeed * float(display->Width / 2 - Mousedx);
	verticalAngle += CameraSpeed * float(display->Height / 2 - Mousedy);




	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);
	glm::vec3 up = glm::cross(right, direction);


	camera->forward = direction;
	camera->up = up;
	camera->left = right;

	double Movedx = 0;
	double Movedy = 0;
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		Movedx = 1;
	}
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		Movedx = -1;
	}
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		Movedy = -1;
	}
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		Movedy = 1;
	}



	glm::vec3 MoveForward = camera->forward;
	MoveForward.y = 0;
	MoveForward = glm::normalize(MoveForward);


	glm::vec3 CheckPos = camera->position;
	CheckPos = camera->position;
	CheckPos += MoveForward * (float)Movedx *movementSpeed*dt;

	bool overlapx = false;
	for (auto &box : Colliders)
	{
		if (box->PointOverlap(CheckPos))
		{
			if (box->isTrigger == false) {
				overlapx = true;
			}
		}
	}
	if (overlapx == false)
	{

		camera->position += MoveForward * (float)Movedx *movementSpeed *dt;
	}







	CheckPos = camera->position;
	CheckPos += camera->left * (float)Movedy *movementSpeed*dt;
	bool overlapy = false;
	for (auto &box : Colliders)
	{
		if (box->PointOverlap(CheckPos))
		{
			if (box->isTrigger == false) {
			
				overlapy = true;
			}
		}
	}
	if (overlapy == false)
	{

		camera->position += camera->left * (float)Movedy *movementSpeed*dt;
	}

}

