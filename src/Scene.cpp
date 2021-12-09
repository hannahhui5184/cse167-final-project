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

                Triangle *worldTri = new Triangle;
                //TODO: check this, the math might be wrong
                worldTri->points = glm::mat3(cur_VM * (cur->modeltransforms[i]) * p_mat);
                worldTri->norms = n_vm * norms;
                worldTri->material = (cur->models[i])->material;

                this->worldTriangles.push_back(worldTri);
            }
        }

        // Continue the DFS: put all the child nodes of the current node in the stack
        for (unsigned int i = 0; i < cur->childnodes.size(); i++)
        {
            dfs_stack.push(cur->childnodes[i]);
            // (HW3 hint: you should do something here)
            matrix_stack.push(cur_VM * (cur->childtransforms[i]));
        }

    } // End of DFS while loop.
}
