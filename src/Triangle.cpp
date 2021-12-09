#include <stdlib.h>
#include <math.h>
#include "../lib/Triangle.h"

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

    glm::vec3 p1 = this->points[0];
    glm::vec3 p3 = this->points[2];
    glm::vec3 p2 = this->points[1];

    glm::vec3 n1 = this->norms[0];
    glm::vec3 n2 = this->norms[1];
    glm::vec3 n3 = this->norms[2];

    // Solve for Barycentric coord
    glm::mat4x4 mat(glm::vec4(p1, 1.0f),
                    glm::vec4(p2, 1.0f),
                    glm::vec4(p3, 1.0f),
                    glm::vec4(-1.0f * ray.dir, 0.0f));

    glm::vec4 p0(ray.pos, 1.0f);
    glm::vec4 bary = glm::inverse(mat) * p0;

    // No intersection with this ray
    if (bary.x < 0 || bary.y < 0 || bary.z < 0 || bary.w < 0)
    {
        intersect.distance = -1.0f;
        return intersect;
    }

    // Find the intersection point with Barycentric coord
    glm::vec3 q = bary.x * p1 + bary.y * p2 + bary.z * p3;

    glm::vec3 n = glm::normalize(bary.x * n1 + bary.y * n2 + bary.z * n3);

    intersect.position = q;                             // position of the intersection
    intersect.n = n;                                    // surface normal (unit vector)
    intersect.material = Triangle::material;            // pointer to material/object
    intersect.v = glm::normalize(-1.0f * ray.dir);      // direction to the incoming ray (unit vector)
    intersect.distance = sqrt(sq_distance(q, ray.pos)); // distance from ray source to intersect point

    return intersect;
}
