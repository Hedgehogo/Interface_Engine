#include "../../lambda/lambdaInteraction.h"
#include "../mouseInteraction.h"

namespace ui {
	class MouseLambdaInteraction : public MouseInteraction, public LambdaInteraction {
	public:
		MouseLambdaInteraction(ui::ButtonEvent *leftMouseButton, ui::ButtonEvent *rightMouseButton, void ( *startPointing)(sf::Vector2i mousePosition), void (*finishPointing)(sf::Vector2i mousePosition));
		~MouseLambdaInteraction();
	};
}