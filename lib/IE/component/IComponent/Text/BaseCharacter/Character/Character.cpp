#include "Character.hpp"
#include "IE/utils/color/hsv_to_rgb/hsv_to_rgb.hpp"

namespace ie {
	template<typename T>
	auto make_rect_bones_position(sf::Rect<T> rect, sf::VertexArray& vertex_array) -> void {
		vertex_array[0].position = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top}};
		vertex_array[1].position = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top}};
		vertex_array[2].position = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top + rect.height}};
		vertex_array[3].position = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top + rect.height}};
	}
	
	template<typename T>
	auto make_rect_bones_tex_coords(sf::Rect<T> rect, sf::VertexArray& vertex_array) -> void {
		vertex_array[0].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top}};
		vertex_array[1].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top}};
		vertex_array[2].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top + rect.height}};
		vertex_array[3].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top + rect.height}};
	}
	
	Character::Character(
		char32_t character,
		TextStyle const& text_style,
		std::vector<BoxPtr<BaseLine> >& lines,
		orl::Option<sf::RenderTarget&> render_target
	) :
		render_target_(character == '\n' ? orl::Option<sf::RenderTarget&>{} : render_target),
		text_style_(text_style),
		character_(character),
		glyph_(text_style_.font.getGlyph(
			character,
			text_style_.size,
			text_style_.bold
		)),
		advance_(glyph_.advance),
		kerning_(0),
		vertex_array_(sf::Quads, 4),
		selection_vertex_array_(sf::Quads, 4),
		texture_(text_style_.font.getTexture(text_style_.size)),
		lines_(lines) {
		if(render_target.is_some()) {
			make_rect_bones_tex_coords(glyph_.textureRect, vertex_array_);
			
			make_rect_bones_position<int>({{}, glyph_.textureRect.getSize()}, vertex_array_);
			
			make_rect_bones_position<float>({{}, {get_advance(), get_height()}}, selection_vertex_array_);
			
			if(text_style_.italic) {
				float italic_shear = -0.26794;
				
				for(size_t i = 0; i < 4; ++i) {
					vertex_array_[i].position.x += (vertex_array_[i].position.y + glyph_.bounds.top) * italic_shear;
				}
			}
			
			for(size_t i = 0; i < 4; ++i) {
				vertex_array_[i].position += {glyph_.bounds.left, glyph_.bounds.top};
				selection_vertex_array_[i].position.y -= get_height();
				
				vertex_array_[i].color = text_style_.text_color;
				selection_vertex_array_[i].color = text_style_.background_selection_color;
			}
		}
	}
	
	auto Character::set_active(bool active) -> void {
		BaseCharacter::set_active(active);
		if(active) {
			for(int i = 0; i < 4; ++i) {
				vertex_array_[i].color = text_style_.text_selection_color;
				selection_vertex_array_[i].color = text_style_.background_selection_color;
			}
		} else {
			for(int i = 0; i < 4; ++i) {
				vertex_array_[i].color = text_style_.inactive_text_selection_color;
				selection_vertex_array_[i].color = text_style_.inactive_background_selection_color;
			}
		}
	}
	
	auto Character::get_size_texture() -> sf::Vector2i {
		if(get_char() == U' ') {
			return sf::Vector2i{sf::Vector2f{get_advance(), get_height()}};
		}
		return {glyph_.textureRect.width, glyph_.textureRect.height};
	}
	
	auto Character::set_selection(bool selection) -> void {
		BaseCharacter::set_selection(selection);
		auto current_color{selection ? text_style_.text_selection_color : text_style_.text_color};
		for(size_t i = 0; i < 4; ++i) {
			vertex_array_[i].color = current_color;
		}
	}
	
	auto Character::draw() -> void {
		for(auto& render_target_value: render_target_) {
			if(selection_) {
				render_target_value.draw(selection_vertex_array_);
			}
			render_target_value.draw(vertex_array_, &texture_);
		}
	}
	
	auto Character::is_special() -> Special {
		if(character_ == L' ') {
			return BaseCharacter::Special::Space;
		} else if(character_ == L'\n') {
			return BaseCharacter::Special::Enter;
		}
		return BaseCharacter::Special::No;
	}
	
	auto Character::get_char() -> char32_t {
		return character_;
	}
	
	auto Character::get_kerning(char32_t character) -> float {
		return text_style_.font.getKerning(this->character_, character, text_style_.size);
	}
	
	auto Character::get_advance() -> float {
		return advance_;
	}
	
	auto Character::get_height() const -> float {
		return static_cast<float>(text_style_.size);
	}
	
	auto Character::set_position(sf::Vector2f position) -> void {
		position.x += kerning_;
		move(position - this->position_);
		BaseCharacter::set_position(position);
	}
	
	auto Character::set_kerning(float kerning) -> void {
		advance_ -= this->kerning_;
		advance_ += kerning;
		this->kerning_ = kerning;
		selection_vertex_array_[0].position -= {kerning, 0};
		selection_vertex_array_[3].position -= {kerning, 0};
	}
	
	auto Character::move(sf::Vector2f offset) -> void {
		BaseCharacter::move(offset);
		for(size_t i = 0; i < 4; ++i) {
			selection_vertex_array_[i].position += offset;
			vertex_array_[i].position += offset;
		}
	}
	
	auto Character::get_line() -> std::vector<BoxPtr<BaseLine> > const& {
		return lines_;
	}
	
	auto Character::in(sf::Vector2f point_position) -> bool {
		return
			position_.x < point_position.x && position_.x + get_advance() > point_position.x &&
			position_.y - get_height() < point_position.y && position_.y > point_position.y;
	}
	
	bool Character::debug_ = false;
	
	auto Character::set_debug(bool debug) -> void {
		Character::debug_ = debug;
	}
	
	auto Character::draw_debug(sf::RenderTarget& render_target, int, size_t hue, size_t) -> void {
		if(debug_) {
			auto size{sf::Vector2f{get_advance() - 2.0f, get_height() - 2.0f}};
			auto position{this->get_position() + sf::Vector2f{1.0f, 1.0f - get_height()}};
			if(size.x > 0 && size.y > 0) {
				auto color{hsv_to_rgb(static_cast<float>(hue % 360))};
				
				auto rectangle{sf::RectangleShape{size}};
				rectangle.setPosition(position);
				rectangle.setFillColor(sf::Color::Transparent);
				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(color);
				
				render_target.draw(rectangle);
			}
		}
	}
}