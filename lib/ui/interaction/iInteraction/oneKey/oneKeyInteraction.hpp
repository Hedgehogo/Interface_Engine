#pragma once

#include "../iInteraction.hpp"
#include "../../../enums/keyHandler/keyHandler.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class OneKeyInteraction : public virtual IInteraction {
	public:
		OneKeyInteraction(KeyEvent* event, Key key);
		
		~OneKeyInteraction() override;
		
		void init(InteractionInitInfo interactionInitInfo) override;
		
		Key getKey();
		
		KeyEvent* getEvent();
		
		void setEvent(KeyEvent* event);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		OneKeyInteraction* copy() override;
	
	protected:
		KeyEvent* event;
		Key key;
	};
	
	template<>
	struct DecodePointer<OneKeyInteraction> {
		static bool decodePointer(const YAML::Node& node, OneKeyInteraction*& oneKeyInteraction);
	};
}
