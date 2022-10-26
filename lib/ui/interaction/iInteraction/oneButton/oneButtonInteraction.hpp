#pragma once
#include "../iInteraction.hpp"
#include "../../../enums/keyHandler/keyHandler.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class OneButtonInteraction : public virtual IInteraction {
	protected:
		ButtonEvent *event;
		Key button;
	
	public:
		OneButtonInteraction(ButtonEvent *event, Key button);
		
		~OneButtonInteraction() override;
		
		Key getButton();

		ButtonEvent* getEvent();
		
		void setEvent(ButtonEvent *event);
		
		void start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		OneButtonInteraction* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, OneButtonInteraction *&oneButtonInteraction);
}
