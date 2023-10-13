#include "IE/enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	template<typename T>
	void IBasicMouseInteraction<T>::update(sf::Vector2i mousePosition) {
		getLeftButtonAction().update(mousePosition, KeyHandler::isKeyPressed(Key::MouseLeft));
		getRightButtonAction().update(mousePosition, KeyHandler::isKeyPressed(Key::MouseRight));
	}
}