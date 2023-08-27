#pragma once

#include "../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../IAction.hpp"
#include "../../../SfmlEvents/MouseWheel/MouseWheel.hpp"

namespace ie {
	class WheelAction : public IAction {
	public:
		explicit WheelAction();
		
		virtual void update(sf::Vector2i mousePosition, int value) = 0;
		
		virtual WheelAction* copy() = 0;
	
	protected:
		bool active;
	};
}
