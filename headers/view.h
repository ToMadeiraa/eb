#pragma once
#include <SFML/Graphics.hpp>

sf::View view;

sf::View getPlayerCoordinateForView(int x, int y) {

	float tempX = x; float tempY = y;

	if (x < 800) tempX = 800;
	if (x > 1248) tempX = 1248;
	if (y < 450) tempY = 450;
	if (y > 1598) {
		tempY = 1598;
	}

	view.setCenter(tempX, tempY);
	return view;
};
