#pragma once

#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISVec2/ISVec2.hpp"
#include "IE/component/IComponent/IScalable/INonInteractive/INonInteractive.hpp"
#include "SliderTrigger/SliderTrigger.hpp"

namespace ie {
	class BaseSlider : public virtual IScalable, public virtual IUpdatable {
	public:
		BaseSlider(
			BoxPtr<INonInteractive::Make>&& slider,
			BoxPtr<INonInteractive::Make>&& background,
			SliderTrigger::Make&& trigger,
			MakeDyn<ISMRVec2F>&& value,
			InitInfo init_info
		);
		
		auto on_slider(sf::Vector2i mouse_position) -> bool;
		
		auto get_slider_size() -> sf::Vector2f;
		
		auto get_value() -> sf::Vector2f;
		
		auto get_value_ptr() -> ISMRVec2F&;
		
		auto set_value(sf::Vector2f value) -> void;
		
		auto set_value_by_mouse(sf::Vector2i mouse_position) -> void;
		
		auto move_slider(sf::Vector2f value, sf::Vector2f offset) const -> sf::Vector2f;
		
		static auto round_value_to_division(sf::Vector2f value, sf::Vector2i division) -> sf::Vector2f;
		
		auto get_area_position() const -> sf::Vector2f override;
		
		auto get_area_size() const -> sf::Vector2f override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override = 0;
		
		auto update() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		virtual auto resize_slider(sf::Vector2f new_value) -> void;
		
		BoxPtr<INonInteractive> background_;
		BoxPtr<INonInteractive> slider_;
		SliderTrigger trigger_;
		SReader<ISMRVec2F> value_;
		sf::Vector2f position_;
		sf::Vector2f slider_size_;
		sf::Vector2f move_zone_size_;
	};
}