#version 330 core
  
layout(location = 0) in vec4 vVertex;	//<vec2 pos, vec2 tex>
out vec2 TexCoords;
uniform mat4 Projection;	


void main()
{  
	gl_Position = Projection*vec4(vVertex.xy,0.0f, 1.0f);
	TexCoords = vVertex.zw;
}