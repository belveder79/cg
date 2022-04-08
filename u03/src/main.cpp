#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL Tutorial 03", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // load resources, initialize the OpenGL states, ...

    int angle, i = 0;

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
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
    		GLfloat color_array[] = { 0.0,0.0,1.0 };
    		glColor3fv(color_array);

    		glMatrixMode(GL_MODELVIEW);
    		glLoadIdentity();

        glBegin(GL_TRIANGLES);
        glVertex3f(-0.5, -0.5, 0.0);
    		glVertex3f(-0.75, -0.5, 0.0);
    		glVertex3f(-0.75, -0.75, 0.0);
        glEnd();

        glColor3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glVertex3f(0.5,  0.5, 0.0);
        glVertex3f(0.75, 0.5, 0.0);
        glVertex3f(0.75, 0.75, 0.0);
        glVertex3f(0.5,  0.75, 0.0);
        glEnd();

        angle = i++ % 360;

        glColor3f(1.0,1.0,0.0);
        glRotatef(angle, 0.0, 0.0, 1.0);
        glTranslatef(-0.3, 0.3, 0.0);
        glBegin(GL_POLYGON);
        glVertex3f(-0.1,  0.1, 0.0);
        glVertex3f(-0.1, -0.1, 0.0);
        glVertex3f(0.1, -0.1, 0.0);
        glVertex3f(0.1,  0.1, 0.0);
        glEnd();

        glColor3f(0.0,1.0,1.0);
        glLoadIdentity();
        glTranslatef(-0.3, 0.3, 0.0);
        glRotatef(angle, 0.0, 0.0, 1.0);

        glBegin(GL_POLYGON);
        glVertex3f(-0.1,  0.1, 0.0);
        glVertex3f(-0.1, -0.1, 0.0);
        glVertex3f(0.1, -0.1, 0.0);
        glVertex3f(0.1,  0.1, 0.0);
        glEnd();

        //glTranslatef(-0.625, 0.625, 0.0);
        //glRotatef(angle, 0.0, 0.0, 1.0);


//         //glTranslatef(-0.5, 0.0, 0.0);
//     		//glRotatef(45.0, 0.0, 0.0, 1.0);
//     		//glRotatef(45.0, 0.0, 0.0, 1.0);
//     		//glTranslatef(-0.5, 0.0, 0.0);
//     		glBegin(GL_POLYGON);
//     		glVertex3f(0.25, 0.25, 0.0);
//     		glVertex3f(0.75, 0.25, 0.0);
//     		glVertex3f(0.75, 0.75, 0.0);
//     		glVertex3f(0.25, 0.75, 0.0);
//     		glVertex3f(0.1, 0.5, 0.0);
//         glEnd();
//
//         angle = i++ % 360;
//         // glTranslatef(0.0, 0.4, 0.0);
//         // glRotatef(angle, 0.0, 0.0, 1.0);
//         glBegin(GL_POLYGON);
//         glColor3f(1.0,0.0,0.0);
//         glVertex3f(-0.25, -0.25, 0.0);
//     		glVertex3f(-0.75, -0.25, 0.0);
//     		glVertex3f(-0.75, -0.75, 0.0);
//     		glEnd();



    		glFlush();

        // end the current frame (internally swaps the front and back buffers)
        window.display();

        i++;
    }

    // release resources...

    return 0;
}
