#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include "Vect.h"


const int R=20, N=100;
struct Ball
{
	Vect r, v;
	bool collided;
};


void set_data(Ball *balls)
{
	int n = sqrt(N);
	float distance = 600/n;
	int v_max = 80;

	float x, y;

	for (int i=0; i<N; ++i)
		{
			x = (int(i/n) + 0.5) * distance;
			y = (i%n + 0.5) * distance;
			balls[i].r = Vect(x,y);

			x = rand()%v_max - v_max/2;
			y = rand()%v_max - v_max/2;
			balls[i].v = Vect(x,y);
		}
}


void draw_ball(sf::RenderWindow *window, Ball *ball)
{
	sf::CircleShape circle(R);
	circle.setFillColor( (ball->collided ? sf::Color(255, 0, 0) : sf::Color(0, 0, 0)) );
	circle.setPosition(ball->r.x - R, ball->r.y - R);
	circle.setPointCount(50);
	window->draw(circle);
}


void move_ball(Ball *ball, float dt)
{
	ball->r.x += ball->v.x * dt;
	ball->r.y += ball->v.y * dt;
}


void wall_collide(Ball *ball)
{
	if (((ball->r.x < R) and (ball->v.x < 0)) or ((ball->r.x > 600 - R) and (ball->v.x > 0)))
	{
		ball->v.x *= -1;
	}
	if (((ball->r.y < R) and (ball->v.y < 0)) or ((ball->r.y > 600 - R) and (ball->v.y > 0)))
	{
		ball->v.y *= -1;
	}
}


void collide(Ball *ball1, Ball *ball2)
{
	Vect r12 = ball2->r - ball1->r;
	Vect v12 = ball2->v - ball1->v;
	float dist = r12.abs();
	if (dist > 2*R)
		return;
	Vect delta_v = r12 * ((r12*v12)/pow(dist, 2));
	if (delta_v * r12 > 0)
		return;

	ball1->v = ball1->v + delta_v;
	ball2->v = ball2->v - delta_v;
	ball1->collided = true;
	ball2->collided = true;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "100 balls");
	Ball *balls = new Ball[N];
	set_data(balls);

	sf::Clock clock;

	while (window.isOpen())
	{
		window.clear(sf::Color(255,255,255));

		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();

		for (int i=0; i<N; ++i)
		{
			draw_ball(&window, &balls[i]);
			move_ball(&balls[i], dt);
			wall_collide(&balls[i]);
			balls[i].collided = false;
			for (int j=0; j<N; ++j)
			{
				if (j>=i)
					continue;
				collide(&balls[i], &balls[j]);
			}
		}

		window.display();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	return 0;
}
