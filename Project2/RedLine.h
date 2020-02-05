#pragma once

#ifndef RED_LINE
#define RED_LINE

#include <iostream>
#include "GL/glew.h"
#include <string>
#include <vector>
#include "Loader.h"
#include "ModelView.h"

class RedLine {

private:
	GLuint vaoHandle;
	GLuint vbo_line_vertices, vbo_line_colors;
	glm::vec4 m_start;
	glm::vec4 m_end;

	void setup();

public:
	RedLine(glm::vec4 start, glm::vec4 end);
	void update(glm::vec4 start, glm::vec4 end);
	void draw();

};


#endif 