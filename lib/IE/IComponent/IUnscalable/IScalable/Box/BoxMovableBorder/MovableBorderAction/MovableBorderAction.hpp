#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BoxMovableBorder;
	
	class MovableBorderAction : public BaseKeyAction {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		explicit MovableBorderAction(BoxMovableBorder& box);
		
		void setBox(BoxMovableBorder& box);
		
		MovableBorderAction* copy() override;
	
	protected:
		BoxMovableBorder* box;
		sf::Vector2i startMousePosition;
		float startBorderValue;
		bool active;
	};
}



