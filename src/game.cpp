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

#include "game.h"
#include "window.h"
#include "controls.h"
#include "cursor.h"
#include "ui.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>

//initialize variables
clock_t game::time_started;
float game::time = 0.0f;
double game::time_elapsed = 0.0f;
bool game::paused=false;
scene* game::current_scene = new scene();
std::vector<scene*> game::scenes;
std::map<std::string, game::setting> game::settings;
std::map<std::string, game::condition> game::conditions;

//This checks which objects are touching and what they should do when that occurs
//NOTE: This function uses C++11 "for" loops
void game::collision_detection()
{
    for(auto a:current_scene->rts_objects)//iterate through rts objects comparing
    {
        for(auto b:current_scene->rts_objects)//iterate through rts objects being compared
        {
            if(a.first!=b.first && a.second->is_close(*b.second))//check objects colliding with other objects
            {
                a.second->identify_touched(*b.second);
                a.second->repel(*b.second);
            }
        }
    }
    for(auto a:current_scene->physics_objects)//iterate through physics objects comparing
    {
        for(auto b:current_scene->physics_objects)//iterate through physics objects being compared
        {
            if(a.first!=b.first && a.second->is_close(*b.second))//check objects colliding with other objects
            {
                a.second->identify_touched(*b.second);
                a.second->repel(*b.second);
                a.second->calc_momentum(*b.second);
            }
        }
    }
    for(auto a:current_scene->draggable_objects)//iterate through draggable objects comparing
    {
        for(auto b:current_scene->draggable_objects)//iterate through draggable objects being compared
        {
            if(a.first!=b.first && a.second->is_close(*b.second))//check objects colliding with other objects
            {
                a.second->identify_touched(*b.second);
                a.second->repel(*b.second);
            }
        }
    }
}
//All the elements of the game are initialized here
void game::initialize()
{
//Initialize Settings
    add_setting("window","width",window::width);
    add_setting("window","height",window::height);
    add_setting("window","position_x",window::position.x);
    add_setting("window","position_y",window::position.y);
    add_setting("game","main_scene#",1);
    add_setting("game","play_scene#",2);
    add_setting("game","show_draggable_objects",1);
    add_setting("game","show_physics_objects",1);
    add_setting("game","show_rts_objects",1);
    add_setting("draggable_object","origin_x",draggable_object::origin.x);
    add_setting("draggable_object","origin_y",draggable_object::origin.y);
    add_setting("physics_object","origin_x",physics_object::origin.x);
    add_setting("physics_object","origin_y",physics_object::origin.y);
    add_setting("rts_object","origin_x",rts_object::origin.x);
    add_setting("rts_object","origin_y",rts_object::origin.y);

//Initialize Conditions
    add_condition("game","show_draggable_objects",1,show_draggable_objects);
    add_condition("game","show_draggable_objects",0,hide_draggable_objects);
    add_condition("game","show_physics_objects",1,show_physics_objects);
    add_condition("game","show_physics_objects",0,hide_physics_objects);
    add_condition("game","show_rts_objects",1,show_rts_objects);
    add_condition("game","show_rts_objects",0,hide_rts_objects);

//Initialize Objects
    std::clog<<"initializing objects...\n";
    //initialize the physics objects
    physics_object* po1 = new physics_object();
    po1->set_position(window::width/2-48,window::height/2+48);//set position forward left of window center
    po1->cue_action("move right",12);
    po1->cue_action("move back",12);
    po1->cue_action("move left",12);
    po1->cue_action("move forward",12);
    po1->cue_action("turn left",15);
    po1->cue_action("turn right",15);

    physics_object* po2 = new physics_object();
    po2->set_position(window::width/2+48,window::height/2+48);//set position forward right of window center
    po2->cue_action("move back",12);
    po2->cue_action("move left",12);
    po2->cue_action("move forward",12);
    po2->cue_action("move right",12);
    po2->cue_action("turn left",15);
    po2->cue_action("turn right",15);

    physics_object* po3 = new physics_object();
    po3->set_position(window::width/2+48,window::height/2-48);//set position backward right of window center
    po3->cue_action("move left",12);
    po3->cue_action("move forward",12);
    po3->cue_action("move right",12);
    po3->cue_action("move back",12);
    po3->cue_action("turn left",15);
    po3->cue_action("turn right",15);

    physics_object* po4 = new physics_object();
    po4->set_position(window::width/2-48,window::height/2-48);//set position backward left of window center
    po4->cue_action("move forward",12);
    po4->cue_action("move right",12);
    po4->cue_action("move back",12);
    po4->cue_action("move left",12);
    po4->cue_action("turn left",15);
    po4->cue_action("turn right",15);
    std::clog<<"initialized physics objects\n";
    //initialize the draggable objects
    draggable_object* do1 = new draggable_object();
    do1->set_position(window::center.x,window::center.y);//set position window center
    do1->fill_color.set("black");
    std::clog<<"initialized draggable objects\n";
    //initialize the rts objects
    rts_object* rtso1 = new rts_object();
    rtso1->set_position(window::center.x+96,window::center.y);//set position right of window center
    rtso1->fill_color.set("yellow");

    rts_object* rtso2 = new rts_object();
    rtso2->set_position(window::center.x,window::center.y-96);//set position below window center
    rtso2->fill_color.set("green");

    rts_object* rtso3 = new rts_object();
    rtso3->set_position(window::center.x,window::center.y+96);//set position above window center
    rtso3->fill_color.set("red");

    rts_object* rtso4 = new rts_object();
    rtso4->set_position(window::center.x-96,window::center.y);//set position left of window center
    rtso4->fill_color.set("blue");
    std::clog<<"initialized rts objects\n";
//Initialize Text
    //Information Overlay Text
    label* object_info = new label();
    object_info->spacing=20;
    object_info->set_position(ui::margin,window::height-20);
    object_info->hide();//we don't want to see this right away

    label* game_info = new label();
    game_info->spacing=20;
    game_info->set_position(window::width-(ui::margin+200),window::height-20);
    game_info->hide();//we don't want to see this right away

    std::clog<<"initialized text\n";
    std::clog<<"initializing user interface...\n";
//Initialize Checkboxes
    checkbox* show_dos = new checkbox();
    show_dos->set_position(window::width*0.9,window::height*0.4);
    show_dos->set_label("show draggable objects");
    show_dos->bind_option(&settings["game"]["show draggable objects"]);

    checkbox* show_pos = new checkbox();
    show_pos->set_position(window::width*0.9,window::height*0.35);
    show_pos->set_label("show physics objects");
    show_pos->bind_option(&settings["game"]["show physics objects"]);

    checkbox* show_rtsos = new checkbox();
    show_rtsos->set_position(window::width*0.9,window::height*0.3);
    show_rtsos->set_label("show rts objects");
    show_rtsos->bind_option(&settings["game"]["show rts objects"]);
    std::clog<<"initialized checkboxes\n";
//Initialize Buttons
    //Main Menu Buttons
    button* play_button = new button();
    play_button->set_label("Play");
    play_button->set_action(play);

    button* quit_button = new button();
    quit_button->set_label("Quit");
    quit_button->set_action(warn_quit);

    //Quit Menu Buttons
    button* confirm_quit = new button();
    confirm_quit->set_label("Yes");
    confirm_quit->set_action(quit);

    button* cancel_quit = new button();
    cancel_quit->set_label("No");
    cancel_quit->set_action(return_menu);
    //Pause Menu Buttons
    button* resume_button = new button();
    resume_button->set_label("Resume");
    resume_button->set_action(resume);

    button* load_button = new button();
    load_button->set_label("Load");
    load_button->set_action(load);

    button* save_button = new button();
    save_button->set_label("Save");
    save_button->set_action(save);

    button* main_menu_button = new button();
    main_menu_button->set_label("Main Menu");
    main_menu_button->set_action(warn_return);
    //Warning Menu Buttons
    button* confirm_return_button = new button();
    confirm_return_button->set_label("Yes");
    confirm_return_button->set_action(return_menu);

    button* cancel_return_button = new button();
    cancel_return_button->set_label("No");
    cancel_return_button->set_action(pause);
    //Game Buttons
    button* create_po_button = new button();//"po" stands for "physics object"
    create_po_button->set_label("physics object");
    create_po_button->set_action(add_physics_object);

    button* create_do_button = new button();//"do" stands for "draggable object"
    create_do_button->set_label("draggable object");
    create_do_button->set_action(add_draggable_object);

    button* create_rtso_button = new button();//"rtso" stands for "real-time strategy object"
    create_rtso_button->set_label("rts object");
    create_rtso_button->set_action(add_rts_object);

    button* create_object_button = new button();
    create_object_button->set_position(window::width*0.9,window::height*0.1);//put the button on the right side, 1/5th of the way up
    create_object_button->set_label("create object");
    create_object_button->set_action(create_object);

    button* delete_object_button = new button();
    delete_object_button->set_position(window::width*0.9,window::height*0.05);//put the button on the right side, 1/5th of the way up
    delete_object_button->set_label("delete object");
    delete_object_button->set_action(delete_selected);

    button* menu_button = new button();
    menu_button->set_position(window::center.x,window::height-20);//put the button at the top middle, just below the top
    menu_button->set_label("Menu");
    menu_button->set_action(pause);
    std::clog<<"initialized buttons\n";
//Initialize Menus
    dropdown_menu* creation_menu = new dropdown_menu();
    creation_menu->set_title("create new...");
    creation_menu->set_position(window::width*0.9,window::height*0.25);
    creation_menu->add_item(create_do_button);
    creation_menu->add_item(create_po_button);
    creation_menu->add_item(create_rtso_button);

    menu* main_menu = new menu();
    main_menu->set_title("Main Menu");
    main_menu->add_item(play_button);
    main_menu->add_item(load_button);
    main_menu->add_item(quit_button);
    main_menu->format();//make sure everything is neat and tidy

    menu* quit_menu = new menu();
    quit_menu->set_title("Warning");
    quit_menu->set_subtitle("Are you sure you want to quit?");
    quit_menu->add_item(confirm_quit);
    quit_menu->add_item(cancel_quit);
    quit_menu->set_layout("horizontal");
    quit_menu->format();
    quit_menu->hide();//we don't want to see this right away

    menu* pause_menu = new menu();
    pause_menu->set_title("Pause Menu");
    pause_menu->add_item(resume_button);
    pause_menu->add_item(save_button);
    pause_menu->add_item(main_menu_button);
    pause_menu->format();//make sure everything is neat and tidy
    pause_menu->hide();//we don't want to see this right away

    menu* leave_menu = new menu();
    leave_menu->set_title("Warning");
    leave_menu->set_subtitle("Are you sure you want to leave?");
    leave_menu->set_layout("horizontal");
    leave_menu->add_item(confirm_return_button);
    leave_menu->add_item(cancel_return_button);
    leave_menu->format();//make sure everything is neat and tidy
    leave_menu->hide();//we don't want to see this right away
    std::clog<<"initialized menus\n";
//Initialize Scenes
    std::clog<<"initializing scenes...\n";
    scene* home_screen = new scene();
    home_screen->add_menu(main_menu);
    home_screen->add_menu(quit_menu);
    home_screen->current_menu=main_menu;
    home_screen->bind_key("up","hold",controls::previous_item);//select previous item when up arrow is pressed
    home_screen->bind_key("down","hold",controls::next_item);//select next item when down arrow is pressed
    home_screen->bind_key("left","hold",controls::previous_item);//select previous item when left arrow is pressed
    home_screen->bind_key("right","hold",controls::next_item);//select next item when right arrow is pressed
    home_screen->bind_key('\r',"press",controls::choose_item);//choose current item when return key is pressed
    home_screen->bind_key(27,"press",warn_quit);//open warning when escape key is pressed
    scenes.push_back(home_screen);//add to scenes
    current_scene=home_screen;//start the game with this screen

    scene* game_screen = new scene();
    game_screen->background_color.set("white");
    game_screen->add_object(do1);
    game_screen->add_object(po1);
    game_screen->add_object(po2);
    game_screen->add_object(po3);
    game_screen->add_object(po4);
    game_screen->add_object(rtso1);
    game_screen->add_object(rtso2);
    game_screen->add_object(rtso3);
    game_screen->add_object(rtso4);
    game_screen->add_text(object_info);
    game_screen->add_text(game_info);
    game_screen->add_checkbox(show_dos);
    game_screen->add_checkbox(show_pos);
    game_screen->add_checkbox(show_rtsos);
    game_screen->add_button(delete_object_button);
    game_screen->add_button(create_object_button);
    game_screen->add_button(menu_button);
    game_screen->add_menu(pause_menu);
    game_screen->add_menu(leave_menu);
    game_screen->add_menu(creation_menu);
    game_screen->bind_key('w',"hold",controls::move_forward);//move selected object forward when 'w' key is held
    game_screen->bind_key('a',"hold",controls::move_left);//move selected object left when 'a' key is held
    game_screen->bind_key('s',"hold",controls::move_back);//move selected object back when 's' key is held
    game_screen->bind_key('d',"hold",controls::move_right);//move selected object right when 'd' key is held
    game_screen->bind_key('q',"hold",controls::turn_left);//turn selected object left when 'q' key is held
    game_screen->bind_key('e',"hold",controls::turn_right);//turn selected object right when 'e' key is held
    game_screen->bind_key('i',ui::show_text,ui::hide_text);//toggles between two actions
    game_screen->bind_key('\r',"press",controls::choose_item);//choose current item when return key is pressed
    game_screen->bind_key("up","hold",controls::previous_item);//select previous item when up arrow is held
    game_screen->bind_key("down","hold",controls::next_item);//select next item when down arrow is held
    game_screen->bind_key("left","hold",controls::previous_item);//select previous item when left arrow is held
    game_screen->bind_key("right","hold",controls::next_item);//select next item when right arrow is held
    game_screen->bind_key("insert","press",game::create_object);//creates an object when insert key is pressed
    game_screen->bind_key(127,"press",delete_selected);//delete selected object when DEL key is pressed
    game_screen->bind_key(27,pause,resume);//open/close pause menu when escape key is pressed
    scenes.push_back(game_screen);//add to scenes
}

