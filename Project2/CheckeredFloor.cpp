#include "CheckeredFloor.h"



CheckeredFloor::CheckeredFloor(int size, int nSquare)
{
	_size = size;
	_nSquare = nSquare;
	setup();
}


CheckeredFloor::~CheckeredFloor()
{
}


void CheckeredFloor::setup()
{
	setup_vertex();

	glGenVertexArrays(1, &vaoHandle);		//create a vao
	glBindVertexArray(vaoHandle);			//"activate" or "im going to do somthing on here" 	

	//create vbos
	glGenBuffers(1, &vbo_floor_vertices);		//
	glBindBuffer(GL_ARRAY_BUFFER, vbo_floor_vertices);  //bind the vbo
	//create a buffer in GPU memory and copy the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertex_positions.size() * 4, _vertex_positions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,				//attribute number
		4,				//number of data for each vertex
		GL_FLOAT,		//data type
		GL_FALSE,		//is it normalized ?
		0,				//stride : gap between two adjacent vertex 
		0				//offset : gap from the starting address 
	);
	glEnableVertexAttribArray(0); // attrib number

	glGenBuffers(1, &vbo_floor_colors);		//
	glBindBuffer(GL_ARRAY_BUFFER, vbo_floor_colors);  //bind the vbo
	//create a buffer in GPU memory and copy the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertex_color.size() * 3, _vertex_color.data(), GL_STATIC_DRAW);
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

void CheckeredFloor::setup_vertex()
{
	float maxX = _size / ((float)2), maxY = _size / ((float)2);
	float minX = -_size / 2.f, minY = -_size/2.f;

	int x, y, i;

	float xp, yp, xd, yd;

	glm::vec3 color1 = glm::vec3(.7f, .7f, .7f);
	glm::vec3 color2 = glm::vec3(.3f, .3f, .3f);

	xd = (maxX - minX) / ((float)_nSquare);
	yd = (maxY - minY) / ((float)_nSquare);

	for (x = 0, xp = minX; x < _nSquare; x++, xp += xd) {
		for (y = 0, yp = minY, i = x; y < _nSquare; y++, yp += yd, i++) {
			_vertex_color.push_back(i % 2 == 1 ? color1 : color2);
			_vertex_color.push_back(i % 2 == 1 ? color1 : color2);
			_vertex_color.push_back(i % 2 == 1 ? color1 : color2);
			_vertex_color.push_back(i % 2 == 1 ? color1 : color2);
			_vertex_color.push_back(i % 2 == 1 ? color1 : color2);
			_vertex_color.push_back(i % 2 == 1 ? color1 : color2);
			_vertex_positions.push_back(glm::vec4(xp, 0, yp, 1));
			_vertex_positions.push_back(glm::vec4(xp, 0, yp + yd, 1));
			_vertex_positions.push_back(glm::vec4(xp + xd, 0, yp + yd, 1));
			_vertex_positions.push_back(glm::vec4(xp + xd, 0, yp, 1));
			_vertex_positions.push_back(glm::vec4(xp + xd, 0, yp + yd, 1));
			_vertex_positions.push_back(glm::vec4(xp, 0, yp, 1));
		}
	}
}

void CheckeredFloor::draw()
{
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, _nSquare * _nSquare * 6);

}