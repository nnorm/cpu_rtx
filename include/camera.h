#ifndef _CAMERA_H_
#define _CAMERA_H_
#pragma once
#include <glm.hpp>
#include <ray.h>
struct Camera
{
	glm::vec3 eye_position = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 right = glm::vec3(1.0, 0.0, 0.0f);
	glm::vec3 forward = glm::vec3(0.0, 0.0, -1.0f);

	Ray getRD(glm::vec2 const& uv, float aspectRatio) const;
};

#endif //_CAMERA_H_
