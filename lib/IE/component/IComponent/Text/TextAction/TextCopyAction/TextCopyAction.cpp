#include "TextCopyAction.hpp"

namespace ie {
	auto ProcessClipboard<sf::Clipboard>::set_string(sf::Clipboard&, sf::String const& str) -> void {
		sf::Clipboard::setString(str);
	}
	
	auto ProcessClipboard<sf::Clipboard>::get_string(sf::Clipboard&) -> sf::String {
		return sf::Clipboard::getString();
	}
}