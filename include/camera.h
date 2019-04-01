#ifndef _CAMERA_H_
#define _CAMERA_H_
#pragma once
#include <glm.hpp>
#include <ray.h>
struct Camera
{
	Camera(glm::vec3 const& eye = glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3 const& upV = glm::vec3(0.0, 1.0, 0.0), glm::vec3 const& rightV = glm::vec3(1.0, 0.0, 0.0f), glm::vec3 const& forwardV = glm::vec3(0.0, 0.0, -1.0f), float fov = 45.0f, float apertureSize = 1.0f, glm::vec3 const& uV = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 const& vV = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 const& wV = glm::vec3(0.0f, 0.0f, -1.0f));
	Camera(float verticalfov, float aspectRatio, float apertureSize, float focusPlaneDistance, glm::vec3 const& eyePos, glm::vec3 const& lookAt, glm::vec3 const& upVector);
	float vfov;
	float lens_radius;
	glm::vec3 eye_position;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 forward;

	Ray getRD(glm::vec2 const& uv) const;

private:
	glm::vec2 randomPointOnLens() const;
	glm::vec3 u, v, w;
};

#endif //_CAMERA_H_
