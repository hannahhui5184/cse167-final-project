/**************************************************
Geometry is an abstract class for a geometric object.
 A derived class of Geometry will have an implemention of
   ```void init(void)```
 or
   ```void init(const char* s).```
 The option for const char* input is for a derived class
 that requires reading external files.
 The implementation of the `init` is for initializing the
 geometry (i.e. setting up the buffers etc).
 
 The draw command is fixed.  We can call
 
 glBindVertexArray(obj.vao);
 glDrawElements(obj.mode, obj.count, obj.type, 0);
 
which should explain the purpose of those class members.
 We can also just call the "draw()" member function, which
 is equivalent to the commands above.
 
The array of buffers is encapsulated in std::vector so
we do not need to manually allocate/free the memory for
arrays of unknown size.
*****************************************************/
#include <vector>

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

// #include "rtx_source/Intersection.h"
// #include "rtx_source/Util.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Triangle.h"

using namespace std;

class Geometry
{
public:
  // GLenum mode = GL_TRIANGLES;    // the cookboook for glDrawElements
  // int count;                     // number of elements to draw
  // GLenum type = GL_UNSIGNED_INT; // type of the index array
  // GLuint vao;                    // vertex array object a.k.a. geometry spreadsheet
  // std::vector<GLuint> buffers;   // data storage

  vector<Triangle *> triangles;
  vector<Triangle *> worldTriangles;

  void init(){};
  // Init used by .obj files
  void init(const char *s);

  // Init used by triangle objects
  void init(glm::mat3 points, glm::mat3 norm);

  // Intersect overwritten by Triangle and Sphere
  Intersection Intersect(Ray ray, Material *material);

  // constructor 
  Geometry()
  {
    triangles = {};
    worldTriangles = {};
  }

  // destructor
  ~Geometry()
  {
  }
};

#endif
