#pragma once

#ifndef CHECKERED_FLOOR_H
#define CHECKERED_FLOOR_H

#include <iostream>
#include "GL/glew.h"
#include <string>
#include <vector>
#include "Loader.h"
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"

class CheckeredFloor
{
public:
	CheckeredFloor(int size, int nSquare);
	~CheckeredFloor();

	void draw();

private:

	void setup();
	void setup_vertex();

	GLuint vaoHandle;
	GLuint vbo_floor_vertices, vbo_floor_colors;
	int _size;
	int _nSquare;
	std::vector<glm::vec4> _vertex_positions;
	std::vector<glm::vec3> _vertex_color;
};

#endif
