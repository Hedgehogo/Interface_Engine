#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
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
		
		void draw() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		DrawManager first_draw_manager_;
		DrawManager second_draw_manager_;
		BoxPtr<IUninteractive> background_;
		BoxPtr<IScalable> object_;
		BoxPtr<IScalable> first_object_;
		BoxPtr<IScalable> second_object_;
		float aspect_ratio_;
		bool render_first_;
		bool render_second_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxConstRatioCenter::Make> {
	static orl::Option<ie::BoxConstRatioCenter::Make> decode(ieml::Node const& node);
};
