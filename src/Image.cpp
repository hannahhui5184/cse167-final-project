#include "../lib/Image.h"
using namespace std;

/**
 * Constructor for Image
 */
Image::Image(int width, int height)
{
    for (int col = 0; col < width; col++)
    {
        vector<glm::vec3> row_vec;
        for (int row = 0; row < height; row++)
        {
            row_vec.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        }
        Image::pixelArr.push_back(row_vec);
    }
}

//std::vector<int> second (4,100);
