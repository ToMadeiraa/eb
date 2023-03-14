#pragma once
#include <SFML/Graphics.hpp>

class Timer
{
	int position_x, position_y;
	int font_size;
	int frame_time;
	int seconds;
	int minutes;
	int hours;
	sf::Font time_font;
	sf::Color time_color;
	sf::Text clock_text;
	void InitText();
public:

	Timer(int x = 50, int y = 50, int size = 3, sf::Color mycolor = sf::Color::White, std::string font = "fonts/Freshman.ttf");
	void setposition(int x, int y);
	void setcolor(sf::Color color);
	void setTime_size(int size);
	void drawTime(sf::RenderWindow& window);
};
