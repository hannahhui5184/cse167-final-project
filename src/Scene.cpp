/**************************************************
Scene.cpp contains the implementation of the draw command
*****************************************************/
#include <stdlib.h>
#include <iostream>
#include "../lib/Scene.h"
#include "../lib/Cube.h"
#include "../lib/Obj.h"
#include "../lib/Geometry.h"
#include <glm/gtx/string_cast.hpp>

// The scene init definition
#include "Scene.inl"

using namespace glm;
void Scene::draw(void)
{
    // Pre-draw sequence: assign uniforms that are the same for all Geometry::draw call.  These uniforms include the camera view, proj, and the lights.  These uniform do not include modelview and material parameters.
    camera->computeMatrices();
    // shader->view = camera->view;
    // shader->projection = camera->proj;
    // shader->nlights = light.size();
    // shader->lightpositions.resize(shader->nlights);
    // shader->lightcolors.resize(shader->nlights);
    // int count = 0;
    // for (std::pair<std::string, Light *> entry : light)
    // {
    //     shader->lightpositions[count] = (entry.second)->position;
    //     shader->lightcolors[count] = (entry.second)->color;
    //     count++;
    // }

    // Define stacks for depth-first search (DFS)
    std::stack<Node *> dfs_stack;
    std::stack<mat4> matrix_stack; // HW3: You will update this matrix_stack during the depth-first search while loop.

    // Initialize the current state variable for DFS
    Node *cur = node["world"]; // root of the tree
    //TODO: Need to make it start at the world view matrix... identity matrix?
    mat4 cur_VM = camera->view; // HW3: You will update this current modelview during the depth first search.  Initially, we are at the "world" node, whose modelview matrix is just camera's view matrix.

    // HW3: The following is the beginning of the depth-first search algorithm.
    // HW3: The depth-first search for the node traversal has already been implemented (cur, dfs_stack).
    // HW3: All you have to do is to also update the states of (cur_VM, matrix_stack) alongside the traversal.  You will only need to modify starting from this line.
    dfs_stack.push(cur);
    matrix_stack.push(cur_VM);

    while (!dfs_stack.empty())
    {
        // Detect whether the search runs into infinite loop by checking whether the stack is longer than the size of the graph.
        // Note that, at any time, the stack does not contain repeated element.
        if (dfs_stack.size() > node.size())
        {
            std::cerr << "Error: The scene graph has a closed loop." << std::endl;
            exit(-1);
        }

        // top-pop the stacks
        cur = dfs_stack.top();
        dfs_stack.pop();
        // (HW3 hint: you should do something here)
        cur_VM = matrix_stack.top();
        matrix_stack.pop();

        // draw all the models at the current node
        for (unsigned int i = 0; i < cur->models.size(); i++)
        {
            // Prepare to draw the geometry. Assign the modelview and the material.

            // (HW3 hint: you should do something here)
            // shader->modelview = cur_VM * (cur->modeltransforms[i]); // HW3: Without updating cur_VM, modelview would just be camera's view matrix.
            // shader->material = (cur->models[i])->material;

            // // The draw command
            // shader->setUniforms();
            // (cur->models[i])->geometry->draw();

            vector<Triangle *> triangles = cur->models[i]->geometry->triangles;
            vector<Triangle *> transformed;

            for (Triangle *tri : triangles)
            {
                // std::cout << "Triangles: " << glm::to_string(tri->points) << endl;
                glm::mat3x3 points = tri->points;
                glm::mat3x3 norms = tri->norms;

                glm::mat3x4 p_mat(glm::vec4(points[0], 1.0f),
                                  glm::vec4(points[1], 1.0f),
                                  glm::vec4(points[2], 1.0f));

                glm::mat3x3 n_vm = glm::inverse(glm::transpose(glm::mat3(cur_VM * (cur->modeltransforms[i]))));

                Triangle* worldTri = new Triangle;
                //TODO: check this, the math might be wrong
                worldTri->points = glm::mat3(cur_VM * (cur->modeltransforms[i]) * p_mat);
                worldTri->norms = n_vm * norms;
                worldTri->material = (cur->models[i])->material;

                this->worldTriangles.push_back(worldTri);
            }

            //TODO: Minghui's implementation
            // glm::mat3 transformed_view = inverse(transpose(mat3(camera->view)));
            // for (auto it = triangles.begin(); it != triangles.end(); i++)
            // {
            //     Triangle tri;
            //     tri.points[0] = glm::mat3(camera->view) * (triangles[i]->points)[0];
            //     tri.points[1] = glm::mat3(camera->view) * (triangles[i]->points)[1];
            //     tri.points[2] = glm::mat3(camera->view) * (triangles[i]->points)[2];
            //     tri.norms[0] = transformed_view * (triangles[i]->norms)[0];
            //     tri.norms[1] = transformed_view * (triangles[i]->norms)[1];
            //     tri.norms[2] = transformed_view * (triangles[i]->norms)[2];
            //     cur->models[i]->geometry->worldTriangles.push(tri);
            // }
            // glm::vec3 transformed_norm3 = transformed_view * (triangles[i]->norms)[2];
        }

        // Continue the DFS: put all the child nodes of the current node in the stack
        for (unsigned int i = 0; i < cur->childnodes.size(); i++)
        {
            dfs_stack.push(cur->childnodes[i]);
            // (HW3 hint: you should do something here)
            matrix_stack.push(cur_VM * (cur->childtransforms[i]));
        }

    } // End of DFS while loop.
    // HW3: Your code will only be above this line.
}
