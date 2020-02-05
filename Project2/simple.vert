#version 440

layout(location = 0) in vec3 vertexPosition;  //set the attr number set in the glVertexAttribPointer function
layout(location = 1) in vec3 vertexColor;	  // same

out vec3 fColor; //for sending vexter color to Fragment Shader

uniform mat4 mvp;

void main()
{
	fColor = vertexColor;
	//we need to put NDC coordinates int gl_position
	gl_Position = mvp * vec4(vertexPosition, 1.0f);
}