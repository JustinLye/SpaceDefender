#version 330 core
layout(location = 0) out vec4 vFragColor;
uniform vec4 Color;
void main()
{
	vFragColor = Color;
}