#include "renderer.hpp"

#include <glad/glad.h>

opengl::renderer::renderer(uint16_t maxRects) : maxRects(maxRects), maxVertices(maxRects * 4), maxIndices(maxRects * 6)
{
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(vertex), 0, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(vertex), offsetof(vertex, position));

	auto indices = new uint32_t[maxIndices];
	auto offset = 0u;

	for (auto i = 0u; i < maxIndices; i += 6)
	{
		indices[i] = offset;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset;

		offset += 4;
	}

	glCreateBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndices * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	delete[] indices;

	// not finished
}

opengl::renderer::~renderer()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
