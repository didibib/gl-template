#pragma once

namespace templ8
{
	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	class Window
	{
	public:
		Window( );
		~Window( );
		Window( Window const& ) = delete;
		void operator=( Window const& ) = delete;

		bool init( int, int, const char* );
		void clear( );
		bool shouldClose( );
		void swapBuffers( );
		// https://stackoverflow.com/questions/14189440/c-callback-using-class-member
		template<class T> int registerFrameBufferCb(
			T* const object,
			void( T::* const function )( const int&, const int& ) )
		{
			using namespace std::placeholders;
			m_frame_buffer_cb.emplace_back( std::bind( function, object, _1, _2 ) );
			return m_frame_buffer_cb.size( ) - 1; // return index of function
		}
		void unregisterFrameBufferCb( int index );

		bool getWidth( ) { return m_width; }
		bool getHeight( ) { return m_height; }
		std::string getName( ) { return m_title; }

		bool isKeyPressed( int );
		bool isKeyReleased( int );
		bool isKeyRepeat( int );
		bool isMousePressed( int );
		bool isMouseReleased( int );
		bool isMouseRepeat( int );

		float getScrollXOffset( ) { return m_scroll_offset.x; }
		float getScrollYOffset( ) { return m_scroll_offset.y; }


	private:
		GLFWwindow* m_glfw_window = nullptr;
		int m_width, m_height;
		std::string m_title;
		bool m_rotate_camera = false;
		bool m_reset_cursor = false;
		glm::vec4 m_clear_color;
		glm::vec2 m_cursor_last_pos;

		std::map<int, int> m_key_map;
		std::map<int, int> m_mouse_map;
		glm::vec2 m_scroll_offset;

		void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
		void mouseCallback( GLFWwindow* window, int button, int action, int mods );
		void cursorCallback( GLFWwindow* window, double xpos, double ypos );
		void cursorEnterCallback( GLFWwindow* window, int entered );
		void windowFocusCallback( GLFWwindow* window, int focused );
		void scrollCallback( GLFWwindow* window, double xoffset, double yoffset );

		std::vector<std::function<void( const int&, const int& )>> m_frame_buffer_cb;
		void frameBufferCallback( GLFWwindow* window, int width, int height );
		void setupCallbacks( );
	};
} /* namespace templ8 */