#include "template_pch.h"
#include "vertex_buffer.h"

namespace templ8
{
	VertexBuffer::VertexBuffer() :
		m_isBind(false), m_nVertices(0), m_nIndices(0),
		m_VAO(0), m_VBO(0), m_EBO(0)
	{
	}

	void VertexBuffer::create(const std::vector<Vertex>& vertices)
	{
		create(vertices, std::vector<unsigned int>());
	}

	void VertexBuffer::create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	{
		m_nVertices = vertices.size();
		m_nIndices = indices.size();

		TRACE("Creating buffers: [vertices:{}][indices:{}]", m_nVertices, m_nIndices);

		// Generate buffers
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		// Bind VAO
		glBindVertexArray(m_VAO);
		// Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_nVertices, &vertices[0], GL_STATIC_DRAW);

		if (!indices.empty())
		{
			// Bind EBO
			TRACE("Generating EBO");
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_nIndices, &indices[0], GL_STATIC_DRAW);
		}
		// Set attributes
		// Position (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glEnableVertexAttribArray(0);
		// Color (location = 1)
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
		glEnableVertexAttribArray(1);
		// UV (location = 2) 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
		glEnableVertexAttribArray(2);
		// Normal (location = 3
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(3);

		// Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored
		glBindVertexArray(0);
	}

	void VertexBuffer::Bind() const
	{
		glBindVertexArray(m_VAO);
		m_IsBind = true;
	}

	void VertexBuffer::Unbind() const
	{
		glBindVertexArray(0);
		m_IsBind = false;
	}

	void VertexBuffer::Draw() const
	{
		if (!m_IsBind)
		{
			ERROR("Forgot to bind the buffer");
			return;
		}
		if (m_EBO != 0)
		{
			glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_nVertices);
		}
	}
}