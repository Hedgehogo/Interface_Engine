#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../BaseButton.hpp"

namespace ie {
	class Button : public BaseButton {
	public:
		struct Make : public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> background;
			BoxPtr<IBaseTrigger::Make> trigger;
			
			Make(BoxPtr<IScalable::Make>&& background, BoxPtr<IBaseTrigger::Make>&& trigger);
			
			auto make(InitInfo init_info) -> Button* override;
		};
		
		Button(Make&& make, InitInfo init_info);
		
		auto update() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
	protected:
		BoxPtr<IBaseTrigger> trigger_;
	};
}

template<>
struct ieml::Decode<char, ie::Button::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Button::Make>;
};
