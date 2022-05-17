#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>

#include <vector>
#include <marching_cubes.h>

#define PI 3.14159265358979323846
#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))

#define VOL_X 256
#define VOL_Y 256
#define VOL_Z 256

glm::vec3 eye (0,0,10);
glm::vec3 la  (0,0,0);
glm::vec3 up  (0,1,0);

sf::Window window;

float mMouseXOrigin, mMouseYOrigin;

void glInit() {
	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);
}

template <class t_type>
class VoxelData {
    size_t m_width, m_height, m_depth;
    std::vector<t_type> m_data;


	void readVoxelData(std::string pPath) {
		std::ifstream infile;
		infile.open(pPath.c_str(), std::ios::binary | std::ios::in);
		if(!infile.is_open()) {
			std::cerr << "Error opening volume file <" << pPath << ">" << std::endl;
			exit(1);
		}
		m_data.resize(m_width * m_height * m_depth);
		infile.read(m_data.data(), m_width * m_height * m_depth * sizeof(t_type));
	}

  public:
    VoxelData(std::string path, int width, int height, int depth) : m_width(width), m_height(height), m_depth(depth)
    {
     	readVoxelData(path);
    }


    const t_type& operator()(int x, int y, int z) const {
        return m_data.at(x + y * m_width + z * m_width * m_height);
    }


    size_t width() const { return m_width; }
    size_t height() const { return m_height; }
    size_t depth() const { return m_depth; }
};



class Triangle {
	public:

		glm::vec3 v1;
		glm::vec3 v2;
		glm::vec3 v3;

		Triangle() {

		}

		Triangle(glm::vec3 p_v1, glm::vec3 p_v2, glm::vec3 p_v3) : v1(p_v1), v2(p_v2), v3(p_v3)
		{

		}

		const void draw() const {
			glBegin(GL_TRIANGLES);
				glVertex3fv((GLfloat*) &v1);
				glVertex3fv((GLfloat*) &v2);
				glVertex3fv((GLfloat*) &v3);
			glEnd();
		}

};

std::vector<Triangle> triangles;


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


void draw() {

	glColor3f(1,1,1);
	for(const auto &a : triangles) {
		a.draw();
	}
}


void MarchingCubes(const VoxelData<char> &vol, char density) {

	for(int i = 0; i < vol.depth(); i++) {
		for(int j = 0; j < vol.height(); j++) {
			for(int k = 0; k < vol.width(); k++) {

				int voxel = (int) vol(i,j,k);

				std::cout << "voxel<" << i << ", " << j << ", " << k << "> : " << voxel << std::endl;

				//START HERE!!!
				//Adding single triangle for demo
				triangles.push_back(Triangle(glm::vec3(0,0,5), glm::vec3(1,0,5), glm::vec3(1,1,5)));
				break;
			}
		}
	}

}


int  main()
{
	int WINDOW_X = 800;
	int WINDOW_Y = 600;
	float aspect = WINDOW_X / (float) WINDOW_Y;

    // create the window
    window.create(sf::VideoMode(WINDOW_X, WINDOW_Y), "Marching Cubes u08", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // load resources, initialize the OpenGL states, ...
	//More dataset at volvis.org
	VoxelData<char> voxels(std::string("../data/skull.raw"), 256, 256, 256);


	MarchingCubes(voxels, 100);

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

		// Other Transformations
		// glTranslatef( 0.1, 0.0, 0.0 );      // Not included
		// glRotatef( 180, 0.0, 1.0, 0.0 );    // Not included
	    // glScalef( 2.0, 2.0, 0.0 );          // Not included

        // draw...
		draw();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}
