#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

int main()
{
  // create the window
  sf::RenderWindow window(sf::VideoMode(800, 600), "Bezier Tutorial 04", sf::Style::Default, sf::ContextSettings(32));
  window.setVerticalSyncEnabled(true);

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


    // Create a vertex array for drawing; a line strip is perfect for this
    sf::VertexArray vertices(sf::LinesStrip, 0);

    vertices.append(sf::Vertex(sf::Vector2f(10, 10), sf::Color::White));
    vertices.append(sf::Vertex(sf::Vector2f(150, 150), sf::Color::White));

    // draw...
    window.draw(vertices);


    // end the current frame (internally swaps the front and back buffers)
    window.display();
  }

  // release resources...

  return 0;
}
