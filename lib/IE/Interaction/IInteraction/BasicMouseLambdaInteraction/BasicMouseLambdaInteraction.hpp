#pragma once

#include "../BasicLambdaInteraction/BasicLambdaInteraction.hpp"
#include "../IBasicMouseInteraction/IBasicMouseInteraction.hpp"

namespace ui {
	class MouseLambdaInteraction : public LambdaInteraction, public IMouseInteraction {
	public:
		MouseLambdaInteraction(BoxPtr<KeyEvent>&& leftButtonEvent, BoxPtr<KeyEvent>&& rightButtonEvent, void (* startPointing)(sf::Vector2i mousePosition), void (* finishPointing)(sf::Vector2i mousePosition));
		
		KeyEvent& getLeftButtonEvent() override;
		
		const KeyEvent& getLeftButtonEvent() const override;
		
		KeyEvent& getRightButtonEvent() override;
		
		const KeyEvent& getRightButtonEvent() const override;
		
		MouseLambdaInteraction* copy() override;
	
		static MouseLambdaInteraction debug;
		
	protected:
		BoxPtr<KeyEvent> leftButtonEvent;
		BoxPtr<KeyEvent> rightButtonEvent;
	};
}