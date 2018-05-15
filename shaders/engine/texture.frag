#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex;
uniform int mixInColor;
uniform vec4 mixColor;

void main()
{
	FragColor = texture(tex, TexCoord);
	if (mixInColor == 1)
	{
		FragColor *= mixColor;
	}
}