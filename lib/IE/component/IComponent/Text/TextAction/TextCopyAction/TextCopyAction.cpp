#include "TextCopyAction.hpp"

namespace ie {
	void ProcessClipboard<sf::Clipboard>::set_string(sf::Clipboard&, const sf::String& str) {
		sf::Clipboard::setString(str);
	}
	
	sf::String ProcessClipboard<sf::Clipboard>::get_string(sf::Clipboard&) {
		return sf::Clipboard::getString();
	}
}