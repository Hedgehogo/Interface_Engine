#include "Text.hpp"

#include <cmath>

namespace ie {
	Text::Make::Make(
		std::vector<BoxPtr<BaseTextBlock::Make>>&& text_blocks,
		sf::Font& font,
		BoxPtr<INonInteractive::Make>&& background,
		size_t size,
		sf::Color text_color,
		sf::Color text_selection_color,
		sf::Color background_selection_color,
		sf::Color inactive_text_selection_color,
		sf::Color inactive_background_selection_color,
		sf::Text::Style style,
		BoxPtr<BaseTextResizer::Make>&& resizer,
		BoxPtr<IBasicInteraction<Text&>::Make>&& text_interaction
	) : text_blocks(std::move(text_blocks)),
		font(font),
		background(std::move(background)),
		size(size),
		text_color(text_color),
		text_selection_color(text_selection_color),
		background_selection_color(background_selection_color),
		inactive_text_selection_color(inactive_text_selection_color),
		inactive_background_selection_color(inactive_background_selection_color),
		style(style),
		resizer(std::move(resizer)),
		text_interaction(std::move(text_interaction)) {
	}
	
	auto Text::Make::make(InitInfo init_info) -> Text* {
		return new Text{std::move(*this), init_info};
	}
	
	Text::Text(Make&& make, InitInfo init_info) :
		interaction_manager(&init_info.interaction_manager),
		render_target(&init_info.render_target),
		background(make.background->make(init_info)),
		interact(false),
		old_interact(false),
		size(make.size),
		text_blocks(
			map_make(
				std::move(make.text_blocks),
				TextBockInitInfo{
					init_info,
					render_texture,
					draw_manager,
					*interaction_manager,
					TextBockInitInfo::TextVariables{
						make.text_color,
						make.text_selection_color,
						make.background_selection_color,
						make.inactive_text_selection_color,
						make.inactive_background_selection_color,
						make.font,
						make.style,
						make.size
					}
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
		text_interaction(make.text_interaction->make({init_info, *this})) {
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
	
	auto Text::get_character(sf::Vector2f mouse_position) -> orl::Option<std::vector<BaseCharacter*>::iterator> {
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
				auto distance_y_to_iterator{get_distance_y(iterator, mouse_position.y)};
				auto distance_y_to_result{get_distance_y(value, mouse_position.y)};
				if(distance_y_to_iterator <= distance_y_to_result) {
					if((distance_y_to_iterator < distance_y_to_result) || min_distance_x(iterator, value, mouse_position.x)) {
						return iterator;
					}
				}
				return value;
			}).some_or(iterator);
		}
		
		for(auto& value: result) {
			if(mouse_position.x > (*value)->get_position().x + (static_cast<float>((*value)->get_size_texture().x) / 2.f)) {
				++value;
			}
		}
		
		return result;
	}
	
	auto Text::update() -> void {
		if(interact != old_interact) {
			old_interact = interact;
			
			if(interact) {
				interaction_manager->add_interaction(*text_interaction);
			} else {
				interaction_manager->delete_interaction(*text_interaction);
			}
		}
		interact = false;
		
		for(auto& text_block: text_blocks) {
			text_block->update();
		}
	}
	
	auto Text::update_interactions(sf::Vector2f mouse_position) -> bool {
		interact = true;
		
		for(auto& text_bock: text_blocks) {
			if(text_bock->in(mouse_position)) {
				if(text_bock->update_interactions(mouse_position)) {
					return true;
				}
			}
		}
		return background->update_interactions(mouse_position);
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
				line->draw();
			}
			render_texture.display();
			texture = render_texture.getTexture();
			sprite.setTexture(texture);
		}
		
		render_target->draw(sprite);
	}
	
	auto Text::move(sf::Vector2f position) -> void {
		view.reset({get_position() + position, view.getSize()});
		render_texture.setView(view);
		sprite.move(position);
		background->move(position);
		resizer->move(position);
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
	auto color{map.get_as<sf::Color>("text-color").except().ok_or(sf::Color::Black)};
	return ie::Text::Make{
		map.at("text-blocks").except().as<std::vector<bp::BoxPtr<ie::BaseTextBlock::Make> > >().except(),
		map.at("font").except().as<sf::Font&>().except(),
		map.get_as<bp::BoxPtr<ie::INonInteractive::Make> >("background").except().ok_or_else([] {
			return bp::make_box_ptr<ie::INonInteractive::Make, ie::FullColor::Make>(sf::Color::White);
		}),
		map.get_as<size_t>("font-size").except().ok_or(14),
		color,
		map.get_as<sf::Color>("text-selection-color").except().ok_or(sf::Color::White),
		map.get_as<sf::Color>("background-selection-color").except().ok_or(sf::Color::Blue),
		map.get_as<sf::Color>("inactive-text-selection-color").except().ok_or(color),
		map.get_as<sf::Color>("inactive-background-selection-color").except().ok_or(
			sf::Color{150, 150, 150}
		),
		map.get_as<ie::LoadTextStyle>("style").except().ok_or({}).style,
		map.get_as<bp::BoxPtr<ie::BaseTextResizer::Make> >("resizer").except().ok_or_else([] {
			return bp::make_box_ptr<ie::BaseTextResizer::Make, ie::TextResizer::Make>(1.15f, ie::BaseTextResizer::Align::Left);
		}),
		map.get_as<bp::BoxPtr<ie::IBasicInteraction<ie::Text&>::Make> >("text-interaction").except().ok_or_else([] {
			return bp::make_box_ptr<ie::IBasicInteraction<ie::Text&>::Make, ie::BasicEmptyInteraction<ie::Text&>::Make>();
		}),
	};
}
