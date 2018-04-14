#include"engine/util/DebugFunctions.h"


void engine::debug::Print4x4Matrix(glm::mat4 mat)
{
	Print4x4Matrix(glm::value_ptr(mat));
}
void engine::debug::Print4x4Matrix(const float* mat)
{
	int index = 0;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << "[" << mat[index] << ", " << mat[index + 1] << ", " << mat[index + 2] << ", " << mat[index + 3] << "]\n";
		index += 4;
	}
}