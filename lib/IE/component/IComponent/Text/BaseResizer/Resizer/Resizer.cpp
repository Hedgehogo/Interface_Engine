#include "Resizer.hpp"

namespace ie {
	Resizer::Make::Make(float line_spacing, BaseResizer::Align align, BaseResizer::Algorithm algorithm) : line_spacing(line_spacing), align(align), algorithm(algorithm) {
	}
	
	Resizer* Resizer::Make::make(ResizerInitInfo init_info) {
		return new Resizer{std::move(*this), init_info};
	}
	
	Resizer::Resizer(Make&& make, ResizerInitInfo init_info) : BaseResizer{make.line_spacing, make.align, make.algorithm, init_info} {
	}
	
	void Resizer::move(sf::Vector2f position) {
		start_render += position;
		end_render += position;
		
		for(auto& character: characters) {
			character->move(position);
		}
		
		for(auto& line: lines) {
			line->move(position);
		}
	}
	
	void Resizer::set_position(sf::Vector2f position) {
		sf::Vector2f offset{position - start_render};
		for(auto& character: characters) {
			character->move({offset});
		}
		
		for(auto& line: lines) {
			line->move(offset);
		}
		
		end_render += offset;
		start_render = position;
	}
	
	void Resizer::print_character(std::vector<BaseCharacter*>::iterator character) {
		(*character)->set_position(next_position);
		next_position.x += (*character)->get_advance();
	}
	
	void Resizer::equalize_characters(std::vector<BaseCharacter*>::iterator end_character, float line_size, float length_end_character ) {
		sf::Vector2f offset{end_render.x - (((*(end_character - 1))->get_position().x) + length_end_character), line_size};
		
		switch(align) {
			case Align::Left:
				offset.x = 0;
				break;
			case Align::Center:
				offset.x /= 2;
				break;
			default:
				break;
		}
		
		for(auto character = after_enter; character != end_character; ++character) {
				(*character)->move(offset);
		}
	}
	
	float Resizer::equalize(std::vector<BaseCharacter*>::iterator end_character, float height_end_character) {
		float line_size{0};
		for(auto character = after_enter; character != end_character; ++character) {
			if(character != end_character - 1 && (*character)->is_special() !=  BaseCharacter::Special::FullLine && (*character)->is_special() !=  BaseCharacter::Special::Object) {
				float character_size = (*character)->get_height();
				if(line_size < character_size)
					line_size = character_size;
			}
		}
		
		line_size *= line_spacing;
		
		equalize_characters(end_character, line_size, 0);
		
		const std::vector<BoxPtr<BaseLine>>* old_line = nullptr;
		float start_line = 0;
		
		for(auto character = after_enter; character != end_character; ++character) {
			auto& character_line = (*character)->get_line();
			if(old_line != &character_line) {
				sf::Vector2f character_pos = (*character)->get_position();
				if(old_line) {
					for(auto& line: *old_line) {
						BaseLine* copy_line = line->copy();
						copy_line->resize(start_line, character_pos.x, character_pos.y);
						this->lines.emplace_back(copy_line);
					}
				}
				
				old_line = &character_line;
				start_line = character_pos.x;
			}
		}
		
		if(old_line) {
			BaseCharacter* character = *(end_character - ((end_character != characters.begin() + 1 && (*(end_character - 1))->is_special() != BaseCharacter::Special::No) ? 2 : 1));
			sf::Vector2f line_end = character->get_position();
			line_end.x += character->get_advance();
			
			for(auto& line: *old_line) {
				BaseLine* copy_line = line->copy();
				copy_line->resize(start_line, line_end.x, line_end.y);
				this->lines.emplace_back(copy_line);
			}
		}
		return line_size;
	}
	
	void Resizer::porting(std::vector<BaseCharacter*>::iterator end_character) {
		next_position.y += equalize(end_character, 0);
		next_position.x = start_render.x;
		
		after_enter = end_character;
	}
	
	void Resizer::auto_porting(std::vector<BaseCharacter*>::iterator end_character) {
		next_position.y += equalize(after_space, 0);
		next_position.x = start_render.x;
		
		for(auto character = after_space; character != end_character; ++character) {
			print_character(character);
		}
		
		after_enter = after_space;
		after_space = end_character;
	}
	
	void Resizer::delete_old_cash(sf::Vector2f size, sf::Vector2f position) {
		lines.clear();
		
		start_render = position;
		end_render = position + size;
		this->next_position = start_render;
		
		after_enter = characters.begin();
		after_space = characters.begin();
	}
	
	void Resizer::character_resize() {
		if(algorithm == BaseResizer::Algorithm::Console)
			return space_resize();
		
		print_character(current_character);
	}
	
