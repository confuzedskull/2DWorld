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

#include "button.h"
#include "ui.h"
#include "window.h"
#include "cursor.h"
#include "audio.h"
#include <iostream>
#include <math.h>

std::string ui::button::default_texture="";
std::string ui::button::default_mask="";
std::string ui::button::default_click_sound="";
std::string ui::button::default_hover_sound="";
color ui::button::default_fill_color = ui::default_fill_color;
color ui::button::default_border_color = ui::default_border_color;
int ui::button::default_margin = 5;
int ui::button::default_width = 48;
int ui::button::default_height = 12;

int ui::button::combined_width()
{
    if(text.get_allignment()==LEFT || text.get_allignment()==RIGHT)
        return text.get_width()+margin+width;
    else
    {
        if(text.get_width()>width)
            return text.get_width();
        else
            return width;
    }
}

int ui::button::combined_height()
{
    if(text.get_allignment()==TOP || text.get_allignment()==BOTTOM)
        return text.get_height()+margin+height;
    else
    {
        if(text.get_height()>height)
            return text.get_height();
        else
            return height;
    }
}

std::string ui::button::get_type()
{
    return "button";
}

void ui::button::format()
{
    if(width<text.get_width()+(margin*2))
        width=text.get_width()+(margin*2);
    if(height<text.get_height()+(margin*2))
        height=text.get_height()+(margin*2);
    calc_boundaries();
    text.set_position(position.x,position.y);
}

void ui::button::set_label(std::string txt)
{
    text.set_text(txt);
    text.set_position(position.x,position.y);
    format();
}

void ui::button::set_action(void (*act)())
{
    action=act;
}

void ui::button::set_action(void (*act)(int),int i)
{
    action1i=act;
    int_param1=i;
}

void ui::button::mouse_function()
{
    if(visible && enabled)
    {
        hover_function();
        if(left_clicked())
        {
            if(!performed_action)
            {
                if(!muted)
                    audio::play(click_sound);
                action();
                action1i(int_param1);
                performed_action=true;
                std::clog<<"object#"<<number<<"(button)"<<" clicked.\n";
            }
        }
        else
            performed_action=false;
    }
}

void ui::button::render()
{
    if(visible)
    {
        render_shape();
        render_border();
        text.render();
        mark_selected();
    }
}

void ui::button::update()
{
    text.visible=visible;
    mouse_function();
}

void ui::button::action_placeholder(){}

void ui::button::action_placeholder1i(int i){}

ui::button::button()
{
    set_dimensions(default_width,default_height);
    fill_color=default_fill_color;
    border_color=default_border_color;
    margin=default_margin;
    text.set_text("click me");
    action=ui::button::action_placeholder;
    action1i=ui::button::action_placeholder1i;
    bordered=true;
    performed_action=false;
    set_texture(default_texture);
    set_mask(default_mask);
    set_click_sound(default_click_sound);
    set_hover_sound(default_hover_sound);
    std::clog<<"object#"<<number<<"(button)"<<" created.\n";
}

ui::button::button(float x, float y, char* txt, void (*act)(void))
{
    position.set(x,y);
    set_dimensions(default_width,default_height);
    fill_color=default_fill_color;
    border_color=default_border_color;
    margin=default_margin;
    set_label(txt);
    action=act;
    bordered=true;
    performed_action=false;
    set_texture(default_texture);
    set_mask(default_mask);
    set_click_sound(default_click_sound);
    set_hover_sound(default_hover_sound);
    std::clog<<"object#"<<number<<"(button)"<<" created.\n";
}
