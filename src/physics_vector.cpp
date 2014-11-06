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

#include "physics_vector.h"

void physics_vector::set(float x_direction, float y_direction)
{
    x=x_direction;
    y=y_direction;
}

void physics_vector::set(float x_direction, float y_direction, float magnitude)
{
    x=x_direction;
    y=y_direction;
    m=magnitude;
}

physics_vector::physics_vector()
{
    x=0.0f;
    y=0.0f;
    m=0.0f;
}

physics_vector::physics_vector(float x_direction, float y_direction)
{
    x=x_direction;
    y=y_direction;
    m=1.0f;
}

physics_vector::physics_vector(float x_direction, float y_direction, float magnitude)
{
    x=x_direction;
    y=y_direction;
    m=magnitude;
}
