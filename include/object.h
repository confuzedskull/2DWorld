#ifndef OBJECT_H
#define OBJECT_H
#include "color.h"
#include "point2f.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//This is the base class for all other object types. It has basic properties such as name, color, and dimensions.
class object
{
    public:
    static int total_objects;
    char* name;
    int number;
    point2f current;
    point2f rest;//resting point
    float rotation;
    float width, height;
    color primary_color;//RGB values
    bool visible;
    float xmax,xmin,ymax,ymin;//the boundaries of the object
    void set_boundaries();//calculates the max's and mins
    void render();//draws the object
    void rotate(float angle);//changes the object's rotation by the given angle
    int get_radius();//calculates a radius from the width and height
    object();
    object(float x, float y, float w, float h, color c);
};
#endif // OBJECT_H
