/**************************************************
Obj is subclass class of Geometry
that loads an obj file.
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Geometry.h"
#include "rtx_source/Triangle.h"
#ifndef __OBJ_H__
#define __OBJ_H__

class Obj : public Geometry
{
public:
    void init(const char *filename);

    Intersection Intersect(Ray ray, Material *material);
};

#endif
