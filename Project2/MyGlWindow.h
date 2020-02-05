#pragma once

#ifndef MY_GL_WINDOW_H
#define MY_GL_WINDOW_H

#include <iostream>
#include "GL/glew.h"
#include <string>
#include "Loader.h"
#include "ColorCube.h"
#include "ModelView.h"
#include "Viewer.h"
#include "glm/gtc/type_ptr.hpp"
#include "CheckeredFloor.h"
#include "WireCube.h"
#include "RedLine.h"


class MyGlWindow {
public:
	MyGlWindow(float w, float h);
	~MyGlWindow();
	void draw(float rotate, float X_translation, float Y_translation, bool cube_view);
	void resize(int width, int height);

	Viewer *m_viewer;

private:
	ShaderProgram *m_shaderProgram;
	float m_width;
	float m_height;
	WireCube *m_wire_cube;
	ColorCube *m_color_cube;
	RedLine *m_line;

	Model m_model;
	CheckeredFloor *m_floor;

	void setupBuffer();
};

#endif