#pragma once

#include "IE/modules/yaml-cpp/shared/shared.hpp"
#include "IE/component/IComponent/IScalable/IUninteractive/IUninteractive.hpp"
#include "../BasicInteractiveData.hpp"
#include "SliderInteraction/SliderInteraction.hpp"

namespace ie {
	class BaseSlider : public virtual IScalable, public virtual IUpdatable {
	public:
		BaseSlider(
			BoxPtr<IUninteractive::Make>&& slider,
			BoxPtr<IUninteractive::Make>&& background,
			BoxPtr<SliderInteraction::Make>&& interaction,
			const PSRVec2f& value,
			InitInfo init_info
		);
		
		BaseSlider(
			BoxPtr<IUninteractive>&& slider,
			BoxPtr<IUninteractive>&& background,
			BoxPtr<SliderInteraction>&& interaction,
			const PSRVec2f& value
		);
		
		BaseSlider(const BaseSlider& other);
		
		void init(InitInfo init_info) override;
		
		bool on_slider(sf::Vector2i mouse_position);
		
		sf::Vector2f get_slider_size();
		
		sf::Vector2f get_value();
		
		PSRVec2f get_value_ptr();
		
		void set_value(sf::Vector2f value);
		
		void set_value_by_mouse(sf::Vector2i mouse_position);
		
		sf::Vector2f move_slider(sf::Vector2f value, sf::Vector2f offset) const;
		
		static sf::Vector2f round_value_to_division(sf::Vector2f value, sf::Vector2i division);
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override = 0;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		BaseSlider* copy() override = 0;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		virtual void resize_slider(sf::Vector2f new_value);
		
		BasicInteractiveData<BaseSlider&> interactive;
		BoxPtr<IUninteractive> background;
		BoxPtr<IUninteractive> slider;
		PSRVec2f value;
		sf::Vector2f position;
		sf::Vector2f slider_size;
		sf::Vector2f move_zone_size;
	};
}