#include <SFML/Graphics.hpp>
#include <cmath>
#include "Vect.h"


const float a = 80;

class Drawable
{
public:
	virtual draw(sf::RenderWindow window);
};


class myColor
{
public:
	int R, G, B;

	myColor()
	{
		this->R = 0;
		this->G = 0;
		this->B = 0;
	}

	myColor(int R, int G, int B)
	{
		this->R = R;
		this->G = G;
		this->B = B;
	}
};


class Ball: Drawable
{
public:
	Vect r, v;
	int R=50, hp=3;
	bool collided=false;
	myColor colors[3];
	Ball(int x, int y, myColor (*colors)[3])
	{
		this->r = Vect(x,y);
		for (int i=0; i<3; ++i)
		{
			this->colors[i] = *colors[i];
		}
	}

	void wallCollide()
	{
		int R = this->R;
		if (((this->r.x < R) and (this->v.x < 0)) or ((this->r.x > 600 - R) and (this->v.x > 0)))
		{
			this->v.x *= -1;
			this->hp -= 1;
		}
		if (((this->r.y < R) and (this->v.y < 0)) or ((this->r.y > 600 - R) and (this->v.y > 0)))
		{
			this->v.y *= -1;
			this->hp -= 1;
		}
	}

	void draw(sf::RenderWindow *window)
	{
		float circles = 200;
		myColor clr = this->colors[3 - this->hp];
		for (int i=circles; i>0; --i)
		{
			float darkness = sqrt(1-pow((i-1)/circles, 2));
			float radius = this->R * i / circles;

			sf::CircleShape circle(radius);
			circle.setFillColor(sf::Color(clr.R*darkness, clr.G*darkness, clr.B*darkness));
			circle.setPosition(this->r.x - radius, this->r.y - radius);
			circle.setPointCount(100);

			window->draw(circle);
		}
	}
};


class myText: Drawable
{
private:
	char *txt;
	int x, y;
public:
	myText(char *txt, int x, int y)
	{
		this->txt = txt;
		this->x = x;
		this->y = y;
	}

	void draw(sf::RenderWindow *window)
	{
		sf::Font font;
		font.loadFromFile("arial.ttf");
		sf::Text text_surface(txt, font, 50);
		text_surface.setFont(font);
		text_surface.setPosition(x,y);
		window->draw(text_surface);
	}
};	


void moveBall(Ball *ball, float dt)
{
	float k = 0.23;
	ball->v *= 1 - k*dt;
	ball->r += ball->v * dt;
}


void controllBall(Ball *ball, float dt, bool first=true)
{
	if (sf::Keyboard::isKeyPressed((first ? sf::Keyboard::A : sf::Keyboard::Left)))
		ball->v.x -= a*dt;
	if (sf::Keyboard::isKeyPressed((first ? sf::Keyboard::D : sf::Keyboard::Right)))
		ball->v.x += a*dt;
	if (sf::Keyboard::isKeyPressed((first ? sf::Keyboard::W : sf::Keyboard::Up)))
		ball->v.y -= a*dt;
	if (sf::Keyboard::isKeyPressed((first ? sf::Keyboard::S : sf::Keyboard::Down)))
		ball->v.y += a*dt;
}


void AI(Ball *ball1, Ball *ball2, float dt)
{
	if ((ball2->v.x > 0) and ((ball2->r.x - ball2->R) / (- ball2->v.x) > 3))
		ball2->v.x += a*dt;
	else if ((ball2->v.x > 0) and ((600 - ball2->R - ball2->r.x) / ball2->v.x < 3))
		ball2->v.x -= a*dt;
	else if ((ball2->v.y > 0) and ((ball2->r.y - ball1->R)/(- ball2->v.y) > 3))
		ball2->v.y += a*dt;
	else if ((ball2->v.y > 0) and ((600 - ball1->R - ball2->r.x) / ball2->v.x < 3))
		ball2->v.y -= a*dt;
	else {
		ball2->v.x += a * dt * cos((ball1->r.y - ball2->r.y)/(ball1->r.x - ball2->r.x)) * (ball2->r.x < ball1->r.x  ?  1  :  -1);
		ball2->v.y += a * dt * sin((ball1->r.y - ball2->r.y)/(ball1->r.x - ball2->r.x)) * (ball2->r.x < ball1->r.x  ?  1  :  -1);
	}
}


void collide(Ball *ball1, Ball *ball2)
{
	Vect r12 = ball2->r - ball1->r;
	Vect v12 = ball2->v - ball1->v;
	float dist = r12.abs();
	if (dist > ball1->R + ball2->R)
		return;
	Vect delta_v = r12 * ((r12*v12)/pow(dist, 2));
	if (delta_v * r12 > 0)
		return;

	ball1->v = ball1->v + delta_v;
	ball2->v = ball2->v - delta_v;
}


bool modeChoice(sf::RenderWindow *window, bool *quit)
{
	char choiceText[] = "press o for one player\npress t for two players";
	myText text(choiceText, 50, 200);

	window->clear(sf::Color(0,0,0));
	text.draw(window);
	window->display();

	while (window->isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			return false;

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				*quit = true;
			}
		}
	}
	return true;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Sumo");

	myColor colors1[3] = {myColor(0,255,0), myColor(0,150,150), myColor(0,0,255)};
	Ball ball1(100, 300, &colors1);

	myColor colors2[3] = {myColor(255,255,0), myColor(255,150,0), myColor(255,0,0)};
	Ball ball2(500, 300, &colors2);

	char *resultText;
	bool gameOver = false;
	bool quit = false;
	bool singlePlayer = modeChoice(&window, &quit);

	sf::Clock clock;
	while (not (gameOver or quit))
	{
		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();


		controllBall(&ball1, dt);
		if (singlePlayer)
			AI(&ball1, &ball2, dt);
		else
			controllBall(&ball2, dt, false);


		collide(&ball1, &ball2);
		ball1.wallCollide();
		ball2.wallCollide();
		moveBall(&ball1, dt);
		moveBall(&ball2, dt);


		window.clear(sf::Color(0,0,0));
		ball1.draw(&window);
		ball2.draw(&window);
		window.display();


		if (ball1.hp == 0)
		{
			char text[] = "player 2 is winner";
			resultText = text;
			gameOver = true;
		}
		if (ball2.hp == 0)
		{
			char text[] = "player 1 is winner";
			resultText = text;
			gameOver = true;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				quit = true;
			}
		}
	}


	if (not quit)
	{
		myText result = myText(resultText, 100, 200);
		result.draw(&window);
		window.display();
	}

	sf::Event event;
	while (not quit)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				quit = true;
			}
		}
	}

	return 0;
}
