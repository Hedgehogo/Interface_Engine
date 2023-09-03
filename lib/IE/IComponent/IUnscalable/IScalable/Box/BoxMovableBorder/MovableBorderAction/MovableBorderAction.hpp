#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BoxMovableBorder;
	
	class MovableBorderAction : public BasicBaseKeyAction<BoxMovableBorder&> {
	public:
		struct Make : public virtual BasicKeyAction<BoxMovableBorder&>::Make {
			MovableBorderAction* make(BasicActionInitInfo<BoxMovableBorder&> initInfo) override;
		};
		
		MovableBorderAction(Make&& make, BasicActionInitInfo<BoxMovableBorder&> initInfo);
		
		explicit MovableBorderAction();
		
		void init(BasicActionInitInfo<BoxMovableBorder&> initInfo) override;
		
		void setBox(BoxMovableBorder& box);
		
		MovableBorderAction* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		BoxMovableBorder* box;
		sf::Vector2i startMousePosition;
		float startBorderValue;
		bool active;
	};
}



