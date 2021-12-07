#include <stdlib.h>
#include <iostream>
#include <../lib/Camera.h>
#include "../lib/Intersection.h"
#include <../lib/Ray.h>
#include <../lib/Scene.h>
#include <../lib/Screenshot.h>
#include <glm/gtx/string_cast.hpp>

using namespace std;
int width = 100;
int height = 100;

int REC_DEPTH = 1;
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
    float alpha = (2 * (i + 0.5) / width - 1) * tan(cam->fovy / 2 * 3.14159265 / 180.0);
    float beta = (1 - 2 * (j + 0.5) / height) * cam->aspect * tan(cam->fovy / 2 * 3.14159265 / 180.0);
    // std::cout <<  "position: " << ray.pos.x << "," << ray.pos.y << "," << ray.pos.z << endl;
    // std::cout << "direction: " << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << endl;
    // std::cout << "eye: " << cameraMat[3][0] << "," << cameraMat[3][1] << "," << cameraMat[3][2] << endl;
    // std::cout << "aspect: " << cam->aspect << endl;

    // std::cout << "view:" << glm::to_string(cameraMat) << endl;
    // std::cout << "alpha " << alpha << endl;
    // std::cout << "beta " << beta << endl;
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
    // std::cout << scene->worldTriangles.size() << endl;
    for (Triangle *tri : scene->worldTriangles)
    { // Find closest intersection; test all objects
        // std::cout << "World Tri: " << glm::to_string(tri->points) << endl;
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

    cout << "depth: " << depth << endl;
    // Get all light rays and lighting effects from each light
    if (depth > 0)
    {
    for (pair<string, Light *> light_pair : scene->light)
    {
        cout << "test" << endl;
        Light *light = light_pair.second;
        glm::vec3 lightDir = glm::vec3(light->position) - hit.position;

        Ray lightRay(hit.position, lightDir);

        // If there is an intersection between the light and the intersect point,
        // do not add this color component
        if (!hasIntersect(lightRay, scene))
        {
            cout << "test2" << endl;
            Intersection lightHit = Intersect(lightRay, scene);
            // ambient and Lambert diffuse components (4-3 Lighting slide 25)
            glm::vec4 light4 = (lightHit.material->ambient + lightHit.material->diffuse * std::max(glm::dot(lightHit.n, lightDir), 0.0f)) * light->color;

            color += glm::vec3(light4);
        }
    }

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
            std::cout <<  "position: " << ray.pos.x << "," << ray.pos.y << "," << ray.pos.z << endl;
            std::cout << "direction: " << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << endl;
            Intersection hit = Intersect(ray, scene);
            std::cout <<  "position intersection: " << hit.position.x << "," << hit.position.y << "," << hit.position.z << endl;
            std::cout << "distance: " << hit.distance << endl;
            std::cout << "normal: " << glm::to_string(hit.n) << endl;
            image->pixelArr[i][j] = FindColor(hit, scene, REC_DEPTH);
            std::cout << image->pixelArr[i][j].x << "," << image->pixelArr[i][j].y << "," << image->pixelArr[i][j].z << endl;
        }
        std::cout << endl;
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
    // scene.camera->eye = glm::vec3(2.0f,2.0f,2.0f);
    scene.draw();
    
    


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
