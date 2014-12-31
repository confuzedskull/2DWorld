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

#ifndef COMPLEX_H
#define COMPLEX_H
#include "basic_object.h"
#include "point.h"
#include "physics_vector.h"

//A complex object consists of a number of points which are calculated based on the object's position and rotation
class complex_object: virtual public basic_object
{
protected:
    //headings for each direction
    physics_vector leftward;
    physics_vector rightward;
    physics_vector forward;
    physics_vector backward;
public:
    //the mid-point of each side
    point2f front();
    point2f back();
    point2f left();
    point2f right();
    std::string get_type() override;
    void orient();//calculates each directional heading
    void rotate(float angle) override;//performs a rotation transformation based on the given angle
    void set_rotation(float angle) override;
    void mark_selected() override;
    void render() override;//makes the object visible on screen
    complex_object();
};
#endif // COMPLEX_H
