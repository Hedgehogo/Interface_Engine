#pragma once

#include "../Box.hpp"
#include "../../IUninteractive/OnlyDrawable/Empty/Empty.hpp"
#include "../../IScalableLayout/IScalableBackground/IScalableBackground.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxConstRatioCenter : public Box, public virtual IScalableObject, public virtual IScalableBackground, public virtual IScalableTwoObjects, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make, public virtual IScalableBackground::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IScalable::Make> first_object;
			BoxPtr<IScalable::Make> second_object;
			BoxPtr<IUninteractive::Make> background;
			float aspect_ratio;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, float aspect_ratio, sf::Vector2f min_size = {});
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				BoxPtr<IScalable::Make>&& first_object,
				BoxPtr<IScalable::Make>&& second_object,
				BoxPtr<IUninteractive::Make>&& background,
				float aspect_ratio = 1.f,
				sf::Vector2f min_size = {}
			);
			
			BoxConstRatioCenter* make(InitInfo init_info) override;
		};
		
		BoxConstRatioCenter(Make&& make, InitInfo init_info);
		
		BoxConstRatioCenter(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& background, float aspect_ratio, sf::Vector2f min_size = {});
		
		BoxConstRatioCenter(
			BoxPtr<IScalable>&& object,
			BoxPtr<IScalable>&& first_object,
			BoxPtr<IScalable>&& second_object,
			BoxPtr<IUninteractive>&& background,
			float aspect_ratio,
			sf::Vector2f min_size = {}
		);
		
		BoxConstRatioCenter(const BoxConstRatioCenter& other);
		
		void init(InitInfo init_info) override;
		
		void set_aspect_ratio(float aspect_ratio);
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IUninteractive& get_background() override;
		
		const IUninteractive& get_background() const override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		IScalable& get_first_object() override;
		
		const IScalable& get_first_object() const override;
		
		IScalable& get_second_object() override;
		
		const IScalable& get_second_object() const override;
		
		BoxConstRatioCenter* copy() override;
		
		void draw() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) override;
	
	protected:
		DrawManager first_draw_manager;
		DrawManager second_draw_manager;
		BoxPtr<IUninteractive> background;
		BoxPtr<IScalable> object;
		BoxPtr<IScalable> first_object;
		BoxPtr<IScalable> second_object;
		float aspect_ratio;
		bool render_first;
		bool render_second;
	};
	
	template<>
	struct DecodePointer<BoxConstRatioCenter> {
		static bool decode_pointer(const YAML::Node& node, BoxConstRatioCenter*& box_with_const_ratio_center);
	};
}