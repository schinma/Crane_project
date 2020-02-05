#version 440

in vec3 fColor; //getting color data from vertex shader

//we need to create at least one "out vec4" for settting fragment colors
out vec4 fragColor;  //r,g,b,a

void main()
{
		fragColor = vec4(fColor, 1.0);
}