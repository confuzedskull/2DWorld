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

#ifndef OBJECT_H
#define OBJECT_H
#include "color.h"
#include "point.h"
#include <string>

//This is the base class for all other object types. It has basic properties such as name, color, and dimensions.
class object
{
protected:
    int number;
    point2i position;
    float rotation;
    int width;
    int height;
    int marker_width;
    int marker_height;
    float radius;
    int xmax,xmin,ymax,ymin;//the boundaries of the object
public:
    static int total_objects;//total number of objects. This is used to assign the object number
    static point2i origin;
    virtual std::string get_type();
    virtual void render();//draws the object
    virtual void update();
    virtual void mark_selected();//visually indicate that the object is selected
    virtual void set_dimensions(int w, int h);
    const char* file_name;
    int get_number();
    point2i get_position();
    point2i* get_positionptr();
    float get_rotation();
    int get_width();
    int get_height();
    float get_radius();
    color fill_color;
    color marker_color;//color of marker when object is selected
    color border_color;//the color of the border
    bool filled;
    bool bordered;//whether or not a border should be shown
    bool visible;//whether the object should be shown or not
    bool selected;//whether the object has been selected or not
    bool enabled;//whether the object should be updated or not
    void rotate(float angle);//changes the object's rotation by the given angle
    void set_position(int x, int y);
    void set_rotation(float angle);
    void calc_boundaries();//calculates the max's and mins
    void show();//make the object visible
    void hide();//make the object invisible
    void render_shape();//draw the object's shape
    void render_border();//draw the border
    object();
    object(int x, int y, int w, int h);
    object(int x, int y, int w, int h, color c);
    virtual ~object();
};
#endif // OBJECT_H
