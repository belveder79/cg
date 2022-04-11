#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

std::vector<sf::Vector2f> CalcCubicBezier(
  const sf::Vector2f &start,
  const sf::Vector2f &startControl,
  const sf::Vector2f &endControl,
  const sf::Vector2f &end,
  const size_t numSegments)
  {
    std::vector<sf::Vector2f> ret;
    if (!numSegments) // Any points at all?
    return ret;

    ret.push_back(start); // First point is fixed
    float p = 1.f / numSegments;
    float q = p;
    for (size_t i = 1; i < numSegments; i++, p += q) // Generate all between
    ret.push_back(p * p * p * (end + 3.f * (startControl - endControl) - start) +
    3.f * p * p * (start - 2.f * startControl + endControl) +
    3.f * p * (startControl - start) + start);
    ret.push_back(end); // Last point is fixed
    return ret;
  }

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
