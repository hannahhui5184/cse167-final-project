/**************************************************
TODO: Triangle
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Intersection.h"

class Intersection
{
public:
    // Geometry info
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;

    // Intersect
    Intersection Intersect(Ray ray);
};

#endif
