#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#define PI 3.14159265358979323846
#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))


glm::vec3 eye (0,0,10);
glm::vec3 la  (0,0,0);
glm::vec3 up  (0,1,0);

sf::Window window;

float mMouseXOrigin, mMouseYOrigin;

void glInit() {
	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);
}

void drawCube() {

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(   1.0,  1.0, 1.0 );
	glVertex3f(  0.5, -0.5, 0.5 );
	glVertex3f(  0.5,  0.5, 0.5 );
	glVertex3f( -0.5,  0.5, 0.5 );
	glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(  1.0,  0.0,  1.0 );
	glVertex3f( 0.5, -0.5, -0.5 );
	glVertex3f( 0.5,  0.5, -0.5 );
	glVertex3f( 0.5,  0.5,  0.5 );
	glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(   0.0,  1.0,  0.0 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(   0.0,  0.0,  1.0 );
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(   1.0,  0.0,  0.0 );
	glVertex3f(  0.5, -0.5, -0.5 );
	glVertex3f(  0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();



}

void handleKeyboard(sf::Event &event) {

	if ((event.type == sf::Event::KeyPressed))
	switch (event.key.code) {
		case sf::Keyboard::Escape:
		window.close();
		break;
		case sf::Keyboard::Up: {
			std::cout << "Up pressed" << std::endl;
		} break;
		case sf::Keyboard::Down: {
			std::cout << "Down pressed" << std::endl;
		} break;
		case sf::Keyboard::Left: {
			std::cout << "Left pressed" << std::endl;
		} break;
		case sf::Keyboard::Right: {
			std::cout << "Right pressed" << std::endl;
		} break;
		//..
	}
}


void handleMouse(sf::Event &event) {

	int mouseButtonPressed = 0;

	//Button pressed
	if(event.type == sf::Event::MouseButtonPressed) {
		switch (event.mouseButton.button) {
			case sf::Mouse::Left:
			std::cout << "Left Mouse Button pressed" << std::endl;
			mMouseXOrigin = (float) sf::Mouse::getPosition(window).x;
			mMouseYOrigin = (float) sf::Mouse::getPosition(window).y;
			mouseButtonPressed = 1;
			break;

			case sf::Mouse::Middle:
			std::cout << "Middle Mouse Button pressed" << std::endl;
			break;
			case sf::Mouse::Right:
			std::cout << "Right Mouse Button pressed" << std::endl;
			break;
		}

	}

	//Button released
	if(event.type == sf::Event::MouseButtonReleased) {
		switch (event.mouseButton.button) {
			case sf::Mouse::Left:

			std::cout << "Left Button released" << std::endl;
			break;
		}
	}

	//Mouse moved
	if(event.type == sf::Event::MouseMoved) {
		//LOG_OUTL("MOVING MOUSE");
		// if (mMouseXOrigin >= 0 || mMouseYOrigin >= 0) {
		// update deltaAngle
		// mMouseDeltaAngleX = (((sf::Mouse::getPosition(mWindow).x - mMouseXOrigin)/mWindow.getSize().x)*mouseSpeed);
		// mMouseDeltaAngleY = (((sf::Mouse::getPosition(mWindow).y - mMouseYOrigin)/mWindow.getSize().y)*mouseSpeed);

		//   if(mouseButtonPressed==1) {	//Left mouse button
		//camOrientation_.x += mMouseDeltaAngleX * MOUSE_SPEED;
		//camOrientation_.y += mMouseDeltaAngleY * MOUSE_SPEED;
		//  }

		//}	//Camera not null
	}	//mouse origin moved

}


int main()
{
	int WINDOW_X = 800;
	int WINDOW_Y = 600;
	float aspect = WINDOW_X / (float) WINDOW_Y;

	// create the window
	window.create(sf::VideoMode(WINDOW_X, WINDOW_Y), "OpenGL Tutorial 03", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);

	// load resources, initialize the OpenGL states, ...
	glInit();


	float near_plane = 0.1f;
	float far_plane = 1000.f;
	float fov = DEG2RAD(40.f);
	glm::mat4 projMatr = glm::perspective(fov, aspect, near_plane, far_plane);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&(projMatr[0][0]));

	// run the main loop
	bool running = true;
	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}

			handleKeyboard(event);
			handleMouse(event);

		}

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Reset transformations
		glMatrixMode(GL_MODELVIEW);
		glm::mat4 mview = glm::lookAt(eye, la, up);
		glLoadMatrixf(&(mview[0][0]));

		// draw...
		drawCube();

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}