void game::add_setting(std::string section, std::string property, int value)
{
    settings[section][property]=value;
}

void game::add_condition(std::string section, std::string property, int value, void (*action)())
{
    conditions[section][property][value]=action;
}

void game::show_draggable_objects()
{
    current_scene->show_draggable_objects();
}

void game::hide_draggable_objects()
{
    current_scene->hide_draggable_objects();
}

void game::show_physics_objects()
{
    current_scene->show_physics_objects();
}

void game::hide_physics_objects()
{
    current_scene->hide_physics_objects();
}

void game::show_rts_objects()
{
    current_scene->show_rts_objects();
}

void game::hide_rts_objects()
{
    current_scene->hide_rts_objects();
}

void game::add_draggable_object()
{
    draggable_object* new_do = new draggable_object();
    current_scene->add_object(new_do);//add object to current scene
}

void game::add_physics_object()
{
    physics_object* new_po = new physics_object();
    current_scene->add_object(new_po);//add object to current scene
}

void game::add_rts_object()
{
    rts_object* new_rtso = new rts_object();
    current_scene->add_object(new_rtso);//add object to current scene
}

void game::create_object()
{
    if(current_scene->last_object->get_type()=="draggable object")
        current_scene->add_object(new draggable_object());
    if(current_scene->last_object->get_type()=="physics object")
        current_scene->add_object(new physics_object());
    if(current_scene->last_object->get_type()=="rts object")
        current_scene->add_object(new rts_object());
}

