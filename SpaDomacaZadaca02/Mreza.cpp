#include "Mreza.h"

Mreza::Mreza(sf::RenderWindow* window)
{
	this->window = window;
}

void Mreza::inicijaliziraj()
{
	srand(time(nullptr));

	set_pozadina();
	window->draw(this->background);

	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		int y = 0;
		for (int j = 0; j < 20; j++)
		{

			int randy = rand() % 4;
			mreza[i][j].setRadius(19);
			if (!randy)
			{
				mreza[i][j].setFillColor(sf::Color::Red);
				z.stanje[i][j] = true;
			}
			else
			{
				mreza[i][j].setFillColor(sf::Color::Green);
				z.stanje[i][j] = false;
			}
			mreza[i][j].setPosition(sf::Vector2f(x, y));
			y += 40;
			window->draw(mreza[i][j]);
		}
		x += 40;
	}
}

void Mreza::set_pozadina()
{
	background.setSize(sf::Vector2f(800.f, 800.f));
	background.setFillColor(sf::Color::Green);
	background.setOrigin(0, 0);
}

short Mreza::brojSusjeda_sredina(int i, int j)
{
	short broj = 0;
	for (int k = i - 1; k <= i + 1; k++)
	{
		for (int c = j - 1; c <= j + 1; c++)
		{
			if (z.stanje[k][c])
			{
				broj++;
			}
		}
	}

	return broj;
}

short Mreza::brojSusjeda_goreDolje(int x, bool smjer)
{
	int goreDolje, r;
	if (smjer)
	{
		goreDolje = 0;
		r = 1;
	}
	else
	{
		goreDolje = 19;
		r = 18;
	}

	short broj = 0;
	if (z.stanje[goreDolje][x - 1])
	{
		broj++;
	}
	if (z.stanje[goreDolje][x + 1])
	{
		broj++;
	}
	for (int i = x - 1; i <= x + 1; i++)
	{
		if (z.stanje[r][i])
		{
			broj++;
		}
	}
	return broj;
}

short Mreza::brojSusjeda_lijevoDesno(int x, bool strana)
{
	int lijevoDesno;
	int r;
	if (strana)
	{
		lijevoDesno = 0;
		r = 1;
	}
	else
	{
		lijevoDesno = 19;
		r = 18;
	}

	short broj = 0;
	if (z.stanje[x - 1][lijevoDesno])
	{
		broj++;
	}
	if (z.stanje[x + 1][lijevoDesno])
	{
		broj++;
	}
	for (int i = x - 1; i <= x + 1; i++)
	{
		if (z.stanje[i][r])
		{
			broj++;
		}
	}
	return broj;
}

short Mreza::brojSusjeda_rub(char c)
{
	int broj = 0;
	switch (c)
	{
	case 'c':
		if (z.stanje[0][1])
		{
			broj++;
		}
		if (z.stanje[1][0])
		{
			broj++;
		}
		if (z.stanje[1][1])
		{
			broj++;
		}
		break;
	case 'd':
		if (z.stanje[0][18])
		{
			broj++;
		}
		if (z.stanje[1][19])
		{
			broj++;
		}
		if (z.stanje[1][18])
		{
			broj++;
		}
		break;
	case 'a':
		if (z.stanje[19][1])
		{
			broj++;
		}
		if (z.stanje[18][0])
		{
			broj++;
		}
		if (z.stanje[18][1])
		{
			broj++;
		}
		break;
	case 'b':
		if (z.stanje[19][18])
		{
			broj++;
		}
		if (z.stanje[18][19])
		{
			broj++;
		}
		if (z.stanje[18][18])
		{
			broj++;
		}
		break;
	default:
		break;

		return broj;
	}
}

void Mreza::set_z_sredina()
{
	short broj = brojSusjeda_rub('c');
	if (broj < 2)
	{
		z.novoStanje[0][0] = false;
	}
	else if (broj == 3)
	{
		z.novoStanje[0][0] = true;
	}

	broj = brojSusjeda_rub('d');
	if (broj < 2)
	{
		z.novoStanje[0][19] = false;
	}
	else if (broj == 3)
	{
		z.novoStanje[0][19] = true;
	}

	broj = brojSusjeda_rub('a');
	if (broj < 2)
	{
		z.novoStanje[19][0] = false;
	}
	else if (broj == 3)
	{
		z.novoStanje[19][0] = true;
	}

	broj = brojSusjeda_rub('b');
	if (broj < 2)
	{
		z.novoStanje[19][19] = false;
	}
	else if (broj == 3)
	{
		z.novoStanje[19][19] = true;
	}
}

void Mreza::set_z_goreDolje(bool smjer)
{
	int goreDolje;
	if (smjer)
	{
		goreDolje = 0;
	}
	else
	{
		goreDolje = 19;
	}

	for (int x = 1; x < 19; x++)
	{
		short broj = brojSusjeda_goreDolje(x, true);
		if (broj < 2)
		{
			z.novoStanje[goreDolje][x] = false;
		}
		else if (broj == 3)
		{
			z.novoStanje[goreDolje][x] = true;
		}
		else if (broj > 3)
		{
			z.novoStanje[goreDolje][x] = false;
		}

	}
}

void Mreza::set_z_lijevoDesno(bool strana)
{
	int lijevoDesno;
	if (strana)
	{
		lijevoDesno = 19;
	}
	else
	{
		lijevoDesno = 0;
	}

	for (int x = 1; x < 19; x++)
	{
		short broj = brojSusjeda_goreDolje(x, true);
		if (broj < 2)
		{
			z.novoStanje[x][lijevoDesno] = false;
		}
		else if (broj == 3)
		{
			z.novoStanje[x][lijevoDesno] = true;
		}
		else if (broj > 3)
		{
			z.novoStanje[x][lijevoDesno] = false;
		}
	}
}

void Mreza::set_z_rub()
{
	int broj = 0;
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 19; j++)
		{
			broj = brojSusjeda_sredina(i, j);

			switch (broj)
			{
			case 0:
			case 1:
				z.novoStanje[i][j] = false;
				broj = 0;
				break;
			case 2:
				broj = 0;
				break;
			case 3:
				z.novoStanje[i][j] = true;
				broj = 0;
				break;
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				z.novoStanje[i][j] = false;
				broj = 0;
				break;
			default:
				break;
			}

		}
	}
}

void Mreza::preslozi()
{
	set_z_sredina();
	set_z_goreDolje(true);
	set_z_goreDolje(false);
	set_z_lijevoDesno(true);
	set_z_lijevoDesno(false);
	set_z_rub();

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			z.stanje[i][j] = z.novoStanje[i][j];
		}
	}
}

void Mreza::draw()
{
	set_pozadina();
	window->draw(this->background);
	preslozi();

	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		int y = 0;
		for (int j = 0; j < 20; j++)
		{
			if (z.stanje[i][j])
			{
				mreza[i][j].setFillColor(sf::Color::Red);
			}
			else
			{
				mreza[i][j].setFillColor(sf::Color::Green);
			}
			window->draw(mreza[i][j]);
		}
	}
}

