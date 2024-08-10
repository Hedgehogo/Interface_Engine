#include "TextResizer.hpp"

namespace ie {
	TextResizer::Make::Make(float line_spacing, BaseTextResizer::Align align, BaseTextResizer::Algorithm algorithm) :
		line_spacing(line_spacing), align(align), algorithm(algorithm) {
	}
	
	auto TextResizer::Make::make(TextResizerInitInfo init_info) -> TextResizer* {
		return new TextResizer{std::move(*this), init_info};
	}
	
	TextResizer::TextResizer(Make&& make, TextResizerInitInfo init_info) :
		BaseTextResizer{make.line_spacing, make.align, make.algorithm, init_info} {
	}
	
	auto TextResizer::move(sf::Vector2f offset) -> void {
		start_render_ += offset;
		end_render_ += offset;
		
		for(auto& character: characters_) {
			character->move(offset);
		}
		
		for(auto& line: lines_) {
			line->move(offset);
		}
	}
	
	auto TextResizer::set_position(sf::Vector2f position) -> void {
		sf::Vector2f offset{position - start_render_};
		for(auto& character: characters_) {
			character->move({offset});
		}
		
		for(auto& line: lines_) {
			line->move(offset);
		}
		
		end_render_ += offset;
		start_render_ = position;
	}
	
	auto TextResizer::print_character(std::vector<BaseCharacter*>::iterator character) -> void {
		(*character)->set_position(next_position_);
		next_position_.x += (*character)->get_advance();
	}
	
	auto TextResizer::equalize_characters(std::vector<BaseCharacter*>::iterator end_character, float line_size, float length_end_character) -> void {
		auto offset{sf::Vector2f{end_render_.x - (((*(end_character - 1))->get_position().x) + length_end_character), line_size}};
		
		switch(align_) {
			case Align::Left:
				offset.x = 0;
				break;
			case Align::Center:
				offset.x /= 2;
				break;
			default:
				break;
		}
		
		for(auto character = after_enter_; character != end_character; ++character) {
			(*character)->move(offset);
		}
	}
	
	auto TextResizer::equalize(std::vector<BaseCharacter*>::iterator end_character, float height_end_character) -> float {
		auto line_size{0.f};
		for(auto character = after_enter_; character != end_character; ++character) {
			if(
				character != end_character - 1 &&
				(*character)->is_special() != BaseCharacter::Special::FullLine &&
				(*character)->is_special() != BaseCharacter::Special::Object
				) {
				float character_size = (*character)->get_height();
				if(line_size < character_size)
					line_size = character_size;
			}
		}
		
		line_size *= line_spacing_;
		
		equalize_characters(end_character, line_size, 0);
		
		auto old_line{(std::vector<BoxPtr<BaseLine> > const*)nullptr};
		auto start_line{0.f};
		
		for(auto character = after_enter_; character != end_character; ++character) {
			auto& character_line = (*character)->get_line();
			if(old_line != &character_line) {
				auto character_pos{(*character)->get_position()};
				if(old_line) {
					for(auto& line: *old_line) {
						auto copy_line{line->copy()};
						copy_line->resize(start_line, character_pos.x, character_pos.y);
						this->lines_.emplace_back(copy_line);
					}
				}
				
				old_line = &character_line;
				start_line = character_pos.x;
			}
		}
		
		if(old_line) {
			auto character{[this, end_character] {
				if(end_character != characters_.begin() + 1 && (*(end_character - 1))->is_special() != BaseCharacter::Special::No) {
					return *(end_character - 2);
				}
				return *(end_character - 1);
			}()};
			auto line_end{character->get_position()};
			line_end.x += character->get_advance();
			
			for(auto& line: *old_line) {
				auto copy_line{line->copy()};
				copy_line->resize(start_line, line_end.x, line_end.y);
				this->lines_.emplace_back(copy_line);
			}
		}
		return line_size;
	}
	
	auto TextResizer::porting(std::vector<BaseCharacter*>::iterator end_character) -> void {
		next_position_.y += equalize(end_character, 0);
		next_position_.x = start_render_.x;
		
		after_enter_ = end_character;
	}
	
	auto TextResizer::auto_porting(std::vector<BaseCharacter*>::iterator end_character) -> void {
		next_position_.y += equalize(after_space_, 0);
		next_position_.x = start_render_.x;
		
		for(auto character = after_space_; character != end_character; ++character) {
			print_character(character);
		}
		
		after_enter_ = after_space_;
		after_space_ = end_character;
	}
	
	auto TextResizer::delete_old_cash(sf::Vector2f size, sf::Vector2f position) -> void {
		lines_.clear();
		
		start_render_ = position;
		end_render_ = position + size;
		this->next_position_ = start_render_;
		
		after_enter_ = characters_.begin();
		after_space_ = characters_.begin();
	}
	
	auto TextResizer::character_resize() -> void {
		if(algorithm_ == BaseTextResizer::Algorithm::Console) {
			return space_resize();
		}
		
		print_character(current_character_);
	}
	
