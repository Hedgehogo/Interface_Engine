#pragma once

#include "../../lambda/lambdaInteraction.hpp"
#include "../mouseInteraction.hpp"


namespace ui {
	class MouseLambdaInteraction : public MouseInteraction, public LambdaInteraction {
	public:
		
		static MouseLambdaInteraction debug;
		
		MouseLambdaInteraction(KeyEvent* leftMouseButton, KeyEvent* rightMouseButton, void ( * startPointing)(sf::Vector2i mousePosition), void (* finishPointing)(sf::Vector2i mousePosition));
		
		MouseLambdaInteraction* copy() override;
	};
	
}