void game::delete_selected()
{
    for(auto so:cursor::selected_objects)
    {
        if(current_scene->draggable_objects.find(so.first)!=current_scene->draggable_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<'('<<so.second->get_type()<<')'<<" deleted."<<std::endl;
            delete current_scene->draggable_objects[so.first];
            current_scene->draggable_objects.erase(so.first);
        }
        if(current_scene->physics_objects.find(so.first)!=current_scene->physics_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<'('<<so.second->get_type()<<')'<<" deleted."<<std::endl;
            delete current_scene->physics_objects[so.first];
            current_scene->physics_objects.erase(so.first);
        }
        if(current_scene->rts_objects.find(so.first)!=current_scene->rts_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<'('<<so.second->get_type()<<')'<<" deleted."<<std::endl;
            delete current_scene->rts_objects[so.first];
            current_scene->rts_objects.erase(so.first);
        }
    }
    cursor::selected_objects.clear();
}

void game::play()
{
    cursor::reset();
    cursor::highlighting_enabled=true;
    paused=false;
    scenes[1]->enable_all();
    scenes[1]->menus[0]->hide();
    scenes[1]->menus[1]->hide();
    scenes[1]->current_menu=scenes[1]->dropdown_menus[0];//set the creation menu as current
    current_scene=scenes[1];//open game screen
    std::clog<<"started game."<<std::endl;
}

