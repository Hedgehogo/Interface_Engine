#include "Character.hpp"
#include "IE/utils/color/hsv_to_rgb/hsv_to_rgb.hpp"

namespace ie {
	template<typename T>
	void make_rect_bones_position(sf::Rect<T> rect, sf::VertexArray& vertex_array){
		vertex_array[0].position = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top}};
		vertex_array[1].position = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top}};
		vertex_array[2].position = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top + rect.height}};
		vertex_array[3].position = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top + rect.height}};
	}
	
	template<typename T>
	void make_rect_bones_tex_coords(sf::Rect<T> rect, sf::VertexArray& vertex_array){
		vertex_array[0].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top}};
		vertex_array[1].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top}};
		vertex_array[2].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top + rect.height}};
 		vertex_array[3].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top + rect.height}};
	}
	
	Character::Character(
		char32_t character,
		TextVariables& text_variables,
		std::vector<BoxPtr<BaseLine>>& lines,
		orl::Option<sf::RenderTarget&> render_target
	) : render_target(character == '\n' ? orl::Option<sf::RenderTarget&>{} : render_target),
		character(character),
		advance(0),
		kerning(0),
		text_variables(text_variables),
		vertex_array(sf::Quads, 4),
		selection_vertex_array(sf::Quads, 4),
		lines(lines) {
		if(render_target) {
			glyph = text_variables.font.some()->getGlyph(character, text_variables.size.some(), text_variables.style.some() & sf::Text::Style::Bold);
			advance = glyph.advance;
			texture = text_variables.font.some()->getTexture(text_variables.size.some());
			
			make_rect_bones_tex_coords(glyph.textureRect, vertex_array);
			
			make_rect_bones_position<int>({0, 0, glyph.textureRect.width, glyph.textureRect.height}, vertex_array);
			
			make_rect_bones_position<float>({0, 0, get_advance(), get_height()}, selection_vertex_array);
			
			if(text_variables.style.some() & sf::Text::Style::Italic) {
				float italic_shear = -0.26794;
				
				for(size_t i = 0; i < 4; ++i) {
					vertex_array[i].position.x += (vertex_array[i].position.y + glyph.bounds.top) * italic_shear;
				}
			}
			
			for(size_t i = 0; i < 4; ++i) {
				vertex_array[i].position += {glyph.bounds.left, glyph.bounds.top};
				selection_vertex_array[i].position.y -= get_height();
				
				vertex_array[i].color = text_variables.text_color.some();
				selection_vertex_array[i].color = text_variables.background_selection_color.some();
			}
		}
	}
	
	void Character::set_active(bool active) {
		BaseCharacter::set_active(active);
		if(active) {
			for(int i = 0; i < 4; ++i) {
				vertex_array[i].color = text_variables.text_selection_color.some();
				selection_vertex_array[i].color = text_variables.background_selection_color.some();
			}
		} else {
			for(int i = 0; i < 4; ++i) {
				vertex_array[i].color = text_variables.inactive_text_selection_color.some();
				selection_vertex_array[i].color = text_variables.inactive_background_selection_color.some();
			}
		}
	}
	
	sf::Vector2i Character::get_size_texture() {
		if(get_char() == U' ')
			return {static_cast<int>(get_advance()), static_cast<int>(get_height())};
		return {glyph.textureRect.width, glyph.textureRect.height};
	}
	
	void Character::set_selection(bool selection) {
		BaseCharacter::set_selection(selection);
		auto current_color{selection ? text_variables.text_selection_color.some() : text_variables.text_color.some()};
		for(std::size_t i = 0; i < 4; ++i) {
			vertex_array[i].color = current_color;
		}
	}
	
	void Character::draw(bool selection) {
		if(render_target) {
			if(this->selection && selection)
				render_target.some().draw(selection_vertex_array);
			render_target.some().draw(vertex_array, &texture);
		}
	}
	
	BaseCharacter::Special Character::is_special() {
		if(character == L' ')
			return BaseCharacter::Special::Space;
		else if(character == L'\n')
			return BaseCharacter::Special::Enter;
		return BaseCharacter::Special::No;
	}
	
	char32_t Character::get_char() {
		return character;
	}
	
	float Character::get_kerning(char32_t character) {
		return text_variables.font.some()->getKerning(this->character, character, text_variables.size.some());
	}
	
	float Character::get_advance() {
		return advance;
	}
	
	float Character::get_height() const {
		return text_variables.size.some();
	}
	
	void Character::set_position(sf::Vector2f position) {
		position.x += kerning;
		move(position - this->position);
		BaseCharacter::set_position(position);
	}
	
	void Character::set_kerning(float kerning) {
		advance -= this->kerning;
		advance += kerning;
		this->kerning = kerning;
		selection_vertex_array[0].position -= {kerning, 0};
		selection_vertex_array[3].position -= {kerning, 0};
	}
	
	void Character::move(sf::Vector2f position) {
		BaseCharacter::move(position);
		for(std::size_t i = 0; i < 4; ++i) {
			selection_vertex_array[i].position += position;
			         vertex_array[i].position += position;
		}
	}
	
	const std::vector<BoxPtr<BaseLine>>& Character::get_line() {
		return lines;
	}
	
	bool Character::in(sf::Vector2f mouse_position) {
		return position.x < mouse_position.x && position.x + get_advance() > mouse_position.x &&
			   position.y - get_height() < mouse_position.y && position.y > mouse_position.y;
	}
	
	bool Character::debug = false;
	
	void Character::set_debug(bool debug) {
		Character::debug = debug;
	}
	
	void Character::draw_debug(sf::RenderTarget& render_target, int, uint hue, uint) {
		if(debug) {
			sf::Vector2f size{get_advance() - 2.0f, get_height() - 2.0f};
			sf::Vector2f position{this->get_position() + sf::Vector2f{1.0f, 1.0f - get_height()}};
			if(size.x > 0 && size.y > 0) {
				sf::Color color{hsv_to_rgb(static_cast<float>(hue % 360))};
				
				sf::RectangleShape rectangle{size};
				rectangle.setPosition(position);
				rectangle.setFillColor(sf::Color::Transparent);
				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(color);
				
				render_target.draw(rectangle);
			}
		}
	}
}