#include <camera.h>

Ray Camera::getRD(glm::vec2 const& uv, float aspectRatio) const 
{
	glm::vec2 centered_uv = uv - glm::vec2(0.5f);
	return Ray(eye_position, (forward + centered_uv.x * right * aspectRatio + centered_uv.y * up));
}