#include <camera.h>
#include <utils.h>

Camera::Camera(glm::vec3 const & eye, glm::vec3 const & upV, glm::vec3 const & rightV, glm::vec3 const & forwardV, float fov, float apertureSize, glm::vec3 const& uV, glm::vec3 const& vV, glm::vec3 const& wV)
	: eye_position(eye), up(upV), right(rightV), forward(forwardV), vfov(fov), lens_radius(apertureSize/2.0f), u(uV), v(vV), w(wV)
{
}

Camera::Camera(float verticalfov, float aspectRatio, float apertureSize, float focusPlaneDistance, glm::vec3 const& eyePos, glm::vec3 const& lookAt, glm::vec3 const& upVector)
	: vfov(verticalfov), lens_radius(apertureSize/2.0f), eye_position(eyePos), up(upVector)
{
	const float theta = vfov * (3.14159265359f/180.0f);
	const float halfheight = tanf(theta / 2.0f);
	const float halfwidth = aspectRatio * halfheight;

	w = glm::normalize(eye_position - lookAt);
	u = glm::normalize(glm::cross(up, w));
	v = glm::cross(w, u);

	forward = eye_position - halfwidth * u * focusPlaneDistance - halfheight * v * focusPlaneDistance - w * focusPlaneDistance;
	right = 2.0f * halfwidth * u * focusPlaneDistance;
	up = 2.0f * halfheight * v * focusPlaneDistance;
}

Ray Camera::getRD(glm::vec2 const& uv) const
{
	glm::vec2 randomPoint = randomPointOnLens() * lens_radius;
	glm::vec3 originOffset = u * randomPoint.x + v * randomPoint.y;
	return Ray(eye_position + originOffset, glm::normalize(forward + right * uv.x + up * uv.y - eye_position - originOffset));
}

glm::vec2 Camera::randomPointOnLens() const
{
	float r = randomNumberGen() * 0.5f + 0.5f;
	float theta = (randomNumberGen() * 0.5f + 0.5f) * 6.28318530718f;
	glm::vec2 result = glm::vec2(sqrtf(r) * cosf(theta), sqrtf(r) * sinf(theta));
	return (result);
}
