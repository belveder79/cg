#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#define GRID_RES_X 10
#define GRID_RES_Y 10

sf::RenderWindow window;

#define PI 3.14159265358979323846 
#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))

const int WINDOW_RES_X = 800;
const int WINDOW_RES_Y = 800;

const int GRID_CELLS_IN[2] = { 20, 20 };
const int GRID_CELLS_DIM[2] = { WINDOW_RES_X / GRID_CELLS_IN[0], WINDOW_RES_Y / GRID_CELLS_IN[1] };


void setGridCell(int x, int y) {
	sf::RectangleShape rectangle(sf::Vector2f(GRID_CELLS_DIM[0] - 2, GRID_CELLS_DIM[1] - 2));
	rectangle.setFillColor(sf::Color(255, 0, 0));
	rectangle.setPosition(x * GRID_CELLS_DIM[0] + 2, y * GRID_CELLS_DIM[1] + 2);
	window.draw(rectangle);
}


template <typename T>
sf::Vector2<T> operator *(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
	T X = left.x * right.x;
	T Y = left.y * right.y;
	return sf::Vector2<T>(X, Y);
}

void drawGrid(){

	//Draw Grid vertically
	for (int i = 0; i < GRID_CELLS_IN[0]; ++i){
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(i*GRID_CELLS_DIM[0], 0);
		lines[1].position = sf::Vector2f(i*GRID_CELLS_DIM[0], WINDOW_RES_Y);
		window.draw(lines);
	}

	//Draw Grid horizontally
	for (int i = 0; i < GRID_CELLS_IN[1]; ++i){
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(0, i*GRID_CELLS_DIM[1]);
		lines[1].position = sf::Vector2f(WINDOW_RES_X, i*GRID_CELLS_DIM[1]);
		window.draw(lines);
	}

}


void bresenham(int startx, int starty, int endx, int endy) {

	//TODO
	//Implement https://de.wikipedia.org/wiki/Bresenham-Algorithmus
	//			https://en.wikipedia.org/wiki/Bresenham's_line_algorithm
	//			https://www.youtube.com/watch?v=vlZFSzCIwoc
	// ...

	setGridCell(startx, starty);
	setGridCell(endx, endy);

}


int main()
{
	// create the window
	window.create(sf::VideoMode(WINDOW_RES_X, WINDOW_RES_Y), "Bresenham u07", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);

	// load resources, initialize the OpenGL states, ...



	sf::Vector2f line[2] = { 
		sf::Vector2f(2, 2),
		sf::Vector2f(14, 12)
	};

	std::vector<sf::Vertex> vertices_line;

	vertices_line.push_back((line[0] + sf::Vector2f(0.5f, 0.5f)) * sf::Vector2f(GRID_CELLS_DIM[0], GRID_CELLS_DIM[1]));
	vertices_line.push_back((line[1] + sf::Vector2f(0.5f, 0.5f)) * sf::Vector2f(GRID_CELLS_DIM[0], GRID_CELLS_DIM[1]));



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
		}



		window.clear();

		// draw...
		//Rasterize
		bresenham(line[0].x, line[0].y, line[1].x, line[1].y);

		//Draw grid cells
		drawGrid();

		//Draw line
		window.draw(vertices_line.data(), vertices_line.size(), sf::Lines);

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}