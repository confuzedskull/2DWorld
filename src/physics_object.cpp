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

#include "physics_object.h"
#include "game.h"
#include <iostream>
#include <math.h>

void physics_object::set_resting()
{
    if(!moving_horizontal())
        rest.x=current.x;

    if(!moving_vertical())
        rest.y=current.y;

    if(!turning())
        rest_rotation=rotation;
}

void physics_object::calc_delta_time()
{
    if(!isless(current.x,rest.x)&&!isgreater(current.x,rest.x))//x-position is not changing
    {
        stop_time[0]=game::time;
        delta_time[0]=0.0f;
    }
    else
    {
        start_time[0]=game::time;
        delta_time[0]=stop_time[0]-start_time[0];
    }

    if(!isless(current.y,rest.y)&&!isgreater(current.y,rest.y))//y-position is not changing
    {
        stop_time[1]=game::time;
        delta_time[1]=0.0f;
    }
    else
    {
        start_time[1]=game::time;
        delta_time[1]=stop_time[1]-start_time[1];
    }

    if(!moving_horizontal())//x-velocity is not changing
    {
        stop_time[2]=game::time;
        delta_time[2]=0.0f;
    }
    else
    {
        start_time[2]=game::time;
        delta_time[2]=stop_time[2]-start_time[2];
    }

    if(!moving_vertical())//y-velocity is not changing
    {
        stop_time[3]=game::time;
        delta_time[3]=0.0f;
    }
    else
    {
        start_time[3]=game::time;
        delta_time[3]=stop_time[3]-start_time[3];
    }

    if(!isless(rotation,rest_rotation) && !isgreater(rotation,rest_rotation))//rotation is not changing
    {
        stop_time[4]=game::time;
        delta_time[4]=0.0f;
    }
    else
    {
        start_time[4]=game::time;
        delta_time[4]=stop_time[4]-start_time[4];
    }

    if(!turning())//angular velocity is not changing
    {
        stop_time[5]=game::time;
        delta_time[5]=0.0f;
    }
    else
    {
        start_time[5]=game::time;
        delta_time[5]=stop_time[5]-start_time[5];
    }
}
void physics_object::calc_velocity()
{
    if(isnormal(delta_time[0]))
        velocity[0].x=(rest.x-current.x)/delta_time[0];

    if(isnormal(delta_time[1]))
        velocity[0].y=(rest.y-current.y)/delta_time[1];

    if(isnormal(delta_time[4]))
        angular_velocity[0]=(rest_rotation-rotation)/delta_time[4];
}

void physics_object::calc_acceleration()
{
    if(isnormal(delta_time[2]))
        acceleration.x=(velocity[0].x-velocity[1].x)/delta_time[2];

    if(isnormal(delta_time[3]))
        acceleration.y=(velocity[0].y-velocity[1].y)/delta_time[3];

    if(isnormal(delta_time[5]))
        angular_acceleration=(angular_velocity[0]-angular_velocity[1])/delta_time[5];
}

void physics_object::calc_force()
{
    force.x=mass*acceleration.x;
    force.y=mass*acceleration.y;
}

void physics_object::calc_momentum()
{
    momentum.x=mass*velocity[0].x;
    momentum.y=mass*velocity[0].y;
    angular_momentum=mass*angular_velocity[0];
    velocity[1].x=velocity[0].x+momentum.x;
    velocity[1].y=velocity[0].y+momentum.y;
    angular_velocity[1]=angular_velocity[0]+angular_momentum;
}
//calculate momentum after elastic collision with object p
void physics_object::calc_momentum(physics_object p)
{
    momentum.x=momentum.x+p.momentum.x-(p.mass*p.velocity[1].x);
    momentum.y=momentum.y+p.momentum.y-(p.mass*p.velocity[1].y);
}

void physics_object::inertia()
{
    current.x+=momentum.x;
    if(isnormal(momentum.x))
    {
        moving_left=true;
        moving_right=true;
    }
    current.y+=momentum.y;
    if(isnormal(momentum.y))
    {
        moving_forward=true;
        moving_backward=true;
    }
    rotation+=angular_momentum;
    if(isnormal(angular_momentum))
    {
        turning_left=true;
        turning_right=true;
    }
}

void physics_object::physics()
{
    set_resting();
    set_boundaries();
    calc_direction();
    calc_points();
    calc_delta_time();
    calc_velocity();
    calc_acceleration();
    calc_momentum();
    calc_force();
    reset_motion();
}

physics_object::physics_object()
{
    name="physics object";
    mass=0.015f;//If this is too high, objects might just disappear off the screen
    velocity[0].x=0.0f;
    velocity[0].y=0.0f;
    angular_velocity[0]=0.0f;
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
}
