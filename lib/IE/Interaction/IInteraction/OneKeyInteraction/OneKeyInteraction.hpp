#pragma once

#include "../IInteraction.hpp"
#include "../../../Enums/KeyHandler/KeyHandler.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class OneKeyInteraction : public virtual IInteraction {
	public:
		OneKeyInteraction(BoxPtr<KeyEvent>&& event, Key key);
		
		void init(InteractionInitInfo interactionInitInfo) override;
		
		Key getKey();
		
		KeyEvent& getEvent();
		
		const KeyEvent& getEvent() const;
		
		void setEvent(BoxPtr<KeyEvent>&& event);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i) override;
		
		OneKeyInteraction* copy() override;
	
	protected:
		BoxPtr<KeyEvent> event;
		Key key;
	};
	
	template<>
	struct DecodePointer<OneKeyInteraction> {
		static bool decodePointer(const YAML::Node& node, OneKeyInteraction*& oneKeyInteraction);
	};
}
