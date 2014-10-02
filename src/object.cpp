/*  This file is a part of 2DWorld - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    2DWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    2DWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of 2DWorld.  If not, see <http://www.gnu.org/licenses/>.*/

#include "object.h"
#include "window.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <iostream>
//initialize static variable
int object::total_objects=0;

void object::set_boundaries()//calculates the limits of the object
{
    //these two variables store reused data in order to save calculations
    float half_width=width/2;
    float half_height=height/2;
    xmin= current.x-half_width;
    xmax= current.x+half_width;
    ymin= current.y-half_height;
    ymax= current.y+half_height;
    radius=(half_width+half_height)/2;
}

void object::render()//draws the object
{
    glPushMatrix();//need push and pop so that entire scene isn't rotated
    glTranslatef(current.x,current.y,0.0);//translate object according to coordinates
    glRotatef(rotation,0,0,1);//rotates object with object.rotation
    glTranslatef(-current.x,-current.y,0.0);//translate object according to coordinates
    glColor3f(primary_color.r,primary_color.g,primary_color.b);//color the square with object.primary_color

    if(!rendered)
    {
        std::clog<<"object#"<<number<<": "<<name<<" rendered."<<std::endl;
        rendered=true;
    }
    if(visible)
    {
        glBegin(GL_POLYGON);//draws a filled in rectangle
        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner
        glEnd();//finish drawing
        glPopMatrix();//reset transformation matrix
    }
}

void object::rotate(float angle)
{
    rotation+=angle;
}

void object::update()
{
    set_boundaries();
}

object::object()//constructs an object
{
    name="unnamed";
    type="object";
    number=total_objects;
    total_objects++;
    current.set(window::width/2,window::height/2);
    rest.set(current.x,current.y);
    width=64;
    height=64;
    set_boundaries();
    primary_color.set(0.0,0.0,0.0);
    rotation=90;
    rest_rotation=90;
    visible=true;
    rendered=false;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created."<<std::endl;
}

object::object(float x, float y, float w, float h, color c)
{
    name="unnamed";
    type="object";
    number=total_objects;
    total_objects++;
    current.x=x;
    current.y=y;
    rest.x=x;
    rest.y=y;
    width=w;
    height=h;
    set_boundaries();
    primary_color.set(c);
    rotation=90.1;
    rest_rotation=90.1;
    visible=true;
    rendered=false;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created."<<std::endl;
}
