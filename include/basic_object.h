/*  This file is a part of G2 - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    G2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    G2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of G2.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef BASICOBJECT_H
#define BASICOBJECT_H
#include "color.h"
#include "point.h"
#include <string>
#include <map>

//This is the base class for all other object types. A basic object stores information about size and appearance.
class basic_object
{
protected:
    point2f position;
    int number;
    float rotation;
    int width;
    int height;
    int marker_width;
    int marker_height;
    int xmax,xmin,ymax,ymin;//the boundaries of the object
    std::string texture;
    std::string mask;
    std::map<std::string,int> properties;
public:
    static int total_objects;//total number of objects. This is used to assign the object number
    static point2i default_position;//point where a new object is created
    virtual std::string get_type();//returns the object type
    virtual void render_shape();//draw the object's shape
    virtual void render();//draws the object
    virtual void update();//update CPU-regulated functions
    virtual void sync();//update clock-regulated functions
    virtual void save();//save object data to file
    virtual void load();//load object data from file
    virtual void mark_selected();//visually indicate that the object is selected
    virtual void rotate(float angle);//increments the object's rotation by the given angle
    virtual void set_rotation(float angle);//changes the object's rotation to the given angle
    virtual void calc_boundaries();//calculates the max's and mins
    point2f get_position();
    point2f* get_positionptr();
    color fill_color;//color of the body of the object
    color marker_color;//color of selection marker
    color border_color;//color of the border
    const char* file_name;
    int get_number();//returns the object number
    int get_width();
    int get_height();
    float get_x();
    float get_y();
    float get_radius();//returns the distance from the center to the outermost point of the object
    float get_rotation();//returns the current rotation of the object
    std::string get_texture();//returns the texture filename
    bool filled;//whether the body of the object is visible
    bool bordered;//whether or not the object has a border
    bool textured;//whether the object has a texture
    bool masked;//whether the object's texture is masked (has a matching silhouette texture)
    bool visible;//whether the object should be shown or not
    bool selected;//whether the object has been selected or not
    bool muted;//whether the object should make sound or not
    void show();//make the object visible
    void hide();//make the object invisible
    void mute();//make the object inaudible
    void unmute();//make the object audible
    void render_border();//draw the border
    void render_texture();//apply the texture
    void set_position(int x, int y);
    void set_dimensions(int w, int h);
    void set_texture(std::string filename);
    void set_mask(std::string filename);
    void set_property(std::string name, int value);
    void add_property(std::string name, int value);
    basic_object();
    basic_object(int x, int y, int w, int h);
    basic_object(int x, int y, int w, int h, color c);
    virtual ~basic_object();
};
#endif // BASICOBJECT_H
