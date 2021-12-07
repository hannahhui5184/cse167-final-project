#include <stdlib.h>
#include <iostream>
#include <../lib/Camera.h>
#include "../lib/Intersection.h"
#include <../lib/Ray.h>
#include <../lib/Scene.h>
#include <../lib/Screenshot.h>

using namespace std;
int width = 100;
int height = 100;

int REC_DEPTH = 3;
/**
 * RayThruPixel - creates the Ray object that passes from the
 * camera position to the center of the (i,j) pixel
 * @param Camera 
 * @param int
 * @param int
 * @return Ray 
 */
Ray RayThruPixel(Camera *cam, int i, int j)
{
    glm::mat4 cameraMat = glm::inverse(cam->view);
    glm::vec3 u = glm::vec3(cameraMat[0][0], cameraMat[0][1], cameraMat[0][2]);
    glm::vec3 v = glm::vec3(cameraMat[1][0], cameraMat[1][1], cameraMat[1][2]);
    glm::vec3 w = glm::vec3(cameraMat[2][0], cameraMat[2][1], cameraMat[2][2]);
    float alpha = 2 * (i + 1 / 2) / width - 1;
    float beta = 1 - 2 * (i + 1 / 2) / height;
    return Ray(cam->eye, glm::normalize(alpha * u + beta * v - w));
}

/**
 * Intersect - finds the intersection between ray and each of
 * the objects in the scene.
 * @param Ray
 * @param Scene
 * @return Intersection
 */
Intersection Intersect(Ray ray, Scene *scene)
{
    float mindist = FLT_MAX;
    Intersection hit;
    for (Triangle *tri : scene->worldTriangles)
    { // Find closest intersection; test all objects
        Intersection hit_temp = tri->Intersect(ray);
        // Ignore objects with no intersection (negative distance)
        if (hit_temp.distance >= 0 && hit_temp.distance < mindist)
        { // closer than previous hit
            mindist = hit_temp.distance;
            hit = hit_temp;
        }
    }
    return hit;
}

/**
 * @brief 
 * 
 * @param ray 
 * @param scene 
 * @return bool 
 */
bool hasIntersect(Ray ray, Scene *scene)
{
    for (Triangle *tri : scene->worldTriangles)
    {
        Intersection hit_temp = tri->Intersect(ray);
        // Triangles that do have intersection with the ray
        // will have a positive distance
        if (hit_temp.distance >= 0)
        {
            return true;
        }
    }
    return false;
}

/**
 * FindColor
 * @param Intersection
 * @return vec3
 */
glm::vec3 FindColor(Intersection hit, Scene *scene, int depth)
{
    // Lambert diffuse light (like HW3)
    // Run through all the light and take the dot product
    // between the normal and the light direction

    // Recursive mirror reflection

    glm::vec3 color(0.0f, 0.0f, 0.0f);

    // Get all light rays and lighting effects from each light
    for (pair<string, Light *> light_pair : scene->light)
    {
        Light *light = light_pair.second;
        glm::vec3 lightDir = glm::vec3(light->position) - hit.position;

        Ray lightRay(hit.position, lightDir);

        // If there is an intersection between the light and the intersect point,
        // do not add this color component
        if (!hasIntersect(lightRay, scene))
        {
            Intersection lightHit = Intersect(lightRay, scene);
            // ambient and Lambert diffuse components (4-3 Lighting slide 25)
            glm::vec4 light4 = (lightHit.material->ambient + lightHit.material->diffuse * std::max(glm::dot(lightHit.n, lightDir), 0.0f)) * light->color;

            color += glm::vec3(light4);
        }
    }

    if (depth > 0)
    {
        // Generate the mirror reflected ray and recurse
        glm::vec3 mirrorDir = 2 * (glm::dot(hit.n, hit.v)) * (hit.n - hit.v); // (7-1 RayTracing slide 55)
        Ray mirrorRay(hit.position, mirrorDir);
        Intersection mirrorHit = Intersect(mirrorRay, scene);
        color += FindColor(mirrorHit, scene, depth - 1);
    }

    return color;
}

/**
 * Raytrace - runs the raytracing algorithm and returns the
 * generated image.
 * @param Camera*
 * @param Scene
 * @param int
 * @param height
 * @return
 */
Image *Raytrace(Camera *cam, Scene *scene, int width, int height)
{
    Image *image = new Image(width, height);
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            Ray ray = RayThruPixel(cam, i, j);
            Intersection hit = Intersect(ray, scene);
            image->pixelArr[i][j] = FindColor(hit, scene, REC_DEPTH);
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

    // Initialize Scene
    Scene scene;
    scene.init();

    // Create Scene
    // Scene scene = ?

    // Set width and height of image (currently arbitrary num)
    int width = 100;
    int height = 100;

    // Perform ray tracing
    Image *img = Raytrace(scene.camera, &scene, width, height);

    // Save screenshot of image
    Screenshot screenshot;
    screenshot.save("test.png", img);
}
