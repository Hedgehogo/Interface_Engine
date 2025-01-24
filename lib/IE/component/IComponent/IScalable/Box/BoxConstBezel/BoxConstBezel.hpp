#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/trigger/TriggerManager/TriggerManager.hpp"
#include "../Box.hpp"
#include "../../INonInteractive/INonInteractive.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxConstBezel : public Box, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<INonInteractive::Make> bezel;
			float thickness;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<INonInteractive::Make>&& bezel, float thickness, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxConstBezel* override;
		};
		
		BoxConstBezel(Make&& make, InitInfo init_info);
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		BoxPtr<INonInteractive> bezel_;
		BoxPtr<IScalable> object_;
		float thickness_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxConstBezel::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxConstBezel::Make>;
};
