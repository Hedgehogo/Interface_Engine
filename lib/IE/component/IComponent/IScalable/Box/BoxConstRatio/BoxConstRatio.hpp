#pragma once

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
		
		BoxConstRatio(
			BoxPtr<IScalable>&& const_object,
			BoxPtr<IScalable>&& second_object,
			BoxPtr<IUninteractive>&& background,
			float aspect_ratio,
			Corner corner = Corner::UpLeft,
			sf::Vector2f min_size = {}
		);
		
		BoxConstRatio(const BoxConstRatio& other);
		
		void init(InitInfo init_info) override;
		
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
		
		BoxConstRatio* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		DrawManager second_draw_manager;
		BoxPtr<IUninteractive> background;
		BoxPtr<IScalable> const_object;
		BoxPtr<IScalable> second_object;
		bool vertical_side, horizontal_side;      //true = up   true = left
		bool render_second;
		float aspect_ratio;
	};
	
	template<>
	struct DecodePointer<BoxConstRatio> {
		static bool decode_pointer(const YAML::Node& node, BoxConstRatio*& box_with_const_ratio);
	};
}