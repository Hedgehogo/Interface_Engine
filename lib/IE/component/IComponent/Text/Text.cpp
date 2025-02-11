#include "Text.hpp"

#include <cmath>

namespace ie {
	Text::Make::Make(
		std::vector<BoxPtr<BaseTextBlock::Make>>&& text_blocks,
		BoxPtr<INonInteractive::Make>&& background,
		BoxPtr<BaseTextResizer::Make>&& resizer,
		BoxPtr<IBasicTrigger<Text&>::Make>&& text_trigger
	) : text_blocks(std::move(text_blocks)),
	    background(std::move(background)),
	    resizer(std::move(resizer)),
	    text_trigger(std::move(text_trigger)) {
	}
	
	auto Text::Make::make(InitInfo init_info) -> Text* {
		return new Text{std::move(*this), init_info};
	}
	
	Text::Text(Make&& make, InitInfo init_info) :
		trigger_manager(&init_info.trigger_manager),
		render_target(&init_info.render_target),
		background(make.background->make(init_info)),
		text_blocks(
			map_make(
				std::move(make.text_blocks),
				TextBockInitInfo{
					init_info,
					render_texture,
					draw_manager,
					*trigger_manager,
				}
			)
		),
		resizer([this, &make] {
			for(auto& text_block: this->text_blocks) {
				text_block->set_kerning(text_characters.empty() ? U'\0' : text_characters[text_characters.size() - 1]->get_char());
				auto characters{text_block->get_characters()};
				text_characters.insert(text_characters.end(), characters.begin(), characters.end());
			}
			return make.resizer->make(TextResizerInitInfo(text_characters));
		}()),
		text_trigger(make.text_trigger->make({init_info, *this})) {
		init_info.update_manager.add(*this);
		init_info.draw_manager.add(*this);
	}
	
	auto Text::set_selection(Text::Selection selection) -> void {
		this->selection = selection;
	}
	
	auto Text::set_selection_start(orl::Option<std::vector<BaseCharacter*>::iterator> start) -> void {
		selection.start = start;
	}
	
	auto Text::set_selection_end(orl::Option<std::vector<BaseCharacter*>::iterator> end) -> void {
		selection.end = end;
	}
	
	auto Text::get_selection() const -> Text::Selection {
		return selection;
	}
	
	auto Text::get_selection_start() const -> std::vector<BaseCharacter*>::iterator {
		return selection.start.except();
	}
	
	auto Text::get_selection_end() const -> std::vector<BaseCharacter*>::iterator {
		return selection.end.except();
	}
	
	auto Text::get_selection_text() -> sf::String {
		for(auto [local_start, local_end]: selection.start && selection.end) {
			auto selection_text{sf::String{}};
			if(std::distance(local_start, local_end) < 0) {
				std::swap(local_start, local_end);
			}
			
			for(auto item = local_start; item != local_end; ++item) {
				selection_text += (*(item))->get_char();
			}
			
			return selection_text;
		}
		return sf::String{""};
	}
	
	auto Text::get_characters() -> std::vector<BaseCharacter*>& {
		return text_characters;
	}
	
	auto Text::get_character(sf::Vector2f point_position) -> orl::Option<std::vector<BaseCharacter*>::iterator> {
		using Iterator = std::vector<BaseCharacter*>::iterator;
		
		auto get_distance_y = [](Iterator iterator, float mouse_position_y) -> float {
			return std::min(
				std::abs(mouse_position_y - (*iterator)->get_position().y),
				std::abs(mouse_position_y - ((*iterator)->get_position().y - (*iterator)->get_height()))
			);
		};
		
		auto min_distance_x = [](Iterator first, Iterator second, float find) -> bool {
			auto distance_to_first{std::abs((*first)->get_position().x - find)};
			auto distance_to_first1{std::abs((*first)->get_position().x + (*first)->get_advance() - find)};
			auto distance_to_second{std::abs((*second)->get_position().x - find)};
			auto distance_to_second1{std::abs((*second)->get_position().x + (*second)->get_advance() - find)};
			if(distance_to_first > distance_to_first1) {
				std::swap(distance_to_first, distance_to_first1);
			}
			if(distance_to_second > distance_to_second1) {
				std::swap(distance_to_second, distance_to_second1);
			}
			
			if(distance_to_first == distance_to_second) {
				return distance_to_first1 < distance_to_second1;
			}
			return distance_to_first < distance_to_second;
		};
		
		auto result{orl::Option<Iterator>{}};
		
		for(auto iterator = text_characters.begin(); iterator != text_characters.end(); ++iterator) {
			result = result.map([=](auto& value) {
				auto distance_y_to_iterator{get_distance_y(iterator, point_position.y)};
				auto distance_y_to_result{get_distance_y(value, point_position.y)};
				if(distance_y_to_iterator <= distance_y_to_result) {
					if((distance_y_to_iterator < distance_y_to_result) || min_distance_x(iterator, value, point_position.x)) {
						return iterator;
					}
				}
				return value;
			}).some_or(iterator);
		}
		
		for(auto& value: result) {
			if(point_position.x > (*value)->get_position().x + (static_cast<float>((*value)->get_size_texture().x) / 2.f)) {
				++value;
			}
		}
		
		return result;
	}
	
