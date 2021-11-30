#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <stdio.h>
#include <vector>

using namespace std;

typedef vector<vector<glm::vec3>> img;

class Image
{
public:
    // variables
    int width;
    int height;
    img pixelArr;

    // functions
    Image(int width, int height);
};
