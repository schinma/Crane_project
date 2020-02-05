#include "WireCube.h"

WireCube::WireCube() {
	setup();
}

void WireCube::setup()
{
	GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0,
	};

	GLfloat cube_colors[] = {
		// front colors
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
	};

	GLushort cube_elements[36] = {
	0, 1, 2,        2, 3, 0,        1, 5, 6,
	6, 2, 1,        7, 6, 5,        5, 4, 7,
	4, 0, 3,        3, 7, 4,        4, 5, 1,
	1, 0, 4,        3, 2, 6,        6, 7, 3,
	};

	glGenVertexArrays(1, &vaoHandle);		//create a vao
	glBindVertexArray(vaoHandle);			//"activate" or "im going to do somthing on here" 	

	//create vbos
	glGenBuffers(1, &vbo_cube_vertices);		//
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);  //bind the vbo
	//create a buffer in GPU memory and copy the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8 * 3, cube_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,				//attribute number
		3,				//number of data for each vertex
		GL_FLOAT,		//data type
		GL_FALSE,		//is it normalized ?
		0,				//stride : gap between two adjacent vertex 
		0				//offset : gap from the starting address 
	);
	glEnableVertexAttribArray(0); // attrib number

	glGenBuffers(1, &vbo_cube_colors);		//
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);  //bind the vbo
	//create a buffer in GPU memory and copy the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8 * 3, cube_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(
		1,				//attribute number
		3,				//number of data for each vertex
		GL_FLOAT,		//data type
		GL_FALSE,		//is it normalized ? false -> we don't need it
		0,				//stride : gap between two adjacent vertex 
		0				//offset : gap from the starting address 
	);
	glEnableVertexAttribArray(1); // attrib number

	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);


	glBindVertexArray(0);			//unbinding

}

void WireCube::draw()
{
	glLineWidth(2.0);
	glBindVertexArray(vaoHandle);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_LINE_LOOP, size, GL_UNSIGNED_SHORT, 0);
}