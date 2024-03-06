#pragma once

#include "../../Box/BasicBoxMovableBorder/BasicBoxMovableBorder.hpp"

namespace ie {
	class MovableBorder : public BasicBoxMovableBorder<true>, public virtual IUpdatable {
	public:
	struct Make : public BasicBoxMovableBorder<true>::Make {
			int border_interaction_size = 5;
			Key key = Key::MouseLeft;
			
			Make(
				BoxPtr<IScalable::Make>&& first_object,
				BoxPtr<IScalable::Make>&& second_object,
				bool is_horizontal_border,
				MakeDyn<ISMRFloat> border_value,
				int border_interaction_size = 5,
				Key key = Key::MouseLeft,
				sf::Vector2f min_size = {}
			);
			
			auto make(InitInfo init_info) -> MovableBorder* override;
		};
		
		MovableBorder(Make&& make, InitInfo init_info);
		
		auto update() -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
	
	protected:
		BasicInteractiveData<MovableBorder&> interactive_;
		int border_interaction_size_;
	};
}

template<>
struct ieml::Decode<char, ie::MovableBorder::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::MovableBorder::Make>;
};
