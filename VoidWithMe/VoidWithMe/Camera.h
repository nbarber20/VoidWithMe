#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float Zfar) {
		this->perspective = glm::perspective(fov, aspect, zNear, Zfar);
		this->position = pos;
		this->forward = glm::vec3(0, 0, 1);
		this->left = glm::vec3(1, 0, 0);
		this->up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 GetViewProjection() const {
		return perspective * glm::lookAt(position,position + forward, up);
	}

	inline glm::mat4 GetViewMatrix() const{
		return glm::lookAt(position,position + forward, up);
	}
	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 left;
	glm::vec3 up;
};