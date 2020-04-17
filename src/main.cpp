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
#include "Managers/GlobalManager.h"
#include "Scene.h"
#include "ColorPicker/ColorPickerPanel.h"
#include "Slider/Slider.h"
#include "Vectors/Float3.h"

using namespace std;

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
   initCanvas(GlobalManager::getInstance()->screenWidth, GlobalManager::getInstance()->screenHeight, "VectorFigures");
   Scene *scene = new Scene();
   ColorPickerPanel* picker = new ColorPickerPanel({10,10,0},{250,250,0},{0.3,0.3,0.3});
   //ColorSlider* slider = new ColorSlider({300,300,0},10,200);
   //slider->setColors({0,0,0},{1,0,0});
   runCanvas();
}
