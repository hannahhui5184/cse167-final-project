/**************************************************
TODO: Triangle
*****************************************************/
#define GLM_FORCE_RADIANS
#include "Geometry.h"

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Intersection.h"

class Triangle
{
public:
    // Geometry info
    glm::mat3x3 points;
    glm::mat3x3 norms;

    Material *material;

    // Init (each column is a length3 point)
    void init(glm::mat3x3 tri, glm::mat3x3 norm)
    {
        points = tri;
        norms = norm;
    };
    // Intersect
    Intersection Intersect(Ray ray);
};

#endif
