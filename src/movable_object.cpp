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

#include "movable_object.h"
#include "distance.h"
#include "point2f.h"
#include "vector2f.h"
#include <math.h>
#include <queue>
#include <iostream>

std::queue< std::vector<int> > actions;

void movable_object::reset_motion()
{
    moving_forward=false;
    moving_backward=false;
    moving_left=false;
    moving_right=false;
    turning_left=false;
    turning_right=false;
}

bool movable_object::moving_vertical()
{
    if(moving_forward || moving_backward)
        return true;
    else
        return false;
}

bool movable_object::moving_horizontal()
{
    if(moving_left || moving_right)
        return true;
    else
        return false;
}

bool movable_object::turning()
{
    if(turning_left || turning_right)
        return true;
    else
        return false;
}

bool movable_object::moving()
{
    if(moving_forward||moving_backward||moving_left||moving_right)
        return true;
    else
        return false;
}

void movable_object::turn_right()
{
    turn_right(1.0f);
}

void movable_object::turn_right(float degrees)
{
    rotation-=speed*degrees;
    turning_right=true;
}

void movable_object::turn_left()
{
    turn_left(1.0f);
}

void movable_object::turn_left(float degrees)
{
    rotation+=speed*degrees;
    turning_left=true;
}

void movable_object::move_left()
{
    move_left(1.0f);
}

void movable_object::move_left(float units_left)
{
    current.x+=leftward.x*speed*units_left;
    current.y+=leftward.y*speed*units_left;
    moving_left=true;
}

void movable_object::move_right()
{
    move_right(1.0f);
}

void movable_object::move_right(float units_right)
{
    current.x+=rightward.x*speed*units_right;
    current.y+=rightward.y*speed*units_right;
    moving_right=true;
}

void movable_object::move_forward()
{
    move_forward(1.0f);
}

void movable_object::move_forward(float units_forward)
{
    current.x+=forward.x*speed*units_forward;
    current.y+=forward.y*speed*units_forward;
    moving_forward=true;
}

void movable_object::move_back()
{
    move_back(1.0f);
}

void movable_object::move_back(float units_back)
{
    current.x+=backward.x*speed*units_back;
    current.y+=backward.y*speed*units_back;
    moving_backward=true;
}

void movable_object::turn_to_point(float destination_x, float destination_y)//rotates object to face the given coordinates
{
    if(isgreater(distance(destination_x,destination_y,current.x,current.y),radius))//prevent infinite spin
    {
        if(isgreater(destination_x,current.x) && isgreater(destination_y,current.y))//destination lies in quadrant 1
            rotation = atan((destination_y-current.y)/(destination_x-current.x))*180.0f/3.14159f;

        if(isless(destination_x,current.x) && isgreater(destination_y,current.y))//destination lies in quadrant 2
            rotation = atan((destination_y-current.y)/(destination_x-current.x))*180.0f/3.14159f + 180.0f;

        if(isless(destination_x,current.x) && isless(destination_y,current.y))//destination lies in quadrant 3
            rotation = atan((destination_y-current.y)/(destination_x-current.x))*180.0f/3.14159f + 180.0f;

        if(isgreater(destination_x,current.x) && isless(destination_y,current.y))//destination lies in quadrant 4
            rotation = atan((destination_y-current.y)/(destination_x-current.x))*180.0f/3.14159f + 360.0f;

        if((!isless(destination_x,current.x)&&!isgreater(destination_x,current.x)) && isgreater(destination_y,current.y))//destination lies at 12 O'clock
            rotation = 90.0f;

        if((!isless(destination_x,current.x)&&!isgreater(destination_x,current.x))&& isless(destination_y,current.y))//destination lies at 6'O'clock
            rotation = 270.0f;

        if(isless(destination_x,current.x) && (!isless(destination_y,current.y)&&!isgreater(destination_y,current.y)))//destination lies at 9 O'clock
            rotation = 180.0f;

        if(isgreater(destination_x,current.x) && (!isless(destination_y,current.y)&&!isgreater(destination_y,current.y)))//destination lies at 3 O'clock
            rotation = 0.0f;
    }
}

void movable_object::turn_to_point(point2f destination)
{
    turn_to_point(destination.x,destination.y);
}

//moves object to destination over time at specified rate
bool movable_object::move_to_point(float destination_x, float destination_y, float rate)
{
    if(rally_set)
    {
        movable_object::turn_to_point(destination_x,destination_y);
        if(isless(distance(current.x,current.y,destination_x,destination_y),radius))
        rally_set=false;
        move_forward(speed*rate);
        moving_forward=true;
        return true;
    }
    else
        return false;
}

bool movable_object::move_to_point(point2f destination,float rate)
{
    return move_to_point(destination.x,destination.y,rate);
}

bool movable_object::move_to_point(point2f destination)
{
    return move_to_point(destination.x,destination.y,1.0f);
}

bool movable_object::move_to_point(float destination_x,float destination_y)
{
    return move_to_point(destination_x,destination_y,1.0f);
}

void movable_object::add_action(int action_no, int times)
{
    std::vector<int> action;
    action.push_back(action_no);//number of the action to do. this will be put at index 0
    action.push_back(times);//number of times to do the action. this will be stored at index 1
    action.push_back(0);//how many times its already been done. this will be stored at index 2
    actions.push(action);//add this vector to the actions queue
}

bool movable_object::perform_actions()
{
    if(!actions.empty())
    {
        if(actions.front().at(2)<actions.front().at(1))//times done is less than times to do
        {
            switch(actions.front().at(0))//action number from index 0 of the stored vector
            {
            case 1://move left
                move_left();
                break;
            case 2://move right
                move_right();
                break;
            case 3://move up
                move_forward();
                break;
            case 4://move down
                move_back();
                break;
            case 5://turn left
                turn_left();
                break;
            case 6://turn right
                turn_right();
                break;
            }
            actions.front().at(2)++;
        }
        else
            actions.pop();
        return true;
    }
    else
        return false;
}

movable_object::movable_object(): complex_object()
{
    type="movable object";
    speed=1.01f;
    rally = &rest;
    rally_set=false;
    reset_motion();
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created."<<std::endl;
}
