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

#ifndef SCENE_H
#define SCENE_H
#include "draggable_object.h"
#include "physics_object.h"
#include "rts_object.h"
#include "text_object.h"
#include "button.h"
#include "menu.h"
#include "dropdown_menu.h"
#include <map>
#include <vector>

class scene
{
public:
    color background_color;
    menu* current_menu;
    //maps are used because we need to access the objects by referencing a common identifier (object.number)
    //pointers are used because everything is created in game::initialize() and we just need to reference them
    std::map<int,draggable_object*> draggable_objects;
    std::map<int,physics_object*> physics_objects;
    std::map<int,rts_object*> rts_objects;
    std::map<unsigned char, void (*)()> key_bindings;
    std::map<unsigned char, void (*)()> key_toggles;
    std::map<std::string, void (*)()> special_bindings;
    std::map<std::string, void (*)()> special_toggles;
    std::vector<text_object*> text_objects;
    std::vector<button*> buttons;
    std::vector<menu*> menus;
    std::vector<dropdown_menu*> dropdown_menus;
    void add_draggable_object(draggable_object*);//add a draggable object to the scene
    void add_physics_object(physics_object*);//add a physics object to the scene
    void add_rts_object(rts_object*);//add an rts object to the scene
    void add_text(text_object*);//add text object to the scene
    void add_button(button*);//add button to the scene
    void add_menu(menu*);//add menu to the scene
    void add_menu(dropdown_menu*);//add dropdown menu to the scene
    void bind_key(unsigned char, std::string, void (*)());//associate a key with an action that will be performed under given condition
    void bind_key(unsigned char, void (*)(), void (*)());//associate a key that will perform 1 of 2 actions when toggled
    void bind_key(std::string, std::string, void (*)());//associate a special key with an action that will be performed under given condition
    void bind_key(std::string, void (*)(), void (*)());//associate a special key that will perform 1 of 2 actions when toggled
    void show_draggable_objects();//show all draggable objects
    void hide_draggable_objects();//hide all draggable objects
    void show_physics_objects();//show all physics objects
    void hide_physics_objects();//hide all physics objects
    void show_rts_objects();//show all rts objects
    void hide_rts_objects();//hide all rts objects
    void show_text();//show the text
    void hide_text();//hide the text
    void show_buttons();//show all buttons
    void hide_buttons();//hide all buttons
    void show_menus();//show all menus
    void hide_menus();//hide all menus
    void show_all();//show all objects and ui elements
    void hide_all();//hide all objects and ui elements
    void render();//render all objects and ui elements
    void update();//update all objects and ui elements
    void sync();//update clock-based items
    void clear();//delete all objects and ui elements
    scene();
};

#endif // SCENE_H
