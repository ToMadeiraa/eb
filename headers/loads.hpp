#pragma once
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

using namespace sf;


Image image_map;
Image image_enemy;
Image image_enemy2;
Image image_player;
Image image_blood;
Image image_ammo;
Texture texture_map;
Texture texture_enemy;
Texture texture_enemy2;
Texture texture_player;
Texture texture_blood;
Texture texture_ammo;
Sprite s_map;
Sprite s_enemy;
Sprite s_enemy2;
Sprite s_player;
Sprite s_blood;
Sprite s_ammo;




void loadTextures(void) {
	image_map.loadFromFile("images/tiles.png");
	image_enemy.loadFromFile("images/enemy_small.png");
	image_enemy2.loadFromFile("images/enemy2_small.png");
	image_player.loadFromFile("images/player_small.png");
	image_blood.loadFromFile("images/blood.png");
	image_ammo.loadFromFile("images/ammo.png");

	texture_enemy.loadFromImage(image_enemy);
	texture_enemy2.loadFromImage(image_enemy2);
	texture_player.loadFromImage(image_player);
	texture_map.loadFromImage(image_map);
	texture_blood.loadFromImage(image_blood);
	texture_ammo.loadFromImage(image_ammo);

	s_map.setTexture(texture_map);
	s_player.setTexture(texture_player);
	s_enemy.setTexture(texture_enemy);
	s_enemy2.setTexture(texture_enemy2);
	s_blood.setTexture(texture_blood);
	s_ammo.setTexture(texture_ammo);
}

SoundBuffer music1;
SoundBuffer fire1;
SoundBuffer popadanie;
SoundBuffer step;
SoundBuffer take_ammo;
Sound gun;
Sound sound;
Sound s_popadanie;
Sound s_step;
Sound s_take_ammo;


void loadSounds(void) {
	music1.loadFromFile("sounds/Medium.ogg");
	fire1.loadFromFile("sounds/Fire.wav");
	popadanie.loadFromFile("sounds/Popadanie.wav");
	step.loadFromFile("sounds/Step.wav");
	take_ammo.loadFromFile("sounds/take_ammo.wav");

	s_popadanie.setBuffer(popadanie);
	s_popadanie.setVolume(10.f);
	s_step.setBuffer(step);
	s_step.setVolume(00.f);
	s_take_ammo.setBuffer(take_ammo);
	s_take_ammo.setVolume(00.f);
	sound.setVolume(00.f);
	sound.setBuffer(music1);
	gun.setVolume(00.f);
	gun.setBuffer(fire1);
}

Font font;

void loadFonts() {
	font.loadFromFile("fonts/Freshman.ttf");
}

Shader shadowShader;

void loadShaders(void) {
	shadowShader.loadFromFile("shaders/shadow.vert", "shaders/shadow.frag");
	shadowShader.setUniform("u_resolution", Vector2f(1600, 900));
}

