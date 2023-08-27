#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BoxMovableBorder;
	
	class MovableBorderAction : public BasicBaseKeyAction<BoxMovableBorder&> {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		explicit MovableBorderAction();
		
		void init(BasicActionInitInfo<BoxMovableBorder&> initInfo) override;
		
		void setBox(BoxMovableBorder& box);
		
		MovableBorderAction* copy() override;
	
	protected:
		BoxMovableBorder* box;
		sf::Vector2i startMousePosition;
		float startBorderValue;
		bool active;
	};
}



