#pragma once

class Impassable_Objects
{

public:
	RectangleShape imp_shape;
	Impassable_Objects(float a, float b, size_t x, size_t y) {
		this->imp_shape.setSize(Vector2f(a, b));
		this->imp_shape.setOrigin(a / 2, b / 2);
		this->imp_shape.setPosition(x, y);
		this->imp_shape.setFillColor(Color::Blue);
	}
};

void InitPolygons(std::vector<Polygon>& Polygons);
void InitEdges(std::vector<Edge>& Edges, std::vector<Polygon>& Polygons);
void InitObjects(std::vector<Impassable_Objects>& ImpObjects);

void InitPolygons(std::vector<Polygon>& Polygons) {
	Polygons.reserve(17);
	// Square 1
	{
		Polygons.emplace_back(4);
		//Polygon p1(4);
		Polygon& p1 = Polygons[0];
		p1.Edges[0] = { sf::Vector2f(384.0f, 192.0f ), sf::Vector2f(480.0f, 192.0f) };
		p1.Edges[1] = { sf::Vector2f(480.0f, 192.0f), sf::Vector2f(480.0f, 288.0f ) };
		p1.Edges[2] = { sf::Vector2f(480.0f, 288.0f), sf::Vector2f(384.0f, 288.0f ) };
		p1.Edges[3] = { sf::Vector2f(384.0f, 288.0f), sf::Vector2f(384.0f, 192.0f ) };
	} 
	// Square 2
	{
		Polygons.emplace_back(4);
		auto& p2 = Polygons[1];
		p2.Edges[0] = { sf::Vector2f(384.0f, 416.0f), sf::Vector2f(480.0f, 416.0f) };
		p2.Edges[1] = { sf::Vector2f(480.0f, 416.0f), sf::Vector2f(480.0f, 512.0f) };
		p2.Edges[2] = { sf::Vector2f(480.0f, 512.0f), sf::Vector2f(384.0f, 512.0f) };
		p2.Edges[3] = { sf::Vector2f(384.0f, 512.0f), sf::Vector2f(384.0f, 416.0f) };
	}
	// Square 3
	{
		Polygons.emplace_back(4);
		auto& p3 = Polygons[2];
		p3.Edges[0] = { sf::Vector2f(384.0f, 640.0f), sf::Vector2f(480.0f, 640.0f) };
		p3.Edges[1] = { sf::Vector2f(480.0f, 640.0f), sf::Vector2f(480.0f, 736.0f) };
		p3.Edges[2] = { sf::Vector2f(480.0f, 736.0f), sf::Vector2f(384.0f, 736.0f) };
		p3.Edges[3] = { sf::Vector2f(384.0f, 736.0f), sf::Vector2f(384.0f, 640.0f) };
	}
	// Square 4
	{
		Polygons.emplace_back(4);
		auto& p4 = Polygons[3];
		p4.Edges[0] = { sf::Vector2f(384.0f, 864.0f), sf::Vector2f(480.0f, 864.0f) };
		p4.Edges[1] = { sf::Vector2f(480.0f, 864.0f), sf::Vector2f(480.0f, 960.0f) };
		p4.Edges[2] = { sf::Vector2f(480.0f, 960.0f), sf::Vector2f(384.0f, 960.0f) };
		p4.Edges[3] = { sf::Vector2f(384.0f, 960.0f), sf::Vector2f(384.0f, 864.0f) };
	}
	// Square 5
	{
		Polygons.emplace_back(4);
		auto& p5 = Polygons[4];
		p5.Edges[0] = { sf::Vector2f(384.0f, 1088.0f), sf::Vector2f(480.0f, 1088.0f) };
		p5.Edges[1] = { sf::Vector2f(480.0f, 1088.0f), sf::Vector2f(480.0f, 1184.0f) };
		p5.Edges[2] = { sf::Vector2f(480.0f, 1184.0f), sf::Vector2f(384.0f, 1184.0f) };
		p5.Edges[3] = { sf::Vector2f(384.0f, 1184.0f), sf::Vector2f(384.0f, 1088.0f) };
	}
	// Square 6
	{
		Polygons.emplace_back(4);
		auto& p6 = Polygons[5];
		p6.Edges[0] = { sf::Vector2f(384.0f, 1312.0f), sf::Vector2f(480.0f, 1312.0f) };
		p6.Edges[1] = { sf::Vector2f(480.0f, 1312.0f), sf::Vector2f(480.0f, 1408.0f) };
		p6.Edges[2] = { sf::Vector2f(480.0f, 1408.0f), sf::Vector2f(384.0f, 1408.0f) };
		p6.Edges[3] = { sf::Vector2f(384.0f, 1408.0f), sf::Vector2f(384.0f, 1312.0f) };
	}
	// Square 7
	{
		Polygons.emplace_back(4);
		auto& p7 = Polygons[6];
		p7.Edges[0] = { sf::Vector2f(384.0f, 1536.0f), sf::Vector2f(480.0f, 1536.0f) };
		p7.Edges[1] = { sf::Vector2f(480.0f, 1536.0f), sf::Vector2f(480.0f, 1632.0f) };
		p7.Edges[2] = { sf::Vector2f(480.0f, 1632.0f), sf::Vector2f(384.0f, 1632.0f) };
		p7.Edges[3] = { sf::Vector2f(384.0f, 1632.0f), sf::Vector2f(384.0f, 1536.0f) };
	}
	// Square 8
	{
		Polygons.emplace_back(4);
		auto& p8 = Polygons[7];
		p8.Edges[0] = { sf::Vector2f(384.0f, 1760.0f), sf::Vector2f(480.0f, 1760.0f) };
		p8.Edges[1] = { sf::Vector2f(480.0f, 1760.0f), sf::Vector2f(480.0f, 1856.0f) };
		p8.Edges[2] = { sf::Vector2f(480.0f, 1856.0f), sf::Vector2f(384.0f, 1856.0f) };
		p8.Edges[3] = { sf::Vector2f(384.0f, 1856.0f), sf::Vector2f(384.0f, 1760.0f) };
	}
	//--------------------
	// Square 9
	{
		Polygons.emplace_back(4);
		auto& p9 = Polygons[8];
		p9.Edges[0] = { sf::Vector2f(1376.0f, 192.0f), sf::Vector2f(1472.0f, 192.0f) };
		p9.Edges[1] = { sf::Vector2f(1472.0f, 192.0f), sf::Vector2f(1472.0f, 288.0f) };
		p9.Edges[2] = { sf::Vector2f(1472.0f, 288.0f), sf::Vector2f(1376.0f, 288.0f) };
		p9.Edges[3] = { sf::Vector2f(1376.0f, 288.0f), sf::Vector2f(1376.0f, 192.0f) };
	}
	// Square 10
	{
		Polygons.emplace_back(4);
		auto& p10 = Polygons[9];
		p10.Edges[0] = { sf::Vector2f(1376.0f, 416.0f), sf::Vector2f(1472.0f, 416.0f) };
		p10.Edges[1] = { sf::Vector2f(1472.0f, 416.0f), sf::Vector2f(1472.0f, 512.0f) };
		p10.Edges[2] = { sf::Vector2f(1472.0f, 512.0f), sf::Vector2f(1376.0f, 512.0f) };
		p10.Edges[3] = { sf::Vector2f(1376.0f, 512.0f), sf::Vector2f(1376.0f, 416.0f) };
	}
	// Square 11
	{
		Polygons.emplace_back(4);
		auto& p11 = Polygons[10];
		p11.Edges[0] = { sf::Vector2f(1376.0f, 640.0f), sf::Vector2f(1472.0f, 640.0f) };
		p11.Edges[1] = { sf::Vector2f(1472.0f, 640.0f), sf::Vector2f(1472.0f, 736.0f) };
		p11.Edges[2] = { sf::Vector2f(1472.0f, 736.0f), sf::Vector2f(1376.0f, 736.0f) };
		p11.Edges[3] = { sf::Vector2f(1376.0f, 736.0f), sf::Vector2f(1376.0f, 640.0f) };
	}
	// Square 12
	{
		Polygons.emplace_back(4);
		auto& p12 = Polygons[11];
		p12.Edges[0] = { sf::Vector2f(1376.0f, 864.0f), sf::Vector2f(1472.0f, 864.0f) };
		p12.Edges[1] = { sf::Vector2f(1472.0f, 864.0f), sf::Vector2f(1472.0f, 960.0f) };
		p12.Edges[2] = { sf::Vector2f(1472.0f, 960.0f), sf::Vector2f(1376.0f, 960.0f) };
		p12.Edges[3] = { sf::Vector2f(1376.0f, 960.0f), sf::Vector2f(1376.0f, 864.0f) };
	}
	// Square 13
	{
		Polygons.emplace_back(4);
		auto& p13 = Polygons[12];
		p13.Edges[0] = { sf::Vector2f(1376.0f, 1088.0f), sf::Vector2f(1472.0f, 1088.0f) };
		p13.Edges[1] = { sf::Vector2f(1472.0f, 1088.0f), sf::Vector2f(1472.0f, 1184.0f) };
		p13.Edges[2] = { sf::Vector2f(1472.0f, 1184.0f), sf::Vector2f(1376.0f, 1184.0f) };
		p13.Edges[3] = { sf::Vector2f(1376.0f, 1184.0f), sf::Vector2f(1376.0f, 1088.0f) };
	}
	// Square 14
	{
		Polygons.emplace_back(4);
		auto& p14 = Polygons[13];
		p14.Edges[0] = { sf::Vector2f(1376.0f, 1312.0f), sf::Vector2f(1472.0f, 1312.0f) };
		p14.Edges[1] = { sf::Vector2f(1472.0f, 1312.0f), sf::Vector2f(1472.0f, 1408.0f) };
		p14.Edges[2] = { sf::Vector2f(1472.0f, 1408.0f), sf::Vector2f(1376.0f, 1408.0f) };
		p14.Edges[3] = { sf::Vector2f(1376.0f, 1408.0f), sf::Vector2f(1376.0f, 1312.0f) };
	}
	// Square 15
	{
		Polygons.emplace_back(4);
		auto& p15 = Polygons[14];
		p15.Edges[0] = { sf::Vector2f(1376.0f, 1536.0f), sf::Vector2f(1472.0f, 1536.0f) };
		p15.Edges[1] = { sf::Vector2f(1472.0f, 1536.0f), sf::Vector2f(1472.0f, 1632.0f) };
		p15.Edges[2] = { sf::Vector2f(1472.0f, 1632.0f), sf::Vector2f(1376.0f, 1632.0f) };
		p15.Edges[3] = { sf::Vector2f(1376.0f, 1632.0f), sf::Vector2f(1376.0f, 1536.0f) };
	}
	// Square 16
	{
		Polygons.emplace_back(4);
		auto& p16 = Polygons[15];
		p16.Edges[0] = { sf::Vector2f(1376.0f, 1760.0f), sf::Vector2f(1472.0f, 1760.0f) };
		p16.Edges[1] = { sf::Vector2f(1472.0f, 1760.0f), sf::Vector2f(1472.0f, 1856.0f) };
		p16.Edges[2] = { sf::Vector2f(1472.0f, 1856.0f), sf::Vector2f(1376.0f, 1856.0f) };
		p16.Edges[3] = { sf::Vector2f(1376.0f, 1856.0f), sf::Vector2f(1376.0f, 1760.0f) };
	}
	// Walls
	{
		Polygons.emplace_back(4);
		auto& pw = Polygons[16];
		pw.Edges[0] = { Vector2f(0.0f, 0.0f), Vector2f(2048,	0.0f) };
		pw.Edges[1] = { Vector2f(2048, 0.0f), Vector2f(2048,	2048) };
		pw.Edges[2] = { Vector2f(2048, 2048), Vector2f(0.0f,	2048) };
		pw.Edges[3] = { Vector2f(0.0f, 2048), Vector2f(0.0f,	0.0f) };
	}
	
}

void InitEdges(std::vector<Edge>& Edges, std::vector<Polygon>& Polygons) {
	Edges.reserve(68);
	for (auto& p : Polygons) {
		for (uint32_t i = 0; i < p.EdgesCount; i++) {
			Edges.emplace_back(p.Edges[i]);
		}
	}
}

void InitObjects(std::vector<Impassable_Objects>& ImpObjects) {
	for (size_t i = 0; i < 8; i++) {
		Impassable_Objects a(96, 96, 384+48, 192+i*7*32+48);
		ImpObjects.push_back(a);
	}

	for (size_t i = 0; i < 8; i++) {
		Impassable_Objects a(96, 96, 1376 + 48, 192 + i * 7 * 32 + 48);
		ImpObjects.push_back(a);
	}
}

