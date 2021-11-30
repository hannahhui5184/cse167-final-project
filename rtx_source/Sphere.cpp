#include <stdlib.h>
#include "../lib/rtx_source/Sphere.h"

float sq_dist(glm::vec3 p1, glm::vec3 p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.x - p2.x) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
}
/**
 * Reference: Slides 38-40
 */
Intersection Sphere::Intersect(Ray ray)
{
    Intersection intersect;

    float quad = pow(glm::dot(ray.dir, ray.pos - Sphere::center), 2) - sq_dist(ray.pos, Sphere::center) + pow(Sphere::radius, 2);

    // No intersection
    if (quad < 0)
    {
        intersect.distance = -1.0f;
        return intersect;
    }
    // Tangent
    else if (quad == 0)
    {
        intersect.distance = -1.0f;
        return intersect;
    }
    // Two intersections
    else
    {
        float a = glm::dot(-1.0f * ray.dir, ray.pos - Sphere::center);
        float t1 = a + quad;
        float t2 = a - quad;
        float t;

        // Select the smallest positive t
        if (t1 > 0 && t2 > 0)
        {
            t = min(t1, t2);
        }
        else if (t1 > 0)
        {
            t = t1;
        }
        else if (t2 > 0)
        {
            t = t2;
        }

        glm::vec3 q = ray.pos + t * ray.dir;
        glm::vec3 n = glm::normalize(q - Sphere::center);

        intersect.position = q;                         // position of the intersection
        intersect.n = n;                                // surface normal (unit vector)
        intersect.object = (Geometry *)this;            // pointer to material/object
        intersect.v = glm::normalize(-1.0f * ray.dir);  // direction to the incoming ray (unit vector)
        intersect.distance = sqrt(sq_dist(q, ray.pos)); // distance from ray source to intersect point

        return intersect;
    }
}
