#pragma once
#include "../iInteraction.hpp"
#include "../../../enums/enums.hpp"

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

		static OneButtonInteraction* createFromYaml(const YAML::Node &node);
	};
}
