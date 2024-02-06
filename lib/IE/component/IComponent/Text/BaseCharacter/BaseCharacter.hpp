#pragma once

#include "IE/interaction/InteractionManager/InteractionManager.hpp"
#include "../BaseLine/BaseLine.hpp"

namespace ie {
	class BaseTextBlock;
	
	class BaseCharacter {
	public:
		enum class Special{
			No,
			Space,
			Enter,
			Object,
			FullLine,
		};
	
		BaseCharacter();
		
		virtual bool get_rerender() const;
		
		virtual void set_rerender(bool rerender);
		
		virtual void set_active(bool active);
		
		virtual sf::Vector2i get_size_texture() = 0;
		
		virtual bool in(sf::Vector2f mouse_position);
		
		virtual void set_selection(bool selection);
		
		virtual void set_position(sf::Vector2f position);
		
		virtual void set_kerning(float kerning);
		
		virtual void resize(sf::Vector2f position, float);
		
		virtual void move(sf::Vector2f position);
		
		virtual const std::vector<BoxPtr<BaseLine>>& get_line() = 0;
		
		virtual sf::Vector2f get_position() const;
		
		virtual float get_height() const = 0;
		
		virtual float get_advance() = 0;
		
		virtual float get_kerning(char32_t) = 0;
		
		virtual bool is_enter();
		
		virtual Special is_special() = 0;
		
		virtual void draw() = 0;
		
		virtual char32_t get_char() = 0;
		
		virtual float get_min_advance();
		
		virtual void draw_debug(sf::RenderTarget& render_target, int indent_addition, size_t hue, size_t hue_offset) = 0;
		
		virtual ~BaseCharacter() = default;
	
	protected:
		sf::Vector2f position;
		bool selection;
		bool active;
		bool rerender;
	};
}