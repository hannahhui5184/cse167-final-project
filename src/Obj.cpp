/**************************************************
Obj is subclass class of Geometry
that loads an obj file.
 This obj file loader only supports vertex positions and normals:
 v   x y z
 vn nx ny nz
 f 123//456
 i.e. there is no texture.
*****************************************************/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

#include "../lib/Obj.h"

void Obj::init(const char *filename)
{
    std::vector<glm::vec3> temp_vertices, vertices;
    std::vector<glm::vec3> temp_normals, normals;
    std::vector<unsigned int> temp_vertexIndices, indices;
    std::vector<unsigned int> temp_normalIndices;

    // load obj file
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        std::cerr << "Cannot open file: " << filename << std::endl;
        exit(-1);
    }
    std::cout << "Loading " << filename << "...";
    while (!feof(file))
    {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader
        if (strcmp(lineHeader, "v") == 0)
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            //std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], normalIndex[3];
            fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
            temp_vertexIndices.push_back(vertexIndex[0]);
            temp_vertexIndices.push_back(vertexIndex[1]);
            temp_vertexIndices.push_back(vertexIndex[2]);
            temp_normalIndices.push_back(normalIndex[0]);
            temp_normalIndices.push_back(normalIndex[1]);
            temp_normalIndices.push_back(normalIndex[2]);
        }
    }
    std::cout << "done." << std::endl;

    // post processing
    std::cout << "Processing data...";
    unsigned int n = temp_vertexIndices.size(); // #(triangles)*3
    vertices.resize(n);
    normals.resize(n);
    indices.resize(n);
    for (unsigned int i = 0; i < n; i++)
    {
        indices[i] = i;
        vertices[i] = temp_vertices[temp_vertexIndices[i] - 1];
        normals[i] = temp_normals[temp_normalIndices[i] - 1];
    }
    std::cout << "done." << std::endl;

    // setting up buffers
    std::cout << "Setting up buffers...";
    for (unsigned int k = 0; k < n / 3; k++)
    {
        Triangle tri;
        tri.points[0] = vertices[k * 3];
        tri.points[1] = vertices[k * 3 + 1];
        tri.points[2] = vertices[k * 3 + 2];

        tri.norms[0] = normals[k * 3];
        tri.norms[1] = normals[k * 3 + 1];
        tri.norms[2] = normals[k * 3 + 2];

        triangles.push_back(&tri);
    }
    std::cout << "done." << std::endl;
}

/**
 * @brief Finds the closest intersection among the triangles of the object.
 * 
 * @param ray ray that is intersecting
 * @param material material of the object (all object triangles will have the same material)
 * @return Intersection returns the closest intersection to the ray source
 */
Intersection Obj::Intersect(Ray ray, Material *material)
{
    float mindist = FLT_MAX;
    Intersection hit;
    for (Triangle *tri : Obj::worldTriangles)
    {
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
