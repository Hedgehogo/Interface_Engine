#pragma once

#include "IE/modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../IAction.hpp"
#include "../../../sfml-events/MouseWheel/MouseWheel.hpp"

namespace ie {
	class WheelAction : public virtual IAction {
	public:
		explicit WheelAction();
		
		virtual void update(sf::Vector2i mousePosition, int value) = 0;
		
		virtual WheelAction* copy() = 0;
	
	protected:
		bool active;
	};
}