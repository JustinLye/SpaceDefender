#version 330 core
layout(location = 0) in vec3 vVertex;
uniform mat4 MVP;
void main()
{
	gl_Position = MVP*vec4(vVertex.xyz, 1.0f);
}