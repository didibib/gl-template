#include "template_pch.h"
#include "window.h"

using namespace templ8;
using namespace std;

Window* window = new Window();

int main(int argc, char* argv[])
{
	logger::init();

	static float currentTime = 0, previousTime = 0;
	currentTime = glfwGetTime( );
	float m_delta_time = currentTime - previousTime;
	previousTime = currentTime;
	
	window->init(800, 600, "Window");
	while ( !window->shouldClose( ) )
	{
		window->clear( );

		window->swapBuffers( );
		glfwPollEvents( );
	}

	delete window;
	logger::shutdown();
	glfwTerminate( );
}