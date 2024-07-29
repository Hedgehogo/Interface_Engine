#pragma once

#include <string>
#include "../BaseCharacter.hpp"
#include "../../TextStyle/TextStyle.hpp"

namespace ie {
	class Character : public BaseCharacter {
	public:
		Character(
			char32_t character,
			TextStyle& text_style_,
			std::vector<BoxPtr<BaseLine> >& lines,
			orl::Option<sf::RenderTarget&> render_target
		);
		
		auto set_active(bool active) -> void override;
		
		auto get_size_texture() -> sf::Vector2i override;
		
		auto set_selection(bool selection) -> void override;
		
		auto draw() -> void override;
		
		auto set_kerning(float kerning) -> void override;
		
		auto move(sf::Vector2f offset) -> void override;
		
		auto get_line() -> std::vector<BoxPtr<BaseLine> > const& override;
		
		auto in(sf::Vector2f point_position) -> bool override;
		
		auto get_height() const -> float override;
		
		auto get_advance() -> float override;
		
		auto get_kerning(char32_t character) -> float override;
		
		auto is_special() -> Special override;
		
		auto get_char() -> char32_t override;
		
		auto set_position(sf::Vector2f position) -> void override;
		
		static auto set_debug(bool debug) -> void;
		
		auto draw_debug(sf::RenderTarget& render_target, int, size_t hue, size_t) -> void override;
	
	private:
		static bool debug_;
		
	protected:
		orl::Option<sf::RenderTarget&> render_target_;
		
		TextStyle& text_style_;
		
		char32_t character_;
		sf::Glyph glyph_;
		float advance_;
		float kerning_;
		sf::VertexArray vertex_array_;
		sf::VertexArray selection_vertex_array_;
		sf::Texture const& texture_;
		sf::Vector2f origin_;
		
		std::vector<BoxPtr<BaseLine> >& lines_;
	};
}