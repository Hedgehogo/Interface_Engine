#pragma once
#include "../iInteraction.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class EmptyInteraction : public virtual IInteraction {
	public:
		EmptyInteraction() {
		}
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		EmptyInteraction* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, EmptyInteraction *&emptyInteraction);
}
