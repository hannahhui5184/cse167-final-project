
#include <stdlib.h>

/**
 * 
 */
Image Raytrace(Camera cam, Scene scene, int width, int height)
{
    Image image = new Image(width, height);
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            Ray ray = RayThruPixel(cam, i, j);
            Intersection hit = Intersect(ray, scene);
            image[i][j] = FindColor(hit);
        }
    }
    return image;
}

/**
 * RayThruPixel
 * @param Camera 
 * @param int
 * @param int
 * @return Ray 
 */
Ray RayThruPixel(Camera cam, int i, int j)
{
    return nullptr;
}

/**
 * Intersect
 * @param Ray
 * @param Scene
 * @return Intersection
 */
Intersection Intersect(Ray ray, Scene scene)
{
    Distance mindist = INFINITY;
    Intersection hit;
    foreach (object in scene)
    { // Find closest intersection; test all objects
        Intersection hit_temp = object.Intersect(ray);
        if (hit_temp.dist < mindist)
        { // closer than previous hit
            mindist = hit_temp.dist;
            hit = hit_temp;
        }
    }
    return hit;
}

/**
 * FindColor
 * @param Intersection
 * @return vec3
 */
glm : vec3 FindColor(Intersection hit)
{
    // Lambert diffuse light (like HW3)
    // Run through all the light and take the dot product
    // between the normal and the light direction

    // Recursive mirror reflection
}
