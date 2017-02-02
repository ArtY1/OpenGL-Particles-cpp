#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
	sf::Window window(sf::VideoMode(1000, 1000, 32), "OpenGL Particle test.");
	
	glViewport(0, 0, window.getSize().x, window.getSize().y);
	glMatrixMode()

	bool running = true;
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//update

		//draw

		//push the frame
		window.display();
	}

	return 0;
}