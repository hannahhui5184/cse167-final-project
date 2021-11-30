#include <stdlib.h>
#include <math.h>
#include "../lib/rtx_source/Triangle.h"

float sq_distance(glm::vec3 p1, glm::vec3 p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.x - p2.x) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
}
/**
 * Reference: Slides 33-34
 */
Intersection Triangle::Intersect(Ray ray)
{
    Intersection intersect;

    // Solve for Barycentric coord
    glm::mat4x4 mat(glm::vec4(Triangle::p1, 1.0f),
                    glm::vec4(Triangle::p1, 1.0f),
                    glm::vec4(Triangle::p1, 1.0f),
                    glm::vec4(-1.0f * ray.dir, 0.0f));

    glm::vec4 p0(ray.pos, 1.0f);
    glm::vec4 bary = glm::inverse(mat) * p0;

    // No intersection with this ray
    if (bary[0] < 0 || bary[1] < 0 || bary[2] < 0 || bary[3] < 0)
    {
        intersect.distance = -1.0f;
        return intersect;
    }

    // Find the intersection point with Barycentric coord
    glm::vec3 q = bary.x * p1 + bary.y * p2 + bary.z * p3;

    // Find normal to triangle using cross product
    glm::vec3 n = glm::normalize(glm::cross(p1 - p2, p1 - p3));
    // Choose normal vector that points towards the ray
    n = (sq_distance(ray.pos, q + n) < sq_distance(ray.pos, q - n)) ? n : -1.0f * n;

    intersect.position = q;                             // position of the intersection
    intersect.n = n;                                    // surface normal (unit vector)
    intersect.object = (Geometry *)this;                // pointer to material/object
    intersect.v = glm::normalize(-1.0f * ray.dir);      // direction to the incoming ray (unit vector)
    intersect.distance = sqrt(sq_distance(q, ray.pos)); // distance from ray source to intersect point

    return intersect;
}
