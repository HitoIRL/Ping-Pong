#pragma once

#include <cstdint>

namespace opengl
{
	class renderer
	{
	public:
		renderer(uint16_t maxRects = 1000);
		~renderer();
	private:
		const uint16_t maxRects, maxVertices, maxIndices;
		uint32_t vao, vbo, ebo;
	};
}