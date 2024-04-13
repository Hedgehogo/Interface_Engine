#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/enums/Corner/Corner.hpp"
#include "../Box.hpp"
#include "../../INonInteractive/OnlyDrawable/Empty/Empty.hpp"
#include "../../IScalableLayout/IScalableBackground/IScalableBackground.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxConstRatio : public Box, public virtual IScalableBackground, public virtual IScalableTwoObjects, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableBackground::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> const_object;
			BoxPtr<IScalable::Make> second_object;
			BoxPtr<INonInteractive::Make> background;
			float aspect_ratio;
			Corner corner = Corner::UpLeft;
			sf::Vector2f min_size = {};
			
			Make(
				BoxPtr<IScalable::Make>&& const_object,
				BoxPtr<IScalable::Make>&& second_object,
				BoxPtr<INonInteractive::Make>&& background,
				float aspect_ratio = 1.f,
				Corner corner = Corner::UpLeft,
				sf::Vector2f min_size = {}
			);
			
			auto make(InitInfo init_info) -> BoxConstRatio* override;
		};
		
		BoxConstRatio(Make&& make, InitInfo init_info);
		
		auto get_corner() -> Corner;
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto move(sf::Vector2f position) -> void override;
		
		auto set_size(sf::Vector2f size) -> void override;
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(Event event) -> bool override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_background() -> INonInteractive& override;
		
		auto get_background() const -> const INonInteractive& override;
		
		auto get_first_object() -> IScalable& override;
		
		auto get_first_object() const -> IScalable const& override;
		
		auto get_second_object() -> IScalable& override;
		
		auto get_second_object() const -> IScalable const& override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		DrawManager second_draw_manager_;
		BoxPtr<INonInteractive> background_;
		BoxPtr<IScalable> const_object_;
		BoxPtr<IScalable> second_object_;
		bool vertical_side_, horizontal_side_;      //true = up   true = left
		bool render_second_;
		float aspect_ratio_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxConstRatio::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxConstRatio::Make>;
};
