#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BoxMovableBorder;
	
	class MovableBorderAction : public BasicBaseKeyAction<BoxMovableBorder&> {
	public:
		struct Make : public virtual BasicKeyAction<BoxMovableBorder&>::Make {
			auto make(BasicActionInitInfo<BoxMovableBorder&> init_info) -> MovableBorderAction* override;
		};
		
		MovableBorderAction(Make&& make, BasicActionInitInfo<BoxMovableBorder&> init_info);
		
		auto set_box(BoxMovableBorder& box) -> void;
		
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		BoxMovableBorder* box_;
		sf::Vector2i start_mouse_position_;
		float start_border_value_;
		bool active_;
	};
}


