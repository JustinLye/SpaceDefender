#include"engine/objects/Button.h"
namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace button {
Button::Button() :
	UIObject(),
	mTransform(new Transform()),
	mShape(nullptr),
	mText(nullptr),
	mRenderer(nullptr)
{

}

Button::~Button()
{

}

void Button::Init()
{

}

void Button::Render()
{
	mRenderer->Render(mShape, glm::value_ptr(mProjMat*mViewMat*mTransform->Model()));
	mText->Render();
}

void Button::Clicked(float xpos, float ypos)
{

}

void Button::Translate(const glm::vec3& translation)
{
	mTransform->Translate(translation);
}

void Button::Scale(const glm::vec3& scale)
{
	mTransform->Scale(scale);
}

void Button::FillColor(const glm::vec4& color)
{
	mRenderer->Color(color);
}

void Button::TextColor(const glm::vec4& color)
{
	mText->Color(color);
}

void Button::Projection(const glm::mat4& proj)
{
	mProjMat = proj;
}

void Button::View(const glm::mat4& view)
{
	mViewMat = view;
}

void Button::AddRenderer(Renderer* renderer)
{
	mRenderer = renderer;
}

void Button::AddDrawableObject(Shape* shape)
{
	mShape = shape;
}

void Button::AddText(Text* text)
{
	mText = text;
}

glm::vec4 Button::FillColor() const
{
	return mRenderer->Color();
}

glm::vec4 Button::TextColor() const
{
	return mText->Color();
}
} // namespace button
} // namespace impl
} // namespace objects
} // namespace engine
} // namespace sd_app