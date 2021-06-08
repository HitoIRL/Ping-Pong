#pragma once

#include <string>
#include <unordered_map>

#include <glm/mat4x2.hpp>

namespace opengl
{
	class shader
	{
	public:
		shader();
		~shader();

		void setUniformMat4(const std::string& name, const glm::mat4& matrix);

		void bind() const;
		void unbind() const;
	private:
		int getUniformLocation(const std::string& name);

		uint32_t program;
		mutable bool binded;
		std::unordered_map<std::string, int> cache; // uniform location cache
	};
}