#pragma once
#include "../iInteraction.hpp"
#include "../../../enums/keyHandler/keyHandler.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class OneKeyInteraction : public virtual IInteraction {
	protected:
		KeyEvent *event;
		Key key;
	
	public:
		OneKeyInteraction(KeyEvent *event, Key key);
		
		~OneKeyInteraction() override;
		
		Key getKey();

		KeyEvent* getEvent();
		
		void setEvent(KeyEvent *event);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		OneKeyInteraction* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, OneKeyInteraction *&oneKeyInteraction);
}
