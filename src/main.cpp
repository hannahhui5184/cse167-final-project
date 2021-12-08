#include <stdlib.h>
#include <iostream>
#include <../lib/Camera.h>
#include "../lib/Intersection.h"
#include <../lib/Ray.h>
#include <../lib/Scene.h>
#include <../lib/Screenshot.h>
#include <glm/gtx/string_cast.hpp>

using namespace std;

#define WIDTH 120
#define HEIGHT 90
#define REC_DEPTH 0

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
    float alpha = (2 * (i + 0.5) / WIDTH - 1) * tan(cam->fovy / 2 * 3.14159265 / 180.0);
    float beta = (1 - 2 * (j + 0.5) / HEIGHT) * cam->aspect * tan(cam->fovy / 2 * 3.14159265 / 180.0);
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
    // std::cout << "WorldTri size: " << scene->worldTriangles.size() << endl;
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

    // If no intersections are found, the normal vector will never be updated
    // On updates, the normal vector is normalized (magnitude 1)
    if (0 == glm::length(hit.n))
    {
        hit.distance = -1;
    }
    return hit;
}

/**
 * FindColor
 * @param Intersection Intersection from camera ray and scene
 * @param Scene* Scene to get information on lights
 * @param depth Limits recursion depth, base case depth = 0
 * @return vec3 Color of the pixel
 */
glm::vec3 FindColor(Intersection hit, Scene *scene, int depth)
{
    // Lambert diffuse light (like HW3)
    // Run through all the light and take the dot product
    // between the normal and the light direction

    // Recursive mirror reflection

    glm::vec3 color(0.0f, 0.0f, 0.0f);

    // cout << "depth: " << depth << endl;
    if (hit.distance < 0)
    {
        return color;
    }

    // Get all light rays and lighting effects from each light
    for (pair<string, Light *> light_pair : scene->light)
    {
        // cout << "test" << endl;
        Light *light = light_pair.second;
        glm::vec3 lightDir = glm::vec3(light->position) - hit.position;

        Ray lightRay(hit.position + 0.01f * lightDir, lightDir); // offset to avoid self shadowing

        // If there is an intersection between the light and the intersect point,
        // do not add this color component
        Intersection interfere = Intersect(lightRay, scene);
        if (interfere.distance < 0)
        {
            // cout << "test2" << endl;
            // ambient and Lambert diffuse components (4-3 Lighting slide 25)
            glm::vec4 light4 = (hit.material->ambient + hit.material->diffuse * std::max(glm::dot(hit.n, lightDir), 0.0f)) * light->color;

            // cout << "Dot Prod: " << glm::dot(hit.n, lightDir) << endl;
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
 * @param Scene*
 * @param int
 * @param int
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
            // Ray ray(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            // std::cout << "(i,j): " << i << " " << j << endl;
            // std::cout << "position: " << ray.pos.x << "," << ray.pos.y << "," << ray.pos.z << endl;
            // std::cout << "direction: " << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << endl;
            Intersection hit = Intersect(ray, scene);
            // std::cout << "position intersection: " << hit.position.x << "," << hit.position.y << "," << hit.position.z << endl;
            // std::cout << "distance: " << hit.distance << endl;
            // std::cout << "normal: " << glm::to_string(hit.n) << endl
            //           << endl;
            image->pixelArr[j][i] = FindColor(hit, scene, REC_DEPTH);
            // if (hit.distance < 0)
            // {
            //     image->pixelArr[j][i] = glm::vec3(0.0f, 0.0f, 0.0f);
            // }
            // else
            // {
            //     image->pixelArr[j][i] = normalize(hit.n) * 0.5f + 0.5f;
            // }
            // std::cout << image->pixelArr[j][i].x << "," << image->pixelArr[j][i].y << "," << image->pixelArr[j][i].z << endl;
        }
        std::cout << "Raytracing is " << round(j * 100.0 / height) << "% done." << endl;
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
    scene.camera->aspect = float(WIDTH) / HEIGHT;
    scene.draw();

    // Create Scene
    // Scene scene = ?

    // Set width and height of image (currently arbitrary num)

    cout << "Begin raytracing..." << endl;
    // Perform ray tracing
    // Image img(width, height);
    Image *img = Raytrace(scene.camera, &scene, WIDTH, HEIGHT);
    cout << "Finished raytracing." << endl;

    cout << "Begin converting to image..." << endl;
    // Save screenshot of image
    std::cerr << "P3\n"
              << WIDTH << ' ' << HEIGHT << "\n255\n";

    for (int j = 0; j < HEIGHT; ++j)
    {
        for (int i = 0; i < WIDTH; ++i)
        {
            auto r = img->pixelArr[j][i].x;
            auto g = img->pixelArr[j][i].y;
            auto b = img->pixelArr[j][i].z;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cerr << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    cout << "Finished converting to image" << endl;
}
