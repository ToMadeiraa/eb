#include "../headers/Timer.hpp"
#include <windows.h>

Timer::Timer(int x, int y, int size, sf::Color mycolor, std::string font)
{
    position_x = x;
    position_y = y;
    time_font.loadFromFile(font);
    time_color = mycolor;
    font_size = size * 10;
    frame_time = 0;
    seconds = 0;
    minutes = 0;
    hours = 0;
    InitText();
}

void Timer::drawTime(sf::RenderWindow& window)
{
    std::string tmpstr;
    if (hours < 10)
    {
        tmpstr = "0";
        tmpstr.append(std::to_string(hours));
    }
    else tmpstr = std::to_string(hours);
    tmpstr.append(":");
    if (minutes < 10) tmpstr.append("0");
    tmpstr.append(std::to_string(minutes));
    tmpstr.append(":");
    if (seconds < 10) tmpstr.append("0");
    tmpstr.append(std::to_string(seconds));

    clock_text.setPosition(position_x, position_y);
    clock_text.setString(tmpstr);
    window.draw(clock_text);

    frame_time++;
    if (frame_time > 119) {
        frame_time = 0;
        seconds++;
    }
    if (seconds > 59) {
        seconds = 0;
        minutes++;
    }
    if (minutes > 59) {
        minutes = 0;
        hours++;
    }
    if (hours > 23) {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
}

void Timer::InitText()
{
    clock_text.setFont(time_font);
    clock_text.setCharacterSize(font_size);
    clock_text.setFillColor(time_color);
}

void Timer::setposition(int x, int y)
{
    position_x = x;
    position_y = y;
}

void Timer::setcolor(sf::Color color)
{
    time_color = color;
    InitText();
}

void Timer::setTime_size(int size)
{
    (size > 10) ? size = 10 : (size < 3) ? size = 3 : size = size;
    font_size = size * 10;
    InitText();
}