	auto Text::update() -> void {
		text_trigger->update();
		
		for(auto& text_block: text_blocks) {
			text_block->update();
		}
	}
	
	auto Text::handle_event(Event event) -> bool {
		return
			text_trigger->handle_event(event) ||
			event.pointer().map([=](event_system::Pointer pointer) {
				for(auto& text_bock: text_blocks) {
					if(text_bock->in(sf::Vector2f{pointer.position})) {
						if(text_bock->handle_event(event)) {
							return true;
						}
					}
				}
				return background->handle_event(event);
			}).some_or_else([=] {
				auto updated{false};
				for(auto& text_block: text_blocks) {
					updated = text_block->handle_event(event) || updated;
				}
				return background->handle_event(event) || updated;
			});
	}
	
	auto Text::draw() -> void {
		auto rerender{false};
		for(auto& character: text_characters) {
			if(character->get_rerender()) {
				rerender = true;
				character->set_rerender(false);
			}
		}
		
		if(rerender) {
			render_texture.clear(sf::Color{0, 0, 0, 0});
			
			draw_manager.draw();
			
			for(auto& character: text_characters) {
				character->draw();
			}
			
			for(auto& line: resizer->get_lines()) {
				line->draw(&render_texture);
			}
			render_texture.display();
			texture = render_texture.getTexture();
			sprite.setTexture(texture);
		}
		
		render_target->draw(sprite);
	}
	
	auto Text::move(sf::Vector2f offset) -> void {
		view.reset({get_position() + offset, view.getSize()});
		render_texture.setView(view);
		sprite.move(offset);
		background->move(offset);
		resizer->move(offset);
	}
	
	auto Text::set_position(sf::Vector2f position) -> void {
		view.reset({position, view.getSize()});
		render_texture.setView(view);
		sprite.setPosition(position);
		background->set_position(position);
		resizer->set_position(position);
	}
	
	auto Text::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		resizer->resize(size, position);
		
		size = max(resizer->get_size(), size);
		background->resize(size, position);
		
		view.reset({position, size});
		render_texture.create(size.x, size.y);
		render_texture.setView(view);
		sprite.setTextureRect({{0, 0}, sf::Vector2i(size)});
	}
	
	auto Text::get_area_position() const -> sf::Vector2f {
		return background->get_area_position();
	}
	
	auto Text::get_area_size() const -> sf::Vector2f {
		return max(background->get_area_size(), resizer->get_size());
	}
	
	auto Text::get_min_size() const -> sf::Vector2f {
		return max(resizer->get_min_size(), background->get_min_size());
	}
	
	auto Text::get_normal_size() const -> sf::Vector2f {
		return max(resizer->get_normal_size(), background->get_normal_size());
	}
	
	auto Text::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		for(BaseCharacter*& character: text_characters) {
			character->draw_debug(render_target, indent_addition, hue + hue_offset, hue_offset);
		}
		
		background->draw_debug(render_target, indent, indent_addition, hue + hue_offset, hue_offset);
	}
}

auto ieml::Decode<char, ie::Text::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Text::Make> {
	auto map{node.get_map_view().except()};
	return ie::Text::Make{
		map.at("text-blocks").except().as<std::vector<bp::BoxPtr<ie::BaseTextBlock::Make> > >().except(),
		map.get_as<bp::BoxPtr<ie::INonInteractive::Make> >("background").except().ok_or_else([] {
			return bp::make_box_ptr<ie::INonInteractive::Make, ie::FullColor::Make>(sf::Color::White);
		}),
		map.get_as<bp::BoxPtr<ie::BaseTextResizer::Make> >("resizer").except().ok_or_else([] {
			return bp::make_box_ptr<ie::BaseTextResizer::Make, ie::TextResizer::Make>(1.15f, ie::BaseTextResizer::Align::Left);
		}),
		map.get_as<bp::BoxPtr<ie::IBasicTrigger<ie::Text&>::Make> >("text-trigger").except().ok_or_else([] {
			return bp::make_box_ptr<ie::IBasicTrigger<ie::Text&>::Make, ie::BasicEmptyTrigger<ie::Text&>::Make>();
		}),
	};
}
