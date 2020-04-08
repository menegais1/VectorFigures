/// Main class of the program, used for registering the callbacks
/// in GLUT, initialize the window, call the GlobalManager functions
/// and instantiate the program main manager

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include <string>
#include <iostream>
#include <cmath>
#include "Canvas/gl_canvas2d.h"
#include "Utilities.h"
#include "Button/Button.h"
#include "Managers/GlobalManager.h"
#include "Vector4.h"

using namespace std;
int screenWidth = 600, screenHeight = 600;

void render()
{
   GlobalManager::getInstance()->render();
}

void keyboard(int key)
{
   GlobalManager::getInstance()->keyboard(key);
}

void keyboardUp(int key)
{
   GlobalManager::getInstance()->keyboardUp(key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   GlobalManager::getInstance()->mouse(button, state, wheel, direction, x, y);
}

int main(void)
{
   initCanvas(&screenWidth, &screenHeight, "BitmapReader");
   Vector4 test(1,2,3,4);
   for(int i =0; i< 4;i++){
      cout << test[i] << endl;;
   }
   runCanvas();
}
