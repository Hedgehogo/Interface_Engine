#pragma once

#include <string>
#include "../BaseCharacter.hpp"
#include "../../TextVariables/TextVariables.hpp"

namespace ie {
	class Character : public BaseCharacter {
	public:
		Character(char32_t character, TextVariables& text_variables, std::vector<BoxPtr<BaseLine>>& lines, orl::Option<sf::RenderTarget&> render_target);
		
		void set_active(bool active) override;
		
		sf::Vector2i get_size_texture() override;
		
		void set_selection(bool selection) override;
		
		void draw() override;
		
		void set_kerning(float kerning) override;
		
		void move(sf::Vector2f position) override;
		
		const std::vector<BoxPtr<BaseLine>>& get_line();
		
		bool in(sf::Vector2f mouse_position) override;
		
		float get_height() const override;
		
		float get_advance() override;
		
		float get_kerning(char32_t character) override;
		
		Special is_special() override;
		
		char32_t get_char() override;
		
		void set_position(sf::Vector2f position) override;
	
		static void set_debug(bool debug);
		
		void draw_debug(sf::RenderTarget& render_target, int, uint hue, uint) override;
	
	private:
		static bool debug;
	
	protected:
		orl::Option<sf::RenderTarget&> render_target;
		
		char32_t character;
		
		sf::Glyph glyph;
		float advance;
		float kerning;
		TextVariables& text_variables;
		sf::VertexArray vertex_array;
		sf::VertexArray selection_vertex_array;
		sf::Texture texture;
		sf::Vector2f origin;
		
		std::vector<BoxPtr<BaseLine>>& lines;
	};
}