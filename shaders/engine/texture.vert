#version 330 core
layout (location = 0) in vec3 vVertex;
layout (location = 1) in vec2 vTexCoord;
uniform mat4 MVP;
out vec2 TexCoord;
void main()
{
	gl_Position = MVP*vec4(vVertex, 1.0);
	TexCoord = vTexCoord;
}