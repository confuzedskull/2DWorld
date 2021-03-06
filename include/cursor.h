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

#ifndef CURSOR_H
#define CURSOR_H
#include "point.h"
#include "color.h"
#include "basic_object.h"
#include "game.h"
#include <map>

//The cursor class stores data from the mouse that it's interfaced with. Since there can only be one mouse, all the data is static.
class cursor
{
public:
    static color box_color;//RGB values
    static point2i passive;
    static point2i left_down;
    static point2i left_up;
    static point2i left_drag;
    static point2i right_down;
    static point2i right_up;
    static point2i right_drag;
    static interactive_object* left_clicked_object;
    static interactive_object* right_clicked_object;
    static bool left_clicking;
    static bool left_dragging;
    static bool right_clicking;
    static bool right_dragging;
    static bool highlighting;
    static bool highlighting_enabled;
    static std::map<int,interactive_object*> selected_objects;
    static int xmin,xmax,ymin,ymax;
    static int selected_object;
    static int objects_selected();
    static void calc_boundaries();
    static void render_box();
    static void reset();
};
#endif // CURSOR_H
