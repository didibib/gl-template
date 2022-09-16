#pragma once

namespace templ8
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		void create(const std::vector<Vertex>& vertices);
		void create(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		void draw() const;
		void bind() const;
		void unbind() const;
	private:
		mutable bool m_isBind;
		int m_nVertices;
		int m_nIndices;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;
	};
}