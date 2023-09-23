#include "TextVariables.hpp"

namespace ie {
	TextVariables::TextVariables(
		orl::Option<sf::Color> textColor,
		orl::Option<sf::Color> textSelectionColor,
		orl::Option<sf::Color> backgroundSelectionColor,
		orl::Option<sf::Color> inactiveTextSelectionColor,
		orl::Option<sf::Color> inactiveBackgroundSelectionColor,
		orl::Option<sf::Font*> font,
		orl::Option<sf::Text::Style> style,
		orl::Option<uint> size
	) :
		textColor(textColor),
		textSelectionColor(textSelectionColor),
		backgroundSelectionColor(backgroundSelectionColor),
		inactiveTextSelectionColor(inactiveTextSelectionColor),
		inactiveBackgroundSelectionColor(inactiveBackgroundSelectionColor),
		size(size),
		font(font),
		style(style),
		fontLineSpace(font && size ? orl::Option{font.some()->getLineSpacing(this->size.some())} : orl::Option<float>{}) {
	}
}