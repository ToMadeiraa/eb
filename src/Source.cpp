#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <SFML/Graphics.hpp>


#include<iostream>
#include<math.h>
#include<vector>
#include<cstdlib>
#include <algorithm>
#include "../headers/Timer.hpp"
#include"../headers/map.h"
#include"../headers/view.h"
#include"../headers/loads.hpp"
#include"../headers/console.h"

//------------------

#include"../headers/Polygon.hpp"
#include"../headers/Point.hpp"

//------------------

#define WINDOW_WIDTH 1600
#define MAP_SIZE_X 2048
#define MAP_SIZE_Y 2048
#define WINDOW_HEIGHT 900
#define framelimit 120
#define PI 3.14159265f
#define SHADER_ON 0

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
//------------------

void InitPolygons(std::vector<Polygon>& Polygons);
void InitEdges(std::vector<Edge>& Edges, std::vector<Polygon>& Polygons);

//------------------
int main()
{  
	//------------------
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	//------------------

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SS 360", Style::Fullscreen, settings);
	view.reset(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
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



	//------------------
	
	std::vector<Polygon> Polygons;
	InitPolygons(Polygons);

	std::vector<Edge> Edges;
	InitEdges(Edges, Polygons);

	std::vector<Point> Points;
	Points.reserve(500);
	
	std::vector<Vertex> Vertices;
	Vertices.reserve(500);

	sf::Shader shadowShader;
	shadowShader.loadFromFile("shadow.vert", "shadow.frag");
	shadowShader.setUniform("u_resolution", Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

	sf::RenderTexture castTexture;
	castTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	castTexture.setSmooth(true);

	//------------------

	double zoom_current_var = 1;
	Event event;
	while (window.isOpen())
	{
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				window.close();
			}
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

		//-------------------------------------------------
		Vector2f mousePos(sf::Mouse::getPosition(window));
		shadowShader.setUniform("u_mouse", mousePos);
		Points.clear();
		for (auto& e0 : Edges) {
			// Because we have two points in every edge we need to iterate through it like this
			for (uint32_t i = 0; i < 2; i++) {
				// Calculating vector between mouse and point of our edge
				Vector2f rd((!i ? e0.Start : e0.End) - mousePos);
				float baseAng = atan2f(rd.y, rd.x);
				float ang = 0.0f;
				// For casting aditional rays
				for (uint32_t j = 0; j < 3; j++) {
					if (j == 0)	ang = baseAng - 0.0001f;
					if (j == 1)	ang = baseAng;
					if (j == 2)	ang = baseAng + 0.0001f;
					rd.x = 100.0f * cosf(ang);
					rd.y = 100.0f * sinf(ang);
					Vector2f minP;
					float		 minT1 = 9999.0f;
					float		 minAng = 0.0f;
					bool		 valid = false;

					for (auto& e1 : Edges) {
						// Algorithm detecting vector crossing
						// https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect

						Vector2f sd = e1.End - e1.Start;

						float t2 = (rd.x * (e1.Start.y - mousePos.y) + (rd.y * (mousePos.x - e1.Start.x))) / (sd.x * rd.y - sd.y * rd.x);

						float t1 = (e1.Start.x + sd.x * t2 - mousePos.x) / rd.x;

						if (t1 > 0 && t2 >= 0 && t2 <= 1.0f) {
							if (t1 < minT1) {
								// If vectors cross we add thier intersection point to our vector 

								minT1 = t1;
								minP = mousePos + rd * t1;
								minAng = atan2f(minP.y - mousePos.y, minP.x - mousePos.x);

								valid = true;
							}
						}
					}

					if (valid)
						Points.emplace_back(Vector2f(minP.x, minP.y), minAng);
				}
			}
		}

		// We need to sort our points based on thier angle to draw them correctly
		std::sort(Points.begin(), Points.end(), [&](const Point& a, const Point& b) { return a.Angle < b.Angle; });

		window.clear(Color(25, 94, 46));

		// Not sure about this part here maybe it can be done better
		castTexture.clear();
		Vertices.clear();

		// Center of triangle fan
		Vertices.emplace_back(mousePos);

		for (uint32_t i = 0; i < Points.size(); i++)
			Vertices.emplace_back(Points[i].Pos);

		if (!Points.empty())
			Vertices.emplace_back(Points[0].Pos);

		castTexture.draw(Vertices.data(), Vertices.size(), TriangleFan);
		castTexture.display();

		#if SHADER_ON
				window.draw(Sprite(castTexture.getTexture()), &shadowShader);
		#else
				window.draw(sf::Sprite(castTexture.getTexture()));
		#endif

		// Drawing shapes
		for (auto& p : Polygons)
			window.draw(p);

		//window.display();
		//-------------------------------------------------

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
		//появление патриков
		if (frames_timer == 300) {
			bullet_ammos.s_obj.setPosition(Vector2f(rand() % MAP_SIZE_X - 30, rand() % MAP_SIZE_Y - 30));
			ammos.push_back(bullet_ammos);
			frames_timer = 0;
		}
		//подбор патриков
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

void InitPolygons(std::vector<Polygon>& Polygons) {
	// Because of heap allocation in our Polygon class we need to 
	// reserve how many objects we want in our vector to avoid copy constructors

	Polygons.reserve(8); // <- it means 8 shapes (it's always better to reserve more then less)
	
	// Square 0
	{
		// Creates Polygon with 4 vertices
		Polygon p(4);
		Polygons.emplace_back(p);
		//Polygon& p_pointer = Polygons[0];

		// Note: start edge goes first
		p.Edges[0] = { sf::Vector2f(200.0f, 200.0f), sf::Vector2f(300.0f, 200.0f) };
		p.Edges[1] = { sf::Vector2f(300.0f, 200.0f), sf::Vector2f(300.0f, 300.0f) };
		p.Edges[2] = { sf::Vector2f(300.0f, 300.0f), sf::Vector2f(200.0f, 300.0f) };
		p.Edges[3] = { sf::Vector2f(200.0f, 300.0f), sf::Vector2f(200.0f, 200.0f) };
	}

	// Square 3 (Walls)
	{
		//Polygon& p = Polygons.emplace_back(4);
		Polygon p(4);
		Polygons.emplace_back(p);
		//Polygon& p_pointer = Polygons[0];

		p.Edges[0] = { sf::Vector2f(0.0f,		  0.0f), sf::Vector2f(WINDOW_WIDTH, 0.0f) };
		p.Edges[1] = { sf::Vector2f(WINDOW_WIDTH, 0.0f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT) };
		p.Edges[2] = { sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT), sf::Vector2f(0.0f,		 WINDOW_HEIGHT) };
		p.Edges[3] = { sf::Vector2f(0.0f,		  WINDOW_HEIGHT), sf::Vector2f(0.0f,		 0.0f) };
	}
}



void InitEdges(std::vector<Edge>& Edges, std::vector<Polygon>& Polygons) {
	Edges.reserve(50);

	for (auto& p : Polygons)
		for (uint32_t i = 0; i < p.EdgesCount; i++)
			Edges.push_back(p.Edges[i]);
}