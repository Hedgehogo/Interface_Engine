#pragma once
#include "../buttonEvent.hpp"

namespace ui {
	class ButtonEvent_Simple : public virtual ButtonEvent {
	protected:
        sf::Vector2i mousePosition;

		virtual void startPressed() = 0;
		
		virtual void stopPressed() = 0;
		
		virtual void whilePressed() = 0;
		
		virtual void whileNotPressed() = 0;

	public:
		ButtonEvent_Simple();

        void setPressed(bool pressed) override;

		void update(sf::Vector2i mousePosition, bool press) override;
	};
}
