/**************************************************
TODO: Sphere
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Intersection.h"
class Sphere
{
public:
    // Geometry info
    glm::vec3 center;
    float radius;

    // Intersect
    Intersection Intersect(Ray ray);
};

#endif
