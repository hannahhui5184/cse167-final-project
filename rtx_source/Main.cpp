
#include <stdlib.h>
#include <iostream>
#include <../lib/Camera.h>
#include <../lib/rtx_source/Intersection.h>
#include <../lib/rtx_source/Ray.h>
#include <../lib/rtx_source/Image.h>
#include <../lib/Scene.h>

using namespace std;

/**
 * RayThruPixel - creates the Ray object that passes from the
 * camera position to the center of the (i,j) pixel
 * @param Camera 
 * @param int
 * @param int
 * @return Ray 
 */
Ray RayThruPixel(Camera cam, int i, int j)
{
    return {};
}

/**
 * Intersect - finds the intersection between ray and each of
 * the objects in the scene.
 * @param Ray
 * @param Scene
 * @return Intersection
 */
Intersection Intersect(Ray ray, Scene scene)
{
    float mindist = FLT_MAX;
    Intersection hit;
    for (pair<string, Geometry *> geo_pair : scene.geometry)
    { // Find closest intersection; test all objects
        // Intersection hit_temp = IntersectObj(ray, geo_pair.second);
        // // Ignore objects with no intersection (negative distance)
        // if (hit_temp.distance >= 0 && hit_temp.distance < mindist)
        // { // closer than previous hit
        //     mindist = hit_temp.distance;
        //     hit = hit_temp;
        // }
    }
    return hit;
}

/**
 * FindColor
 * @param Intersection
 * @return vec3
 */
glm::vec3 FindColor(Intersection hit)
{
    // Lambert diffuse light (like HW3)
    // Run through all the light and take the dot product
    // between the normal and the light direction

    // Recursive mirror reflection
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

/**
 * Raytrace - runs the raytracing algorithm and returns the
 * generated image.
 * @param Camera
 * @param Scene
 * @param int
 * @param height
 * @return
 */
Image *Raytrace(Camera cam, Scene scene, int width, int height)
{
    Image *image = new Image(width, height);
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            Ray ray = RayThruPixel(cam, i, j);
            Intersection hit = Intersect(ray, scene);
            image->pixelArr[i][j] = FindColor(hit);
        }
    }
    return image;
}

/**
 * Builds the scene and returns an image as a screenshot
 */
int main(int argc, char *argv[])
{
    std::cout << "Program is running" << endl;

    // Initialize Camera with the defaults from HW3
    Camera cam;
    cam.eye = glm::vec3(5.0f, 0.0f, 0.0f);
    cam.target = glm::vec3(0.0f, 0.0f, 0.0f);
    cam.up = glm::vec3(0.0f, 1.0f, 0.0f);
    cam.fovy = 30.0f;
    cam.aspect = 4.0f / 3.0f;
    cam.near = 0.01f;
    cam.far = 100.0f;

    // Create Scene
    // Scene scene = ?

    // Set width and height of image (currently arbitrary num)
    int width = 100;
    int height = 100;

    // Perform ray tracing
    // Image img = Raytrace(cam, scene, width, height);

    // Save screenshot of image
}
