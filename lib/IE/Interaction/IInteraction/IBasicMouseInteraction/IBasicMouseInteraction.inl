#include "../../../Enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	template<typename T>
	void IBasicMouseInteraction<T>::update(sf::Vector2i mousePosition) {
		getLeftButtonAction().update(mousePosition, KeyHandler::isKeyPressed(Key::mouseLeft));
		getRightButtonAction().update(mousePosition, KeyHandler::isKeyPressed(Key::mouseRight));
	}
}
