#pragma once

#include "../keyEvent.hpp"

namespace ui {
	class KeyEvent_Simple : public virtual KeyEvent {
	protected:
		virtual void startPressed() = 0;
		
		virtual void stopPressed() = 0;
		
		virtual void whilePressed() = 0;
		
		virtual void whileNotPressed() = 0;
	
	public:
		KeyEvent_Simple();
		
		void init(InteractionInitInfo interactionInitInfo) override;
		
		void setPressed(bool pressed) override;
		
		void update(sf::Vector2i mousePosition, bool press) override;
	
	protected:
		sf::Vector2i mousePosition;
	};
}
