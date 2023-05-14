#pragma once

#include <SFML/Graphics.hpp>
#include "Zastava.h"

class Mreza
{
public:
	Mreza(sf::RenderWindow* window);
	void inicijaliziraj();
	void set_pozadina();
	short brojSusjeda_sredina(int i, int j);
	short brojSusjeda_goreDolje(int x, bool smjer);
	short brojSusjeda_lijevoDesno(int x, bool strana);
	short brojSusjeda_rub(char c);
	void set_z_sredina();
	void set_z_goreDolje(bool smjer);
	void set_z_lijevoDesno(bool strana);
	void set_z_rub();
	void preslozi();
	void draw();
private:
	sf::RenderWindow* window;
	sf::RectangleShape background;
	sf::CircleShape mreza[20][20];
	struct Zastava z;
};

