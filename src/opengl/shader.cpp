#include "shader.hpp"

#include <glad/glad.h>

constexpr auto vertexSource = R"glsl(
#version 460 core

in vec4 position;
in vec3 color;

out vec3 v_color;

uniform mat4 projection;

void main()
{
	gl_Position = projection * position;

	v_color = color;
}
)glsl";

constexpr auto fragmentSource = R"glsl(
#version 460 core

in vec3 v_color;

out vec4 color;

void main()
{
	color = vec4(v_color, 1.0);
}
)glsl";

opengl::shader::shader() : program(glCreateProgram()), binded(false)
{
	auto createShader = [this](const char* source, uint32_t type)
	{
		auto id = glCreateShader(type);
		glShaderSource(id, 1, &source, 0);
		glCompileShader(id);
		glAttachShader(program, id);
		glDeleteShader(id);
	};

	createShader(vertexSource, GL_VERTEX_SHADER);
	createShader(fragmentSource, GL_FRAGMENT_SHADER);

	glLinkProgram(program);
	glValidateProgram(program);
}

opengl::shader::~shader()
{
	glDeleteProgram(program);
}

void opengl::shader::setUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, 0, &matrix[0][0]);
}

void opengl::shader::bind() const
{
	if (binded)
		return;

	glUseProgram(program);

	binded = true;
}

void opengl::shader::unbind() const
{
	if (!binded)
		return;

	glUseProgram(0);

	binded = false;
}

int opengl::shader::getUniformLocation(const std::string& name)
{
	if (cache.find(name) != cache.end())
		return cache[name];

	const auto location = glGetUniformLocation(program, name.c_str());

	// log if location = -1

	cache[name] = location;
	return location;
}