	void Resizer::space_resize() {
		if(algorithm == BaseResizer::Algorithm::Absolute)
			return character_resize();
		
		if(this->next_position.x + (algorithm == BaseResizer::Algorithm::Console ? (*current_character)->get_advance() : 0) <= end_render.x) {
			print_character(current_character);
			after_space = current_character + 1;
		} else {
			auto_porting(current_character + 1);
		}
	}
	
	void Resizer::enter_resize() {
		(*current_character)->set_position(next_position);
		if(this->next_position.x > end_render.x)
			auto_porting(current_character + 1);
		porting(current_character + 1);
	}
	
	void Resizer::object_resize(bool full) {
		if(next_position.x != start_render.x) {
			enter_resize();
		}
		after_enter = current_character;
		if(full) {
			(*current_character)->resize(next_position, end_render.x);
		} else {
			(*current_character)->set_position(next_position);
			next_position.x = start_render.x;
		}
		float line_size{line_spacing * (*current_character)->get_height()};
		equalize_characters(current_character + 1, line_size, (*current_character)->get_advance());
		next_position.y += line_size;
		after_enter = current_character + 1;
	}
	
	void Resizer::end_line_equalize() {
		if(end_render.x < this->next_position.x) {
			auto_porting(characters.end());
		}
		equalize(characters.end(), 0);
	}
	
	void Resizer::resize(sf::Vector2f size, sf::Vector2f position) {
		if(characters.empty()) {
			start_render = position;
			end_render = position + size;
			return;
		}
		if(size.x == end_render.x - start_render.x) {
			set_position(position);
			return;
		}
		
		delete_old_cash(size, position);
		size_t count = 0;
		for(current_character = characters.begin(); current_character != characters.end(); ++current_character) {
			//printf("%c", static_cast<char>((*current_character)->get_char()));
			switch((*current_character)->is_special()) {
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
			++count;
		}
		
		end_line_equalize();
	}
	
	sf::Vector2f Resizer::get_position() {
		return start_render;
	}
	
	sf::Vector2f Resizer::get_size() {
		if(characters.empty())
			return {0, 0};
		std::vector<BaseCharacter*>::iterator max_x{
			std::max_element(characters.begin(), characters.end(), [](BaseCharacter* elem, BaseCharacter* elem2) {
				return elem->get_position().x < elem2->get_position().x;
			})
		};
		
		std::vector<BaseCharacter*>::iterator max_y{
			std::max_element(characters.begin(), characters.end(), [](BaseCharacter* elem, BaseCharacter* elem2) {
				return elem->get_position().y < elem2->get_position().y;
			})
		};
		return sf::Vector2f{(*max_x)->get_position().x, (*max_y)->get_position().y} - get_position();
	}
	
	sf::Vector2f Resizer::get_min_size_base() {
		sf::Vector2f min_size = {0, 0};
		float word_size_x = 0;
		
		for(auto& character: characters) {
			if(character->is_special() == BaseCharacter::Special::No) {
				word_size_x += character->get_min_advance();
			} else {
				if(min_size.x < word_size_x)
					min_size.x = word_size_x;
				word_size_x = 0;
			}
		}
		if(min_size.x < word_size_x)
			min_size.x = word_size_x;
		
		return min_size;
	}
	
	sf::Vector2f Resizer::get_min_size_console() {
		sf::Vector2f min_size = {0, 0};
		
		float advance = 0;
		for(auto& character: characters) {
			advance = character->get_min_advance();
			if(advance > min_size.x)
				min_size.x = advance;
		}
		return min_size;
	}
	
	sf::Vector2f Resizer::get_min_size_absolute() {
		sf::Vector2f min_size = {0, 0};
		float string_size_x = 0;
		
		for(auto& character: characters) {
			if(character->is_special() != BaseCharacter::Special::Enter) {
				string_size_x += character->get_min_advance();
			} else {
				if(min_size.x < string_size_x)
					min_size.x = string_size_x;
				string_size_x = 0;
			}
		}
		if(min_size.x < string_size_x)
			min_size.x = string_size_x;
		
		return min_size;
	}
	
	sf::Vector2f Resizer::get_normal_size() {
		return get_min_size();
	}
	
	Resizer* Resizer::copy() {
		return new Resizer{*this};
	}
	
	bool DecodePointer<Resizer>::decode_pointer(const YAML::Node& node, Resizer*& resizer) {
/*
		resizer = new Resizer{
			conv_def(node["line-spacing"], 1.15f),
			conv_def(node["align"], BaseResizer::Align::Left),
			conv_def(node["algorithm"], BaseResizer::Algorithm::Base)
		};
		return true;
*/
		
		throw std::runtime_error("DecodePointer<Resizer>::decode_pointer() not correct");
	}
}