void game::pause()
{
    paused=true;
    cursor::highlighting_enabled=false;
    scenes[1]->menus[0]->show();//show the pause menu
    scenes[1]->menus[1]->hide();//hide the warning menu
    scenes[1]->current_menu=scenes[1]->menus[0];//set the pause menu as current
    scenes[1]->disable_all();
    std::clog<<"paused game."<<std::endl;
}

void game::resume()
{
    paused=false;
    cursor::highlighting_enabled=true;
    scenes[1]->enable_all();
    scenes[1]->menus[0]->hide();//hide pause menu
    scenes[1]->menus[1]->hide();//hide warning menu
    scenes[1]->current_menu=scenes[1]->dropdown_menus[0];//set the creation menu as current
    std::clog<<"resumed game."<<std::endl;
}

void game::warn_quit()
{
    scenes[0]->menus[0]->hide();//hide main menu
    scenes[0]->menus[1]->show();//show the quit menu
    scenes[0]->current_menu=scenes[0]->menus[1];//set the warning menu as current
}

void game::warn_return()
{
    scenes[1]->menus[0]->hide();//hide the pause menu
    scenes[1]->menus[1]->show();//show the warning prompt
    scenes[1]->current_menu=scenes[1]->menus[1];//set the warning menu as current
}

void game::return_menu()
{
    cursor::reset();
    scenes[0]->menus[0]->show();//enable the main menu
    scenes[0]->menus[1]->hide();//hide the quit menu
    scenes[0]->current_menu=scenes[0]->menus[0];//set main menu as current
    current_scene=scenes[0];//open home screen
    std::clog<<"returned to menu."<<std::endl;
}

