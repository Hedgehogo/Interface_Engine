#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/enums/Side/Side.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxConstBorder : public Box, public virtual IScalableTwoObjects {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> const_object;
			BoxPtr<IScalable::Make> second_object;
			float border_distance;
			Side side;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& const_object, BoxPtr<IScalable::Make>&& second_object, float border_distance, Side side, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxConstBorder* override;
		};
		
		BoxConstBorder(Make&& make, InitInfo init_info);
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(Event event) -> bool override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_first_object() -> IScalable& override;
		
		auto get_first_object() const -> IScalable const& override;
		
		auto get_second_object() -> IScalable& override;
		
		auto get_second_object() const -> IScalable const& override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		BoxPtr<IScalable> const_object_;
		BoxPtr<IScalable> second_object_;
		float border_distance_;
		Side side_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxConstBorder::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxConstBorder::Make>;
};
