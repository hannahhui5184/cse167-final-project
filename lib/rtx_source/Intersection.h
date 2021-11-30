/**************************************************
TODO: Intersection
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#ifndef __INTERSECT_H__
#define __INTERSECT_H__

#include "Ray.h"
class Intersection
{
public:
    glm::vec3 position; // position of the intersection

    // Geometry info
    glm::vec3 n; // surface normal (unit vector)
    Obj object;  // pointer to material/object

    // Ray info
    glm::vec3 v;    // direction to the incoming ray (unit vector)
    float distance; // distance to the source of the array
};

#endif
