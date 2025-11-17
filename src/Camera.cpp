#include "Camera.h"

Camera::Camera(const glm::vec3 &pos, const glm::vec3 &front, const glm::vec3 &up)
: pos(std::make_shared(pos))
, front(std::make_shared(front))
, up(std::make_shared(up)) {
	
}

Camera::~Camera() {

}