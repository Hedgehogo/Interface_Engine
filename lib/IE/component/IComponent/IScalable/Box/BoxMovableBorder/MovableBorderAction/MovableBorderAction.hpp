#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BoxMovableBorder;
	
	class MovableBorderAction : public BasicBaseKeyAction<BoxMovableBorder&> {
	public:
		struct Make : public virtual BasicKeyAction<BoxMovableBorder&>::Make {
			MovableBorderAction* make(BasicActionInitInfo<BoxMovableBorder&> init_info) override;
		};
		
		MovableBorderAction(Make&& make, BasicActionInitInfo<BoxMovableBorder&> init_info);
		
		void set_box(BoxMovableBorder& box);
		
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		BoxMovableBorder* box_;
		sf::Vector2i start_mouse_position_;
		float start_border_value_;
		bool active_;
	};
}


