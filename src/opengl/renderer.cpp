#include "renderer.hpp"

#include <glad/glad.h>

opengl::renderer::renderer(const glm::mat4& projection, uint16_t maxRects) : maxRects(maxRects), maxVertices(maxRects * 4), maxIndices(maxRects * 6), shaders(std::make_unique<shader>())
{
	vertices.reserve(maxVertices);

	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(vertex), 0, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(vertex), reinterpret_cast<const void*>(offsetof(vertex, position)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, 0, sizeof(vertex), reinterpret_cast<const void*>(offsetof(vertex, color)));

	auto indices = new uint32_t[maxIndices];
	uint32_t offset = 0;

	for (uint32_t i = 0; i < maxIndices; i += 6)
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

	shaders->bind();
	shaders->setUniformMat4("projection", projection);
}

opengl::renderer::~renderer()
{
	shaders->unbind();

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void opengl::renderer::render()
{
	if (vertices.empty())
		return;

	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(vertex), vertices.data());
	glDrawElements(GL_TRIANGLES, static_cast<int>(vertices.size() + (2 * (vertices.size() / 4))), GL_UNSIGNED_INT, 0);

	vertices.clear();
}

void opengl::renderer::rect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
{
	if (vertices.size() >= maxVertices)
		render();

	const glm::vec2 positions[] = {
		{ position.x, position.y + size.y }, // bottom left
		{ position.x, position.y }, // top left
		{ position.x + size.x, position.y }, // top right
		{ position.x + size.x, position.y + size.y } // bottom right
	};

	for (uint16_t i = 0; i < 4; i++)
		vertices.emplace_back(positions[i], color);
}
