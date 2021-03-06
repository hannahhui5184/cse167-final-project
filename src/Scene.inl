/**************************************************
Scene.inl contains the definition of the scene graph
*****************************************************/
#include "../lib/Scene.h"
#include "../lib/Cube.h"
#include "../lib/Geometry.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace glm;
void Scene::init(void)
{
    // Create a geometry palette
    // geometry["cube"] = new Geometry;
    geometry["teapot"] = new Geometry;
    geometry["bunny"] = new Geometry;
    geometry["triangle"] = new Geometry;
    // geometry["cube"]->init("models/teapot.obj");
    geometry["teapot"]->init("models/teapot.obj");
    geometry["bunny"]->init("models/bunny.obj");

    vec3 p1(0.0f, 0.0f, 0.0f);
    vec3 p2(1.0f, 0.0f, 0.0f);
    vec3 p3(1.0f, 2.0f, 0.0f);

    vec3 norm = normalize(cross(p3 - p1, p3 - p2));
    mat3 points = mat3x3(p1, p2, p3);
    mat3 norms = mat3x3(norm, norm, norm);
    geometry["triangle"]->init(points, norms);

    // Create a material palette
    material["wood"] = new Material;
    material["wood"]->ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    material["wood"]->diffuse = vec4(0.3f, 0.15f, 0.1f, 1.0f);
    material["wood"]->specular = vec4(0.3f, 0.15f, 0.1f, 1.0f);
    material["wood"]->shininess = 100.0f;

    material["ceramic"] = new Material;
    material["ceramic"]->ambient = vec4(0.02f, 0.07f, 0.2f, 1.0f);
    material["ceramic"]->diffuse = vec4(0.1f, 0.25f, 0.7f, 1.0f);
    material["ceramic"]->specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["ceramic"]->shininess = 150.0f;

    material["silver"] = new Material;
    material["silver"]->ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    material["silver"]->diffuse = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    material["silver"]->specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["silver"]->shininess = 50.0f;

    material["turquoise"] = new Material;
    material["turquoise"]->ambient = vec4(0.1f, 0.2f, 0.17f, 1.0f);
    material["turquoise"]->diffuse = vec4(0.2f, 0.375f, 0.35f, 1.0f);
    material["turquoise"]->specular = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    material["turquoise"]->shininess = 100.0f;

    material["bulb"] = new Material;
    material["bulb"]->ambient = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"]->diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"]->specular = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    material["bulb"]->emision = vec4(1.0f, 0.2f, 0.1f, 1.0f);
    material["bulb"]->shininess = 200.0f;

    material["brass"] = new Material;
    material["brass"]->ambient = vec4(0.329412f, 0.223529f, 0.027451f, 1.0f);
    material["brass"]->diffuse = vec4(0.780392f, 0.568627f, 0.113725f, 1.0f);
    material["brass"]->specular = vec4(0.992157f, 0.941176f, 0.807843f, 1.0f);
    material["brass"]->shininess = 0.21794872;

    material["obsidian"] = new Material;
    material["obsidian"]->ambient = vec4(0.05375f, 0.05f, 0.06625f, 1.0f);
    material["obsidian"]->diffuse = vec4(0.18275f, 0.17f, 0.22525f, 1.0f);
    material["obsidian"]->specular = vec4(0.332741f, 0.328634f, 0.346435f, 1.0f);
    material["obsidian"]->shininess = 0.3;


    // Create a model palette
    model["teapot1"] = new Model;
    model["teapot1"]->geometry = geometry["teapot"];
    model["teapot1"]->material = material["silver"];
    model["teapot2"] = new Model;
    model["teapot2"]->geometry = geometry["teapot"];
    model["teapot2"]->material = material["ceramic"];
    // model["table piece"] = new Model;
    // model["table piece"]->geometry = geometry["cube"];
    // model["table piece"]->material = material["turquoise"];
    model["bunny"] = new Model;
    model["bunny"]->geometry = geometry["bunny"];
    model["bunny"]->material = material["turquoise"];
    // model["bulb"] = new Model;
    // model["bulb"]->geometry = geometry["cube"];
    // model["bulb"]->material = material["bulb"];
    model["bunny1"] = new Model;
    model["bunny1"]->geometry = geometry["bunny"];
    model["bunny1"]->material = material["brass"];
    model["bunny2"] = new Model;
    model["bunny2"]->geometry = geometry["bunny"];
    model["bunny2"]->material = material["silver"];
    model["triangle"] = new Model;
    model["triangle"]->geometry = geometry["triangle"];
    model["triangle"]->material = material["silver"];

    // Create a light palette
    light["sun"] = new Light;
    light["sun"]->position = vec4(3.0f, 2.0f, 1.0f, 0.0f);
    light["sun"]->color = 0.3f * vec4(0.5f, 0.5f, 0.5f, 0.5f);

    light["bulb"] = new Light;
    light["bulb"]->position = vec4(0.0f, 2.0f, 0.0f, 0.0f);
    light["bulb"]->color = 1.0f * vec4(1.0f, 0.2f, 0.1f, 1.0f);

    // Build the scene graph
    node["world"] = new Node;
    node["bunny1"] = new Node;
    node["bunny2"] = new Node;
    // node["table"] = new Node;
    // node["table top"] = new Node;
    // node["table leg"] = new Node;
    // node["table side"] = new Node;
    // node["table back"] = new Node;
    node["teapot1"] = new Node;
    node["teapot2"] = new Node;
    node["bunny"] = new Node;
    node["triangle"] = new Node;


    // node["table"]->childnodes.push_back(node["table top"]);
    // node["table"]->childtransforms.push_back(translate(vec3(0.0f, 0.0f, 0.0f)));
    // node["table"]->childnodes.push_back(node["table leg"]);
    // node["table"]->childtransforms.push_back(translate(vec3(-0.9f, -0.7f, -0.4f)));
    // node["table"]->childnodes.push_back(node["table leg"]);
    // node["table"]->childtransforms.push_back(translate(vec3(-0.9f, -0.7f, 0.4f)));
    // node["table"]->childnodes.push_back(node["table leg"]);
    // node["table"]->childtransforms.push_back(translate(vec3(0.9f, -0.7f, 0.4f)));
    // node["table"]->childnodes.push_back(node["table leg"]);
    // node["table"]->childtransforms.push_back(translate(vec3(0.9f, -0.7f, -0.4f)));
    // node["table"]->childnodes.push_back(node["table side"]);
    // node["table"]->childtransforms.push_back(translate(vec3(0.95f, 0.0f, 0.0f)));
    // node["table"]->childnodes.push_back(node["table side"]);
    // node["table"]->childtransforms.push_back(translate(vec3(-0.95f, 0.0f, 0.0f)));
    // node["table"]->childnodes.push_back(node["table back"]);
    // node["table"]->childtransforms.push_back(translate(vec3(0.0f, 0.3f, -0.45f)));

    // node["table leg"]->models.push_back(model["table piece"]);
    // node["table leg"]->modeltransforms.push_back(translate(vec3(0.0f, 0.5f, 0.0f)) * scale(vec3(0.1f, 0.2f, 0.2f)));

    // node["table side"]->models.push_back(model["table piece"]);
    // node["table side"]->modeltransforms.push_back(translate(vec3(0.0f, 0.3f, 0.0f)) * scale(vec3(0.1f, 0.8f, 1.0f)));

    // node["table back"]->models.push_back(model["table piece"]);
    // node["table back"]->modeltransforms.push_back(translate(vec3(0.0f, 0.0f, 0.0f)) * scale(vec3(2.0f, 0.8f, 0.1f)));

    // node["table top"]->models.push_back(model["table piece"]);
    // node["table top"]->modeltransforms.push_back(translate(vec3(0.0f, -0.1f, 0.0f)) * scale(vec3(2.0f, 0.1f, 1.0f)));
    // node["table top"]->childnodes.push_back(node["teapot1"]);
    // node["table top"]->childtransforms.push_back(translate(vec3(-0.5f, 0.0f, 0.0f)));
    // node["table top"]->childnodes.push_back(node["teapot2"]);
    // node["table top"]->childtransforms.push_back(translate(vec3(0.5f, 0.0f, 0.0f)) * rotate(-120.0f * float(M_PI) / 180.0f, vec3(0.0f, 1.0f, 0.0f)));

    /*
    node["teapot1"] -> models.push_back( model["teapot1"] );
    node["teapot1"] -> modeltransforms.push_back( scale(vec3(0.5f)) );
    node["teapot2"] -> models.push_back( model["teapot2"] );
    node["teapot2"] -> modeltransforms.push_back( scale(vec3(1.0f,1.5f,1.0f)) * scale(vec3(0.5f)) );
    */

    node["triangle"]->models.push_back(model["triangle"]);
    node["triangle"]->modeltransforms.push_back(scale(vec3(1.2f)) * translate(vec3(0.0f, 1.0f, 0.0f)));

    node["teapot1"] -> models.push_back( model["teapot1"] );
    node["teapot1"] -> modeltransforms.push_back( scale(vec3(0.5f)) );
    node["teapot2"] -> models.push_back( model["teapot2"] );
    node["teapot2"] -> modeltransforms.push_back( scale(vec3(1.0f,1.5f,1.0f)) * scale(vec3(0.5f)) );
    
    // node["bunny"] -> models.push_back( model["bunny"] );
    // node["bunny"] -> modeltransforms.push_back( scale(vec3(0.8f)) * translate(vec3(0.0f,1.0f,0.0f)) );
    
    node["world"] -> childnodes.push_back( node["teapot1"] );
    node["world"] -> childtransforms.push_back( translate(vec3(-0.3f,1.0f,0.0f))* rotate( 180.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f)) );
    node["world"] -> childnodes.push_back( node["teapot2"] );
    node["world"] -> childtransforms.push_back( translate(vec3( 0.5f,1.0f,0.0f)) * rotate( -120.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );


    // BUNNIES HERE TODO:
    // node["bunny1"]->models.push_back(model["bunny1"]);
    // node["bunny1"]->modeltransforms.push_back(scale(vec3(0.2f)) * translate(vec3(0.0f, 0.7f, 0.0f)));


    // node["bunny2"]->models.push_back(model["bunny2"]);
    // node["bunny2"]->modeltransforms.push_back(scale(vec3(0.3f)) * translate(vec3(0.0f, 0.7f, 0.0f)));


    // node["world"]->childnodes.push_back(node["table"]);
    // node["world"]->childtransforms.push_back(mat4(1.0f));

    node["world"]->childnodes.push_back(node["triangle"]);
    node["world"]->childtransforms.push_back(translate(vec3(-1.0f,-0.5f,0.0f)) * rotate(60.0f * float(M_PI) / 180.0f, vec3(0.0f, 1.0f, 0.0f)));

    // node["world"]->childnodes.push_back(node["bunny1"]);
    // node["world"]->childtransforms.push_back(translate(vec3(0.3f, 0.0f, 0.0f)) * rotate(40.0f * float(M_PI) / 180.0f, vec3(0.0f, 1.0f, 0.0f)));


    // node["world"]->childnodes.push_back(node["bunny2"]);
    // node["world"]->childtransforms.push_back(translate(vec3(0.0f, 0.0f, 0.0f)) * rotate(70.0f * float(M_PI) / 180.0f, vec3(0.0f, 1.0f, 0.0f)));
    /*
    node["world"] -> models.push_back( model["bulb"] );
    node["world"] -> modeltransforms.push_back( translate(vec3(0.0f,2.0f,0.0f))*scale(vec3(0.1f)) );
    */

    // TRIANGLE HERE TODO:
    // node["triangle"]->models.push_back(model["triangle"]);
    // node["triangle"]->modeltransforms.push_back(translate(vec3(0.0f, 1.0f, 5.0f)));
    // node["world"]->childnodes.push_back(node["triangle"]);
    // node["world"]->childtransforms.push_back(mat4(1.0f));
    // Put a camera
    camera = new Camera;
    camera->target_default = vec3(0.0f, 1.0f, 0.0f);
    camera->eye_default = vec3(0.0f, 1.0f, 5.0f);
    camera->up_default = vec3(0.0f, 1.0f, 0.0f);
    camera->reset();
}
