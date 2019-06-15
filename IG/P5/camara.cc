#include <GL/gl.h>
#include <vector>
#include <iostream>

using namespace std;

class camara{
   public:
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   GLfloat Window_width,Window_height,Front_plane,Back_plane;
   void setObservador(){
      glTranslatef(0,0,-Observer_distance);
      glRotatef(Observer_angle_x,1,0,0);
      glRotatef(Observer_angle_y,0,1,0);
   }
};
