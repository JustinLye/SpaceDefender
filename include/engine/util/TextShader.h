#ifndef TEXT_SHADER_HEADER_INCLUDED
#define TEXT_SHADER_HEADER_INCLUDED

#include"engine/util/Constants.h"
#include"engine/util/ShaderProgram.h"

/** @addtogroup EngineUtil */
/*@{*/
class TextShader :
	public ShaderProgram
{
public:
	TextShader();
	virtual ~TextShader();
	virtual void Init() override;
};
/*@}*/

#endif
