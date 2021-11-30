#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

float sq_distance(glm::vec3 p1, glm::vec3 p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.x - p2.x) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
}
