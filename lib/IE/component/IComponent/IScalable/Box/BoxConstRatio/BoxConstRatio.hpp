#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/enums/Corner/Corner.hpp"
#include "../Box.hpp"
#include "../../IUninteractive/OnlyDrawable/Empty/Empty.hpp"
#include "../../IScalableLayout/IScalableBackground/IScalableBackground.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxConstRatio : public Box, public virtual IScalableBackground, public virtual IScalableTwoObjects, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableBackground::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> const_object;
			BoxPtr<IScalable::Make> second_object;
			BoxPtr<IUninteractive::Make> background;
			float aspect_ratio;
			Corner corner = Corner::UpLeft;
			sf::Vector2f min_size = {};
			
			Make(
				BoxPtr<IScalable::Make>&& const_object,
				BoxPtr<IScalable::Make>&& second_object,
				BoxPtr<IUninteractive::Make>&& background,
				float aspect_ratio = 1.f,
				Corner corner = Corner::UpLeft,
				sf::Vector2f min_size = {}
			);
			
			BoxConstRatio* make(InitInfo init_info) override;
		};
		
		BoxConstRatio(Make&& make, InitInfo init_info);
		
		Corner get_corner();
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IUninteractive& get_background() override;
		
		const IUninteractive& get_background() const override;
		
		IScalable& get_first_object() override;
		
		const IScalable& get_first_object() const override;
		
		IScalable& get_second_object() override;
		
		const IScalable& get_second_object() const override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		DrawManager second_draw_manager_;
		BoxPtr<IUninteractive> background_;
		BoxPtr<IScalable> const_object_;
		BoxPtr<IScalable> second_object_;
		bool vertical_side_, horizontal_side_;      //true = up   true = left
		bool render_second_;
		float aspect_ratio_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxConstRatio::Make> {
	static orl::Option<ie::BoxConstRatio::Make> decode(ieml::Node const& node);
};