	auto TextResizer::space_resize() -> void {
		if(algorithm_ == BaseTextResizer::Algorithm::Absolute) {
			return character_resize();
		}
		
		if(this->next_position_.x + (algorithm_ == BaseTextResizer::Algorithm::Console ? (*current_character_)->get_advance() : 0) <= end_render_.x) {
			print_character(current_character_);
			after_space_ = current_character_ + 1;
		} else {
			auto_porting(current_character_ + 1);
		}
	}
	
	auto TextResizer::enter_resize() -> void {
		(*current_character_)->set_position(next_position_);
		if(this->next_position_.x > end_render_.x) {
			auto_porting(current_character_ + 1);
		}
		porting(current_character_ + 1);
	}
	
	auto TextResizer::object_resize(bool full) -> void {
		if(next_position_.x != start_render_.x) {
			enter_resize();
		}
		after_enter_ = current_character_;
		if(full) {
			(*current_character_)->resize(next_position_, end_render_.x);
		} else {
			(*current_character_)->set_position(next_position_);
			next_position_.x = start_render_.x;
		}
		auto line_size{line_spacing_ * (*current_character_)->get_height()};
		equalize_characters(current_character_ + 1, line_size, (*current_character_)->get_advance());
		next_position_.y += line_size;
		after_enter_ = current_character_ + 1;
	}
	
	auto TextResizer::end_line_equalize() -> void {
		if(end_render_.x < this->next_position_.x) {
			auto_porting(characters_.end());
		}
		equalize(characters_.end(), 0);
	}
	
	auto TextResizer::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		if(characters_.empty()) {
			start_render_ = position;
			end_render_ = position + size;
			return;
		}
		if(size.x == end_render_.x - start_render_.x) {
			set_position(position);
			return;
		}
		
		delete_old_cash(size, position);
		for(current_character_ = characters_.begin(); current_character_ != characters_.end(); ++current_character_) {
			//printf("%c", static_cast<char>((*current_character)->get_char()));
			switch((*current_character_)->is_special()) {
				case BaseCharacter::Special::No:
					character_resize();
					break;
				case BaseCharacter::Special::Space:
					space_resize();
					break;
				case BaseCharacter::Special::Enter:
					enter_resize();
					break;
				case BaseCharacter::Special::Object:
					object_resize(false);
					break;
				case BaseCharacter::Special::FullLine:
					object_resize(true);
					break;
			}
		}
		
		end_line_equalize();
	}
	
	auto TextResizer::get_position() -> sf::Vector2f {
		return start_render_;
	}
	
	auto TextResizer::get_size() -> sf::Vector2f {
		if(characters_.empty()) {
			return {0, 0};
		}
		auto max_x{
			std::max_element(characters_.begin(), characters_.end(), [](BaseCharacter* elem, BaseCharacter* elem2) {
				return elem->get_position().x < elem2->get_position().x;
			})
		};
		
		auto max_y{
			std::max_element(characters_.begin(), characters_.end(), [](BaseCharacter* elem, BaseCharacter* elem2) {
				return elem->get_position().y < elem2->get_position().y;
			})
		};
		return sf::Vector2f{(*max_x)->get_position().x, (*max_y)->get_position().y} - get_position();
	}
	
	auto TextResizer::get_min_size_base() -> sf::Vector2f {
		auto min_size{sf::Vector2f{0, 0}};
		auto word_size_x{0.f};
		
		for(auto& character: characters_) {
			if(character->is_special() == BaseCharacter::Special::No) {
				word_size_x += character->get_min_advance();
			} else {
				if(min_size.x < word_size_x)
					min_size.x = word_size_x;
				word_size_x = 0;
			}
		}
		if(min_size.x < word_size_x) {
			min_size.x = word_size_x;
		}
		
		return min_size;
	}
	
	auto TextResizer::get_min_size_console() -> sf::Vector2f {
		auto min_size{sf::Vector2f{0, 0}};
		
		auto advance{0.f};
		for(auto& character: characters_) {
			advance = character->get_min_advance();
			if(advance > min_size.x)
				min_size.x = advance;
		}
		return min_size;
	}
	
	auto TextResizer::get_min_size_absolute() -> sf::Vector2f {
		auto min_size{sf::Vector2f{0, 0}};
		auto string_size_x{0.f};
		
		for(auto& character: characters_) {
			if(character->is_special() != BaseCharacter::Special::Enter) {
				string_size_x += character->get_min_advance();
			} else {
				if(min_size.x < string_size_x)
					min_size.x = string_size_x;
				string_size_x = 0;
			}
		}
		if(min_size.x < string_size_x) {
			min_size.x = string_size_x;
		}
		
		return min_size;
	}
	
	auto TextResizer::get_normal_size() -> sf::Vector2f {
		return get_min_size();
	}
}

auto ieml::Decode<char, ie::TextResizer::Make>::decode(ieml::Node const& node) -> orl::Option<ie::TextResizer::Make> {
	auto map{node.get_map_view().except()};
	return ie::TextResizer::Make{
		map.get_as<float>("line-spacing").except().ok_or(1.15f),
		map.get_as<ie::BaseTextResizer::Align>("align").except().ok_or(ie::BaseTextResizer::Align::Left),
		map.get_as<ie::BaseTextResizer::Algorithm>("algorithm").except().ok_or(ie::BaseTextResizer::Algorithm::Base),
	};
}
