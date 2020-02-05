#include "RedLine.h"


RedLine::RedLine(glm::vec4 start, glm::vec4 end)
{
	m_start = start;
	m_end = end;
	setup();
}

void RedLine::setup()
{
	GLfloat line_vertices[] = {
		1.0, 1.0, 1.0,
		0.0, 0.0, 0.0,
	};

	GLfloat line_colors[] = {
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
	};

	glGenVertexArrays(1, &vaoHandle);		//create a vao
	glBindVertexArray(vaoHandle);			//"activate" or "im going to do somthing on here" 	

	//create vbos
	glGenBuffers(1, &vbo_line_vertices);		//
	glBindBuffer(GL_ARRAY_BUFFER, vbo_line_vertices);  //bind the vbo
	//create a buffer in GPU memory and copy the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * 3, line_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE,	0, 0);

	glEnableVertexAttribArray(0); // attrib number

	glGenBuffers(1, &vbo_line_colors);		//
	glBindBuffer(GL_ARRAY_BUFFER, vbo_line_colors);  //bind the vbo
	//create a buffer in GPU memory and copy the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * 3, line_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(
		1,				//attribute number
		3,				//number of data for each vertex
		GL_FLOAT,		//data type
		GL_FALSE,		//is it normalized ? false -> we don't need it
		0,				//stride : gap between two adjacent vertex 
		0				//offset : gap from the starting address 
	);
	glEnableVertexAttribArray(1); // attrib number

	glBindVertexArray(0);			//unbinding

}

void RedLine::draw()
{
	glLineWidth(2.0);
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_LINES, 2 / sizeof(GLuint), 2);
}