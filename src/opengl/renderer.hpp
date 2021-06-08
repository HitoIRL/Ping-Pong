#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <glm/mat4x2.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "shader.hpp"

namespace opengl
{
	class renderer
	{
	public:
		renderer(const glm::mat4& projection, uint16_t maxRects = 1000);
		~renderer();

		void render();
		
		void rect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
	private:
		struct vertex
		{
			glm::vec2 position;
			glm::vec3 color;
		};

		const uint16_t maxRects, maxVertices, maxIndices;
		uint32_t vao, vbo, ebo;
		std::vector<vertex> vertices;
		std::unique_ptr<shader> shaders;
	};
}