/**************************************************
TODO: Ray
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#ifndef __RAY_H__
#define __RAY_H__

class Ray
{
public:
    glm::vec3 pos; // position of ray
    glm::vec3 dir; // direction of ray (unit vector)
};

#endif
