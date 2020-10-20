#pragma once

#ifndef _SHADER_H_
#define _SHADER_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>

class Shader
{
public:
	// the shader program id
	unsigned int ID;

	// ctor: reads paths to vert and frag shaders
	Shader(GLchar const* vertexPath, GLchar const* fragmentPath);

	// use/activate shader
	void use();
	void unuse();

	// utility uniform functions (?)
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 matValue) const;
};


#endif
