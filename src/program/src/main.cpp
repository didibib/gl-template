#include "template_pch.h"
#include "window.h"
#include "camera.h"

using namespace templ8;
using namespace std;

Window* window = new Window( );
Camera* camera = new Camera( );

int main( int argc, char* argv[] )
{
	logger::init( );
	window->init( 800, 600, "Window" );
	camera->init( 90, window );

	while ( !window->shouldClose( ) )
	{
		static float currentTime = 0, previousTime = 0;
		currentTime = glfwGetTime( );
		float m_delta_time = currentTime - previousTime;
		previousTime = currentTime;

		window->clear( );


		window->swapBuffers( );
		glfwPollEvents( );
	}

	delete window;
	logger::shutdown( );
	glfwTerminate( );
}