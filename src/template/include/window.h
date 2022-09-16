#pragma once

namespace templ8
{
	class Shader;
	class Camera;
	class Program;

	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	class Window
	{
		GLFWwindow* m_glfw_window = nullptr;
		Camera* m_camera = nullptr;
		bool m_rotate_camera = false;
		bool m_reset_cursor = false;
		glm::vec4 m_clear_color;
		glm::vec2 m_cursor_last_pos;

		std::map<int, int> m_key_map;
		std::map<int, int> m_mouse_map;
		glm::vec2 m_scroll_offset;

		void setupCallbacks( );

	public:
		Window( );
		~Window( );
		Window( Window const& ) = delete;
		void operator=( Window const& ) = delete;

		bool init( int, int, const char* );
		void clear( );
		bool shouldClose( );
		void swapBuffers( );

		bool isKeyPressed( int );
		bool isKeyReleased( int );
		bool isKeyRepeat( int );
		bool isMousePressed( int );
		bool isMouseReleased( int );
		bool isMouseRepeat( int );

		float getScrollXOffset( ) { return m_scroll_offset.x; }
		float getScrollYOffset( ) { return m_scroll_offset.y; }

		void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
		void mouseCallback( GLFWwindow* window, int button, int action, int mods );
		void cursorCallback( GLFWwindow* window, double xpos, double ypos );
		void cursorEnterCallback( GLFWwindow* window, int entered );
		void windowFocusCallback( GLFWwindow* window, int focused );
		void scrollCallback( GLFWwindow* window, double xoffset, double yoffset );
		void frameBufferCallback( GLFWwindow* window, int width, int height );
	};
} /* namespace templ8 */