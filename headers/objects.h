#pragma once
void InitPolygons(std::vector<Polygon>& Polygons) {
	Polygons.reserve(20);

	// Square 0
	{
		Polygons.push_back(4);
		Polygon& p = Polygons[0];
		p.Edges[0] = { sf::Vector2f(384.0f, 192.0f), sf::Vector2f(480.0f, 192.0f) };
		p.Edges[1] = { sf::Vector2f(480.0f, 192.0f), sf::Vector2f(480.0f, 288.0f) };
		p.Edges[2] = { sf::Vector2f(480.0f, 288.0f), sf::Vector2f(384.0f, 288.0f) };
		p.Edges[3] = { sf::Vector2f(384.0f, 288.0f), sf::Vector2f(384.0f, 192.0f) };
	}
	
	// Square 1
	{
		Polygons.push_back(4);
		Polygon& p2 = Polygons[1];
		p2.Edges[0] = { sf::Vector2f(384.0f, 416.0f), sf::Vector2f(480.0f, 416.0f) };
		p2.Edges[1] = { sf::Vector2f(480.0f, 416.0f), sf::Vector2f(480.0f, 512.0f) };
		p2.Edges[2] = { sf::Vector2f(480.0f, 512.0f), sf::Vector2f(384.0f, 512.0f) };
		p2.Edges[3] = { sf::Vector2f(384.0f, 512.0f), sf::Vector2f(384.0f, 416.0f) };
	}


	// Square 2
	{
		Polygons.push_back(4);
		Polygon& p3 = Polygons[2];
		p3.Edges[0] = { sf::Vector2f(384.0f, 640.0f), sf::Vector2f(480.0f, 640.0f) };
		p3.Edges[1] = { sf::Vector2f(480.0f, 640.0f), sf::Vector2f(480.0f, 732.0f) };
		p3.Edges[2] = { sf::Vector2f(480.0f, 732.0f), sf::Vector2f(384.0f, 732.0f) };
		p3.Edges[3] = { sf::Vector2f(384.0f, 732.0f), sf::Vector2f(384.0f, 640.0f) };
	}


	// Square 3
	{
		Polygons.push_back(4);
		Polygon& p3 = Polygons[3];
		p3.Edges[0] = { sf::Vector2f(384.0f, 640.0f), sf::Vector2f(480.0f, 640.0f) };
		p3.Edges[1] = { sf::Vector2f(480.0f, 640.0f), sf::Vector2f(480.0f, 736.0f) };
		p3.Edges[2] = { sf::Vector2f(480.0f, 736.0f), sf::Vector2f(384.0f, 736.0f) };
		p3.Edges[3] = { sf::Vector2f(384.0f, 736.0f), sf::Vector2f(384.0f, 640.0f) };
	}

	// Square 4
	{
		Polygons.push_back(4);
		Polygon& p4 = Polygons[4];
		p4.Edges[0] = { sf::Vector2f(384.0f, 864.0f), sf::Vector2f(480.0f, 864.0f) };
		p4.Edges[1] = { sf::Vector2f(480.0f, 864.0f), sf::Vector2f(480.0f, 960.0f) };
		p4.Edges[2] = { sf::Vector2f(480.0f, 960.0f), sf::Vector2f(384.0f, 960.0f) };
		p4.Edges[3] = { sf::Vector2f(384.0f, 960.0f), sf::Vector2f(384.0f, 864.0f) };
	}

	// Square 5
	{
		// Creates Polygon with 4 vertices
		Polygons.push_back(4);
		Polygon& p5 = Polygons[5];
		p5.Edges[0] = { sf::Vector2f(384.0f, 1084.0f), sf::Vector2f(480.0f, 1084.0f) };
		p5.Edges[1] = { sf::Vector2f(480.0f, 1084.0f), sf::Vector2f(480.0f, 1180.0f) };
		p5.Edges[2] = { sf::Vector2f(480.0f, 1180.0f), sf::Vector2f(384.0f, 1180.0f) };
		p5.Edges[3] = { sf::Vector2f(384.0f, 1180.0f), sf::Vector2f(384.0f, 1084.0f) };
	}

	// Square 6
	{
		// Creates Polygon with 4 vertices
		Polygons.push_back(4);
		Polygon& p6 = Polygons[6];
		p6.Edges[0] = { sf::Vector2f(384.0f, 1308.0f), sf::Vector2f(480.0f, 1308.0f) };
		p6.Edges[1] = { sf::Vector2f(480.0f, 1308.0f), sf::Vector2f(480.0f, 1436.0f) };
		p6.Edges[2] = { sf::Vector2f(480.0f, 1436.0f), sf::Vector2f(384.0f, 1436.0f) };
		p6.Edges[3] = { sf::Vector2f(384.0f, 1436.0f), sf::Vector2f(384.0f, 1308.0f) };
	}


	// Square 7
	{
		Polygons.push_back(4);
		Polygon& p7 = Polygons[7];
		p7.Edges[0] = { sf::Vector2f(1376.0f, 192.0f), sf::Vector2f(1472.0f, 192.0f) };
		p7.Edges[1] = { sf::Vector2f(1472.0f, 192.0f), sf::Vector2f(1472.0f, 288.0f) };
		p7.Edges[2] = { sf::Vector2f(1472.0f, 288.0f), sf::Vector2f(1376.0f, 288.0f) };
		p7.Edges[3] = { sf::Vector2f(1376.0f, 288.0f), sf::Vector2f(1376.0f, 192.0f) };
	}

	// Square 8
	{
		Polygons.push_back(4);
		Polygon& p8 = Polygons[8];
		p8.Edges[0] = { sf::Vector2f(1376.0f, 416.0f), sf::Vector2f(1472.0f, 416.0f) };
		p8.Edges[1] = { sf::Vector2f(1472.0f, 416.0f), sf::Vector2f(1472.0f, 512.0f) };
		p8.Edges[2] = { sf::Vector2f(1472.0f, 512.0f), sf::Vector2f(1376.0f, 512.0f) };
		p8.Edges[3] = { sf::Vector2f(1376.0f, 512.0f), sf::Vector2f(1376.0f, 416.0f) };
	}
	
	// Walls
	{
		Polygons.emplace_back(4);
		Polygon& p9 = Polygons[1];
		p9.Edges[0] = { Vector2f(0.0f, 0.0f), Vector2f(2048, 0.0f) };
		p9.Edges[1] = { Vector2f(2048, 0.0f), Vector2f(2048, 2048) };
		p9.Edges[2] = { Vector2f(2048, 2048), Vector2f(0.0f,	2048) };
		p9.Edges[3] = { Vector2f(0.0f, 2048), Vector2f(0.0f,	0.0f) };
	}
}



void InitEdges(std::vector<Edge>& Edges, std::vector<Polygon>& Polygons) {
	Edges.reserve(200);
	for (auto& p : Polygons) {
		for (uint32_t i = 0; i < p.EdgesCount; i++) {
			Edges.push_back(p.Edges[i]);
		}
	}
}
