#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include "SFML\Audio.hpp"
#include<math.h>
#include<vector>
#include<cstdlib>
#include "../headers/Timer.hpp"
#include"../headers/map.h"
#include"../headers/view.h"
#include"../headers/loads.hpp"
#include"../headers/console.h"

#define WINDOW_WIDTH 1600
#define MAP_SIZE_X 2048
#define MAP_SIZE_Y 2048
#define WINDOW_HEIGHT 900
#define framelimit 120
#define PI 3.14159265f

using namespace sf;

class Bullet
{
public:
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;
	Bullet(float radius = 2.f)
		: currVelocity(0.f, 0.f), maxSpeed(960*3/framelimit)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Yellow);
	}
};

class Unit
{

public:
	Sprite sprte;
	Unit(Sprite loaded_sprite) {
		sprte = loaded_sprite;
		this->sprte.setOrigin(32, 32);
		this->sprte.setPosition(Vector2f(rand() % MAP_SIZE_X - 30, rand() % MAP_SIZE_Y/2 - 30));
	}
};

class Objects
{

public:
	Sprite s_obj;
	Objects(Sprite loaded_sprite) {
		this->s_obj.setOrigin(32, 32);
		s_obj = loaded_sprite;
	}
};

int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SS 360", Style::Fullscreen);
	view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	window.setFramerateLimit(framelimit);

	loadTextures();
	loadFonts();
	loadSounds();

	sound.play(); //играет музыка

	Clock clock_gun; //таймер выстрелов

	//враги
	int i = 0;
	std::vector<Unit> enemies;
	while (i < 10) {
		Unit enemy(s_enemy);
		enemies.push_back(enemy);
		i++;
	}
	int j = 0;
	while (j < 10) {
		Unit enemy(s_enemy2);
		enemies.push_back(enemy);
		j++;
	}

	//игрок
	Unit player(s_player);
	player.sprte.setPosition(1000, 1500);
	view.setCenter(1000, 1500);

	//пули
	Bullet b1;
	std::vector<Bullet> bullets;

	//кровь 
	Objects bloodd(s_blood);
	bloodd.s_obj.setOrigin(32, 32);
	std::vector<Objects> bloods;

	//патроны
	Objects bullet_ammos(s_ammo);
	bullet_ammos.s_obj.setOrigin(16, 16);
	std::vector<Objects> ammos;
	int frames_timer = 0;
	
	// часы
	Timer mytime(50, 50, 4);

	//консоль
	int total_frames = 0;
	initText();

	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;

	double zoom_current_var = 1;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseWheelMoved) {
				if (event.mouseWheel.delta > 0 && zoom_current_var > 0.5) {
					view.zoom(0.97f);
					zoom_current_var *= 0.97;
				}
				else if (event.mouseWheel.delta < 0 && zoom_current_var < 1.5) {
					view.zoom(1.03f);
					zoom_current_var *= 1.03;
				}
			}
		}
		//расчет полета пулечки
		playerCenter = Vector2f(player.sprte.getPosition().x, player.sprte.getPosition().y);
		mousePosWindow = Vector2f(view.getCenter().x + (Mouse::getPosition().x - WINDOW_WIDTH / 2)*zoom_current_var, view.getCenter().y + (Mouse::getPosition().y - WINDOW_HEIGHT / 2)*zoom_current_var);
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;
		player.sprte.setRotation(deg + 90);

		//настройка управления
		if (Keyboard::isKeyPressed(Keyboard::A) && player.sprte.getPosition().x > 32) {
			player.sprte.move(-480 / framelimit, 0);
			getPlayerCoordinateForView(player.sprte.getPosition().x, player.sprte.getPosition().y);
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && player.sprte.getPosition().x < 2048-32) {
			player.sprte.move(480 / framelimit, 0);
			getPlayerCoordinateForView(player.sprte.getPosition().x, player.sprte.getPosition().y);
		}
		if (Keyboard::isKeyPressed(Keyboard::W) && player.sprte.getPosition().y > 32) {
			player.sprte.move(0, -480 / framelimit);
			getPlayerCoordinateForView(player.sprte.getPosition().x, player.sprte.getPosition().y);
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && player.sprte.getPosition().y < 2048 - 32) {
			player.sprte.move(0, 480 / framelimit);
			getPlayerCoordinateForView(player.sprte.getPosition().x, player.sprte.getPosition().y);
		}
		
		//стрельба
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (clock_gun.getElapsedTime().asSeconds() > 0.09) {
				b1.shape.setPosition(playerCenter);
				b1.currVelocity = aimDirNorm * b1.maxSpeed;
				bullets.push_back(Bullet(b1));
				gun.play();
				clock_gun.restart();
			}
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].shape.move(bullets[i].currVelocity);

			//до каких пор летит
			if (bullets[i].shape.getPosition().x < -(player.sprte.getPosition().x + WINDOW_WIDTH * 2 + 200) || bullets[i].shape.getPosition().x >(player.sprte.getPosition().x + WINDOW_WIDTH *2 + 200)
				|| bullets[i].shape.getPosition().y < -(player.sprte.getPosition().y + WINDOW_HEIGHT *2 + 200) || bullets[i].shape.getPosition().y > (player.sprte.getPosition().y + WINDOW_HEIGHT * 2 + 200))
			{
				bullets.erase(bullets.begin() + i);
			}
			else
			{
				//попадание

				for (size_t k = 0; k < enemies.size(); k++) {

					if (bullets[i].shape.getGlobalBounds().intersects(enemies[k].sprte.getGlobalBounds()))
					{
						bloodd.s_obj.setPosition(enemies[k].sprte.getPosition().x, enemies[k].sprte.getPosition().y);
						enemies[k].sprte.setPosition(Vector2f(rand() % MAP_SIZE_X - 30, rand() % MAP_SIZE_Y/2 - 30));
						bloodd.s_obj.setRotation(rand() % 360);
						float random_size = (rand() % 7) / 10 + 1;
						bloodd.s_obj.setScale(random_size, random_size);
						s_popadanie.play();
						bloods.push_back(bloodd);
						bullets.erase(bullets.begin() + i);
						break;
					}
				}
			}
		}

		if (frames_timer == 300) {
			bullet_ammos.s_obj.setPosition(Vector2f(rand() % MAP_SIZE_X - 30, rand() % MAP_SIZE_Y - 30));
			ammos.push_back(bullet_ammos);
			frames_timer = 0;
		}

		for (size_t i = 0; i < ammos.size(); i++) {
			if (ammos[i].s_obj.getGlobalBounds().intersects(player.sprte.getGlobalBounds())) {
				s_take_ammo.play();
				ammos.erase(ammos.begin() + i);
			}
		}

		//отрисовка
		window.setView(view); //позиция камеры
		window.clear(Color::Black);

		//отрисовка карты
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (TileMap[i][j] == ' ') {
					s_map.setTextureRect(IntRect(0, 0, 32, 32));
				}
				if (TileMap[i][j] == 's') {
					s_map.setTextureRect(IntRect(32, 0, 32, 32));
				}
				if (TileMap[i][j] == '0') {
					s_map.setTextureRect(IntRect(64, 0, 32, 32));
				}
				s_map.setPosition(j * 32,i * 32);
				window.draw(s_map);
			}
		}

		//отрисовка крови
		for (size_t k = 0; k < bloods.size(); k++) {
			window.draw(bloods[k].s_obj);
		}
		for (size_t l = 0; l < ammos.size(); l++) {
			window.draw(ammos[l].s_obj);
		}


		//отрисовка врагов
		for (int k = 0; k < enemies.size(); k++) {
			double enemy_x = enemies[k].sprte.getPosition().x;
			double enemy_y = enemies[k].sprte.getPosition().y;
			double player_x = player.sprte.getPosition().x;
			double player_y = player.sprte.getPosition().y;
			double enemy_center_x = enemy_x + 32;
			double enemy_center_y = enemy_y + 32;
			double player_x_center = player_x+32;
			double player_y_center = player_y+32;
			double rasstoyanie = sqrt(pow(enemy_center_x - player_x_center, 2) + pow(enemy_center_y - player_y_center, 2));
			double sinuss = (enemy_center_y - player_y_center)/rasstoyanie;
			double cosinuss = (enemy_center_x - player_x_center)/rasstoyanie;
			double enemy_speed = 1.5;
			double angle = asin(sinuss) * 57.3;
			if (enemy_x < player_x) {
				enemies[k].sprte.setRotation(180-angle);
			}
			else if (enemy_x >= player_x) {
				enemies[k].sprte.setRotation(angle);
			}
			enemies[k].sprte.move(-enemy_speed * cosinuss, -enemy_speed * sinuss);
			window.draw(enemies[k].sprte);
		}
		
		for (size_t i = 0; i < bullets.size(); i++)
		{
			window.draw(bullets[i].shape);
		}
		
		
		// данные
		double x_view_coord = view.getCenter().x; //получаем X координату центра камеры
		double y_view_coord = view.getCenter().y; //получаем Y координату центра камеры
		double x_text = x_view_coord - (WINDOW_WIDTH / 2 - 30) * zoom_current_var;
		//время
		mytime.setTime_size(3*zoom_current_var);
		mytime.setposition(x_text+ (WINDOW_WIDTH-200) / 2*zoom_current_var, y_view_coord - (WINDOW_HEIGHT / 2 - 10) * zoom_current_var);
		

		//фреймы
		frames_text.setString("Frames: " + std::to_string(total_frames));
		frames_text.setPosition(x_text, y_view_coord - (WINDOW_HEIGHT  / 2 - 10) * zoom_current_var);
		frames_text.setCharacterSize(20 * zoom_current_var);
		total_frames++;
		frames_timer++;

		//угол мышки
		mouse_pos_text.setString("Mouse angle: " + std::to_string(deg));
		mouse_pos_text.setPosition(x_text, y_view_coord - (WINDOW_HEIGHT / 2 - 40) * zoom_current_var);
		mouse_pos_text.setCharacterSize(20 * zoom_current_var);
		

		//x мышки на экране
		mouse_x_text.setString("Mouse X on Screen: " + std::to_string(Mouse::getPosition().x));
		mouse_x_text.setPosition(x_text, y_view_coord - (WINDOW_HEIGHT / 2 - 70) * zoom_current_var);
		mouse_x_text.setCharacterSize(20 * zoom_current_var);
		

		//y мышки
		mouse_y_text.setString("Mouse Y on Screen: " + std::to_string(Mouse::getPosition().y));
		mouse_y_text.setPosition(x_text, y_view_coord - (WINDOW_HEIGHT / 2 - 100) * zoom_current_var);
		mouse_y_text.setCharacterSize(20 * zoom_current_var);
		

		//x мышки на карте
		mouse_x_text_map.setString("Mouse X on map: " + std::to_string(x_view_coord + Mouse::getPosition().x - WINDOW_WIDTH / 2));
		mouse_x_text_map.setPosition(x_text, y_view_coord - (WINDOW_HEIGHT / 2 - 130) * zoom_current_var);
		mouse_x_text_map.setCharacterSize(20 * zoom_current_var);
		

		//y мышки на карте
		mouse_y_text_map.setString("Mouse Y on map: " + std::to_string(y_view_coord + Mouse::getPosition().y - WINDOW_HEIGHT / 2));
		mouse_y_text_map.setPosition(x_text, y_view_coord - (WINDOW_HEIGHT / 2 - 160) * zoom_current_var);
		mouse_y_text_map.setCharacterSize(20 * zoom_current_var);
		
		//x игрока
		player_x_text.setString("Player X: " + std::to_string(player.sprte.getPosition().x));
		player_x_text.setPosition(x_text, y_view_coord - (WINDOW_HEIGHT / 2 - 190) * zoom_current_var);
		player_x_text.setCharacterSize(20 * zoom_current_var);
		
		//y игрока
		player_y_text.setString("Player Y: " + std::to_string(player.sprte.getPosition().y));
		player_y_text.setPosition(x_text, y_view_coord - (WINDOW_HEIGHT / 2 - 220) * zoom_current_var);
		player_y_text.setCharacterSize(20 * zoom_current_var);
		
		//zoom
		zoom_text.setString("Zoom: " + std::to_string(zoom_current_var));
		zoom_text.setPosition(x_text, y_view_coord - (WINDOW_HEIGHT / 2 - 250) * zoom_current_var);
		zoom_text.setCharacterSize(20 * zoom_current_var); //консоль
		window.draw(player.sprte);
		mytime.drawTime(window);
		window.draw(frames_text);
		window.draw(mouse_pos_text);
		window.draw(mouse_x_text);
		window.draw(mouse_y_text);
		window.draw(mouse_x_text_map);
		window.draw(mouse_y_text_map);
		window.draw(player_x_text);
		window.draw(player_y_text);
		window.draw(zoom_text);

		window.display();
	}

	return 0;
}
