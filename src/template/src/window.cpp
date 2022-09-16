#include "template_pch.h"
#include "window.h"
#include "util.h"
#include "camera.h"

namespace templ8
{
	Window::Window( )
	{
		m_clear_color = glm::vec4( 245.f / 255.0f, 245.f / 255.0f, 220.f / 255.0f, 1.0f );
		m_cursor_last_pos = glm::vec2( 0 );
		m_scroll_offset = glm::vec2( 0 );
	}

	Window::~Window( )
	{
		glfwDestroyWindow( m_glfw_window );
	}

	/**
	 * OpenGL context initialisation
	 */
	bool Window::init( int width, int height, const char* win_name )
	{
		glfwInit( );
		// Window hints need to be set before the creation of the window. 
		// They function as additional arguments to glfwCreateWindow.
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
		m_glfw_window = glfwCreateWindow( width, height, win_name, nullptr, nullptr );

		if ( !m_glfw_window )
		{
			CRITICAL( "Failed to create window" );
			return false;
		}
		glfwSetWindowUserPointer( m_glfw_window, this );
		glfwMakeContextCurrent( m_glfw_window );

		// Load OpenGL extensions
		if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
		{
			CRITICAL( "Failed to initialize OpengGL context" );
			return false;
		}

		glEnable( GL_DEPTH_TEST );
		glEnable( GL_VERTEX_PROGRAM_POINT_SIZE );

		setupCallbacks( );

		return true;
	}

	bool Window::shouldClose( )
	{
		return glfwWindowShouldClose( m_glfw_window );
	}

	void Window::swapBuffers( )
	{
		glfwSwapBuffers( m_glfw_window );
	}

	/**
	 * Render the 3D scene
	 */
	void Window::clear( )
	{
		glClearColor( m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

#pragma region ////INPUT
	bool Window::isKeyPressed( int key )
	{
		return m_key_map[key] == GLFW_PRESS;
	}

	bool Window::isKeyReleased( int key)
	{
		return m_key_map[key] == GLFW_RELEASE;
	}

	bool Window::isKeyRepeat( int key )
	{
		return m_key_map[key] == GLFW_PRESS || m_key_map[key] == GLFW_REPEAT;
	}

	bool Window::isMousePressed( int button)
	{
		return m_mouse_map[button] == GLFW_PRESS;
	}

	bool Window::isMouseReleased( int button )
	{
		return m_mouse_map[button] == GLFW_RELEASE;
	}

	bool Window::isMouseRepeat( int button )
	{
		return m_mouse_map[button] == GLFW_PRESS || m_mouse_map[button] == GLFW_REPEAT;
	}
#pragma endregion

#pragma region ////CALLBACKS
	void Window::keyCallback( GLFWwindow* w, int key, int scancode, int action, int mods )
	{
		m_key_map[key] = action;
	}

	void Window::mouseCallback( GLFWwindow* window, int button, int action, int mods )
	{
		m_mouse_map[button] = action;
		std::cout << button << std::endl;
	}

	void Window::scrollCallback( GLFWwindow* w, double xoffset, double yoffset )
	{
		m_scroll_offset.x = xoffset;
		m_scroll_offset.y = yoffset;
		//m_camera->zoom( yoffset );
	}

	void Window::cursorCallback( GLFWwindow* w, double xpos, double ypos )
	{
		// The cursor can enter the window from different angels
		// The difference between two last positions could change dramatically
		if ( !m_reset_cursor )
			m_camera->cursor( xpos - m_cursor_last_pos.x, m_cursor_last_pos.y - ypos );

		m_cursor_last_pos.x = xpos;
		m_cursor_last_pos.y = ypos;
	}

	void Window::frameBufferCallback( GLFWwindow* window, int width, int height )
	{
		glViewport( 0, 0, width, height );
	}

	void Window::cursorEnterCallback( GLFWwindow* w, int entered )
	{
		m_reset_cursor = entered;
	}

	void Window::windowFocusCallback( GLFWwindow* w, int focused )
	{
		m_reset_cursor = focused;
		glfwSetWindowUserPointer( m_glfw_window, this );
		glfwMakeContextCurrent( m_glfw_window );
	}

	// Setup callbacks using lambdas so that member functions can be used
	void Window::setupCallbacks( )
	{
		// Key callback
		auto keyCallback = []( GLFWwindow* w, int key, int scancode, int action, int mods ) {
			auto window = static_cast<Window*>( glfwGetWindowUserPointer( w ) );
			window->keyCallback( w, key, scancode, action, mods );
		};
		glfwSetKeyCallback( m_glfw_window, keyCallback );

		// Mouse callback
		auto mouseCallback = []( GLFWwindow* w, int button, int action, int mods ) {
			auto window = static_cast<Window*>( glfwGetWindowUserPointer( w ) );
			window->mouseCallback( w, button, action, mods );
		};
		glfwSetMouseButtonCallback( m_glfw_window, mouseCallback );

		// Cursor callback
		auto cursorCallback = []( GLFWwindow* w, double xpos, double ypos ) {
			auto window = static_cast<Window*>( glfwGetWindowUserPointer( w ) );
			window->cursorCallback( w, xpos, ypos );
		};
		glfwSetCursorPosCallback( m_glfw_window, cursorCallback );

		// Cursor enter callback
		auto cursorEnterCallback = []( GLFWwindow* w, int entered ) {
			auto window = static_cast<Window*>( glfwGetWindowUserPointer( w ) );
			window->cursorEnterCallback( w, entered );
		};
		glfwSetCursorEnterCallback( m_glfw_window, cursorEnterCallback );

		// Scroll callback
		auto scrollCallback = []( GLFWwindow* w, double xoffset, double yoffset ) {
			auto window = static_cast<Window*>( glfwGetWindowUserPointer( w ) );
			window->scrollCallback( w, xoffset, yoffset );
		};
		glfwSetScrollCallback( m_glfw_window, scrollCallback );

		// Window focus callback
		auto windowfocusCallback = []( GLFWwindow* w, int focused ) {
			auto window = static_cast<Window*>( glfwGetWindowUserPointer( w ) );
			window->windowFocusCallback( w, focused );
		};
		glfwSetWindowFocusCallback( m_glfw_window, windowfocusCallback );

		// Framebuffer callback
		auto framebufferCallback = []( GLFWwindow* w, int width, int height ) {
			auto window = static_cast<Window*>( glfwGetWindowUserPointer( w ) );
			window->frameBufferCallback( w, width, height );
		};
		glfwSetFramebufferSizeCallback( m_glfw_window, framebufferCallback );
	}

#pragma endregion

} /* namespace templ8 */
