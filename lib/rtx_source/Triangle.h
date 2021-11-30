/**************************************************
TODO: Triangle
*****************************************************/
#define GLM_FORCE_RADIANS
#include "../Geometry.h"

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Intersection.h"

class Triangle : public Geometry
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
