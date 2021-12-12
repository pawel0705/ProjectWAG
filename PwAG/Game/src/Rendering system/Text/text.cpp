#include "pch.h"
#include "text.h"

Text::Text(int32_t x, int32_t y, std::string text, const Font& font, const glm::vec3& color)
	: x(x), y(y), text(std::move(text)), fontPtr(&font), color(color)
{
	setForNewText();
}

void Text::render(const ShaderProgram& shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fontPtr->atlasTextureID);
	shader.setVec3f("textColor", color);

	for(auto i = 0; i < text.size(); ++i)
	{
		VAOs[i].bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::setText(std::string newText)
{
	text = std::move(newText);
	setForNewText();
}

const std::string& Text::getText() const
{
	return text;
}

void Text::setColor(const glm::vec3& newColor)
{
	color = newColor;
}

const glm::vec3& Text::getColor() const
{
	return color;
}

void Text::setForNewText()
{
	VBOs.clear();
	VAOs.clear();

	VAOs.reserve(this->text.size());
	VBOs.reserve(this->text.size());

	float xPos = static_cast<float>(x);
	float yPos = static_cast<float>(y);

	for(const auto charInText : this->text)
	{
		const Font::Character& character = fontPtr->characters.at(charInText);

		float width = static_cast<float>(character.size.x);
		float height = static_cast<float>(character.size.y);

		float x1 = xPos + character.bearing.x;
		float y1 = yPos + character.bearing.y;

		float x2 = x1 + width;
		float y2 = y1 - height;

		float vertices[] = {
			x1,			y1,				character.atlasOffset.x / fontPtr->atlasSize.x,											0,
			x2,			y1,				character.atlasOffset.x / fontPtr->atlasSize.x + width / fontPtr->atlasSize.x,			0,
			x1,			y2,				character.atlasOffset.x / fontPtr->atlasSize.x,											height / fontPtr->atlasSize.y,

			x2,			y1,				character.atlasOffset.x / fontPtr->atlasSize.x + width / fontPtr->atlasSize.x,			0,
			x1,			y2,				character.atlasOffset.x / fontPtr->atlasSize.x,											height / fontPtr->atlasSize.y,
			x2,			y2,				character.atlasOffset.x / fontPtr->atlasSize.x + width / fontPtr->atlasSize.x,			height / fontPtr->atlasSize.y
		};

		VAOs.emplace_back();
		VAOs.back().bind();

		VBOs.emplace_back();
		VBOs.back().bind();

		VBOs.back().bufferData(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
		VBOs.back().setAttributesPointers(0, 4, GL_FLOAT, 4 * sizeof(float), nullptr);

		VBOs.back().unbind();
		VAOs.back().unbind();

		xPos += character.advance.x;
		yPos += character.advance.y;
	}
}
