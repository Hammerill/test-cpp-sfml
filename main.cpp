#include <cstdlib>
#include <SFML/Graphics.hpp>

struct Particle
{
	size_t x;
	size_t y;
	size_t ix;
	size_t iy;
	size_t radius;
};

//Init a massive of shapes and particles
void initShapes(sf::CircleShape* obj, Particle* prt, size_t length, size_t scrW, size_t scrH)
{
	for (size_t i = 0; i < length; i++)
	{
		int radius = 20 + (rand() % 100);

		prt[i].radius = radius;
		prt[i].x = radius + (rand() % (scrW - radius));
		prt[i].y = radius + (rand() % (scrH - radius));
		prt[i].ix = 0;
		prt[i].iy = 0;

		obj[i].setRadius(radius);
		obj[i].setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
	}
}

//Calculates inertia X & Y for all elements in Particle massive
void inerShapes (Particle* prt, size_t length, float x = 0, float y = 0)
{
	for (size_t i = 0; i < length; i++)
	{
		prt[i].ix += x;
		prt[i].iy += y;
	}
}

//Calculates bounces, gravity, inertia and resistance for all elements in Particle massive
void bounceShapes(Particle* prt, size_t length, size_t scrW, size_t scrH)
{
	for (size_t i = 0; i < length; i++)
	{
		prt[i].iy += 0.2;
		prt[i].ix /= 1.01;

		prt[i].x += prt[i].ix;
		prt[i].y += prt[i].iy;

		if (prt[i].x > (float)scrW - prt[i].radius)
		{
			prt[i].x = (float)scrW - prt[i].radius;
			prt[i].ix = -prt[i].ix / 1.5;
			prt[i].iy = 0.95 + ((rand() % 5) / 100.0);
		}
		if (prt[i].x < (float)scrW - prt[i].radius)
		{
			prt[i].x = (float)prt[i].radius;
			prt[i].ix = -prt[i].ix / 1.5;
			prt[i].iy = 0.95 + ((rand() % 5) / 100.0);
		}
		if (prt[i].y > (float)scrH - prt[i].radius)
		{
			prt[i].y = (float)scrH - prt[i].radius;
			prt[i].iy = -prt[i].iy / 1.5;
			prt[i].ix = 0.95 + ((rand() % 5) / 100.0);
		}
		if (prt[i].y < (float)scrH - prt[i].radius)
		{
			prt[i].y = (float)prt[i].radius;
			prt[i].iy = -prt[i].iy / 1.5;
			prt[i].ix = 0.95 + ((rand() % 5) / 100.0);
		}
	}
}

//Updates coords in shapes massive from Particle massive
void updateShapes(sf::CircleShape* obj, Particle* prt, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		obj[i].setPosition(prt[i].x, prt[i].y);
	}
}

//Draws all shapes in shape massive (without clear and display)
void drawShapes(sf::CircleShape* obj, size_t length, sf::RenderWindow& win)
{
	for (size_t i = 0; i < length; i++)
	{
		
		int radius = 20 + (rand() % 100);
		
		obj[i].setRadius(radius);
		win.draw(obj[i]);
	}
}

int main()
{
	srand(time(NULL));

	const unsigned int screenwidth = 1400, screenheight = 760;

	size_t kol = 200;
	float iner = 0.5;

	sf::RenderWindow window(sf::VideoMode(screenwidth, screenheight), "Particles test");

	sf::CircleShape* shapes = new sf::CircleShape[kol];
	Particle* parameters = new Particle[kol];

	initShapes(shapes, parameters, kol, screenwidth, screenheight);
	updateShapes(shapes, parameters, kol);

	window.setVerticalSyncEnabled(true);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //-Y
		{
			inerShapes(parameters, kol, 0, -iner);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //-X
		{
			inerShapes(parameters, kol, -iner);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //+Y
		{
			inerShapes(parameters, kol, 0, iner);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //+X
		{
			inerShapes(parameters, kol, iner);
		}

		bounceShapes(parameters, kol, screenwidth, screenheight);
		updateShapes(shapes, parameters, kol);

		window.clear();
		drawShapes(shapes, kol, window);
		window.display();
	}

	delete[] parameters;
	delete[] shapes;

	return 0;
}