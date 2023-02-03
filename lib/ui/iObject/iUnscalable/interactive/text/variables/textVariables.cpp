#include "textVariables.hpp"

namespace ui{
	TextVariables::TextVariables(sf::Color textColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor,
								 sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor,
								 sf::Font *font, sf::Text::Style style, uint size) :
								 TextColor(textColor), textSelectionColor(textSelectionColor),backgroundSelectionColor(backgroundSelectionColor),
								 inactiveTextSelectionColor(inactiveTextSelectionColor), inactiveBackgroundSelectionColor(inactiveBackgroundSelectionColor),
								 font(font), style(style), size(size), fontLineSpace(font ? font->getLineSpacing(size) : 0) {}
}