void game::quit()
{
    std::clog<<"quitting...\n";
    exit(0);
}

void game::update()
{
    if(!paused)
    {
        time_elapsed = ((float)clock()-time_started)/CLOCKS_PER_SEC;//update the start time
        collision_detection();//apply collision effects
    }
    current_scene->update();//update scene
    //process settings
    for(auto sect:settings)//iterate through sections
    {
        for(auto sett:sect.second)//iterate through settings
        {
            if(conditions.find(sect.first)!=conditions.end())//section exists
            {
                if(conditions[sect.first].find(sett.first)!=conditions[sect.first].end())//matching condition exists
                {
                    for(auto val:conditions[sect.first][sett.first])//iterate through the conditions
                    {
                        if(sett.second==val.first)//setting value matches condition value
                            val.second();//perform associated action
                    }
                }
            }
        }
    }
}

void game::load()
{
    std::clog<<"loading settings...\n";
    std::ifstream config_file("./data/settings.ini");
    while(config_file.good())
    {
        std::string file_line;
        char first_char=config_file.peek();//check the first character
        if(first_char==';')//comment is detected
            std::getline(config_file,file_line);//get this line and move iterator to next line
        if(first_char=='[')//section is detected
        {
            config_file>>file_line;
            std::string section=file_line.substr(1,file_line.length()-2);//the section name is between the brackets
            do
            {
                //load settings
                std::string property;
                char separator;
                int value;
                config_file>>property>>separator>>value;
                add_setting(section,property,value);
                std::clog<<"setting: "<<section<<"::"<<property<<':'<<value<<" loaded."<<std::endl;
                config_file.get();//eat the newline character
                first_char=config_file.peek();//check the first character
            }
            while(first_char!='[' && first_char>0);//as long as new section is not detected
        }
    }
    config_file.close();
    std::clog<<"settings loaded.\n";
    std::clog<<"loading scene...\n";
    scenes[settings["game"]["play_scene"]]->load();
    std::clog<<"game loaded.\n";
}

void game::save()
{
    std::clog<<"saving game...\n";
    std::clog<<"saving settings...\n";
    std::ofstream config_file("./data/settings.ini");
    for(auto sect:settings)//iterate through sections
    {
        config_file<<'['<<sect.first<<']'<<std::endl;//add section header
        for(auto sett:sect.second)//iterate through settings
            config_file<<sett.first<<" = "<<sett.second<<std::endl;//add property and value
    }
    config_file.close();
    std::clog<<"settings saved.\n";
    std::clog<<"saving scene...\n";
    current_scene->save();
    std::clog<<"game saved.\n";
}

void game::sync()
{
    if(!paused)
    {
        time_started=clock();//reset the start time
        time+=window::refresh_rate;//increment the game clock
        current_scene->sync();//update clock-based events
    }
}
