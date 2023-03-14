#pragma once
using namespace sf;
Text frames_text, mouse_pos_text, mouse_x_text, mouse_y_text, mouse_x_text_map, mouse_y_text_map, player_x_text, player_y_text, zoom_text;

void initText () {
	frames_text.setFillColor(Color::White);
	frames_text.setFont(font);
	mouse_pos_text = frames_text;
	mouse_x_text = frames_text;
	mouse_y_text = frames_text;
	mouse_x_text_map = frames_text;
	mouse_y_text_map = frames_text;
	player_x_text = frames_text;
	player_y_text = frames_text;
	zoom_text = frames_text;
}
