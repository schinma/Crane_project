#pragma once

#ifndef WIRE_CUBE_H
#define WIRE_CUBE_H

#include <iostream>
#include "GL/glew.h"
#include <string>
#include <vector>
#include "Loader.h"
#include "ModelView.h"

class WireCube {

private:

	GLuint vaoHandle;
	GLuint vbo_cube_vertices, vbo_cube_colors;
	GLuint ibo_cube_elements;
	Model *_model;

	void setup();

public:
	WireCube();
	void draw();

};


#endif
