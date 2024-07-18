#pragma once

#include "IE/interaction/InteractionManager/InteractionManager.hpp"
#include "../BaseLine/BaseLine.hpp"

namespace ie {
	class BaseTextBlock;
	
	class BaseCharacter {
	public:
		enum class Special {
			No,
			Space,
			Enter,
			Object,
			FullLine,
		};
		
		BaseCharacter();
		
		virtual auto get_rerender() const -> bool;
		
		virtual auto set_rerender(bool rerender) -> void;
		
		virtual auto set_active(bool active) -> void;
		
		virtual auto get_size_texture() -> sf::Vector2i = 0;
		
		virtual auto in(sf::Vector2f point_position) -> bool;
		
		virtual auto set_selection(bool selection) -> void;
		
		virtual auto set_position(sf::Vector2f position) -> void;
		
		virtual auto set_kerning(float kerning) -> void;
		
		virtual auto resize(sf::Vector2f position, float) -> void;
		
		virtual auto move(sf::Vector2f offset) -> void;
		
		virtual auto get_line() -> std::vector<BoxPtr<BaseLine> > const& = 0;
		
		virtual auto get_position() const -> sf::Vector2f;
		
		virtual auto get_height() const -> float = 0;
		
		virtual auto get_advance() -> float = 0;
		
		virtual auto get_kerning(char32_t) -> float = 0;
		
		virtual auto is_enter() -> bool;
		
		virtual auto is_special() -> Special = 0;
		
		virtual auto draw() -> void = 0;
		
		virtual auto get_char() -> char32_t = 0;
		
		virtual auto get_min_advance() -> float;
		
		virtual auto draw_debug(sf::RenderTarget& render_target, int indent_addition, size_t hue, size_t hue_offset) -> void = 0;
		
		virtual ~BaseCharacter() = default;
	
	protected:
		sf::Vector2f position_;
		bool selection_;
		bool active_;
		bool rerender_;
	};
}