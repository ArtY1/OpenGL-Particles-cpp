#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>

#include "Particle.h"

#define PARRAYHEIGHT 100 //width of the array of particles
#define PARRAYWIDTH 100 //height of the array of particles

#define INITIAL_POS_X 20
#define INITIAL_POS_Y 20
#define SPREAD 5 //distance between 2 particles next to each other

using namespace std;

int main()
{
	sf::Window window(sf::VideoMode(1000, 1000, 32), "OpenGL Particle test.");
	
	glViewport(0, 0, window.getSize().x, window.getSize().y); // init viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); glOrtho(0, window.getSize().x, window.getSize().y, 0, -1, 1);

	sf::Vector2f camPos(0.f, 0.f); // cam controled with WASD keys
	float zoom = 1.f; // zoom controlled with R and F keys

	vector<Particle> particles; //instances of all particles
	
	for (unsigned y = 0; y < PARRAYHEIGHT; ++y) //stroing particle instances in particles vector
	{
		for (unsigned x = 0; x < PARRAYWIDTH; ++x)
		{
			Particle p;
			p.setMass(1);
			p.SetPos( sf::Vector2f( x * SPREAD, y * SPREAD ) + sf::Vector2f( INITIAL_POS_X, INITIAL_POS_Y ) );  

			particles.push_back(p);
		}
	}

	sf::Clock deltaTime; // to keep track of updates ( = dt)
	float dt = 0.0000001; // init (dt = 1/framerat)

	//OpenGL draw setup
	float vertexCoords[2 * PARRAYHEIGHT * PARRAYWIDTH]; //a static coord array eg [1x, 1y, 2x, 2y, ..., nx, ny]
	unsigned char colours[3 * PARRAYHEIGHT * PARRAYWIDTH]; //a static array for colours eg [1r,1g,1b,2r,2g,...,nr,ng,nb]

	glEnable(GL_POINT_SMOOTH); // rounded dots
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //transparency blend
	glPointSize(2); //size of a dot

	bool running = true; //continue to run the program
	while (running)
	{
		//handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) 
			{
				case sf::Event::Closed:
					running = false;
					break;
				case sf::Event::Resized:
					glViewport(0, 0, event.size.width, event.size.height);
					break;

				default: ;
			}
		}

		//clear the buffer
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//update
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) //zoom control
			zoom += zoom*dt;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			zoom -= zoom*dt;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			camPos.y += 500 * dt;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			camPos.y -= 500 * dt;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			camPos.x += 500 * dt;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			camPos.x -= 500 * dt;


		for (unsigned i = 0; i < PARRAYHEIGHT * PARRAYWIDTH; ++i)
		{
			particles[i].updatePos(dt);
		}

		//draw
		for (unsigned i = 0; i < PARRAYHEIGHT * PARRAYWIDTH; ++i)
		{
			colours[3 * i] = 255;
			colours[3 * i + 1] = 255;
			colours[3 * i + 2] = 255;

			vertexCoords[2 * i] = particles[i].GetPos().x;
			vertexCoords[2 * i + 1] = particles[i].GetPos().y;
		}

		glPushMatrix(); //create a temp matrix to draw from

		glTranslatef(window.getSize().x / 2.f, window.getSize().y / 2.f, 0); //center the camera to the middle on the window 
		glScaled(zoom, zoom, zoom); //apply zoom around the center of the window

		glTranslatef(camPos.x, camPos.y, 0); // apply the camPos shift

		glEnableClientState(GL_VERTEX_ARRAY); // state rendering method
		glEnableClientState(GL_COLOR_ARRAY); 

		glVertexPointer(2, GL_FLOAT, 0, vertexCoords); //buffer the coords
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colours); //buffer the colours
		glDrawArrays(GL_POINTS, 0, PARRAYHEIGHT * PARRAYWIDTH); //actual draw call

			//draw clean-up
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glPopMatrix();

		glFlush();	

		//push the frame
		window.display();

		dt = deltaTime.restart().asSeconds(); //update dt
	}

	return 0;
}