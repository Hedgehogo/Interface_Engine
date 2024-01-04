#include "Text.hpp"

#include <cmath>

namespace ie {
	Text::Make::Make(
		std::vector<BoxPtr<BaseTextBlock::Make>>&& text_blocks,
		sf::Font* font,
		BoxPtr<IUninteractive::Make>&& background,
		size_t size,
		sf::Color text_color,
		sf::Color text_selection_color,
		sf::Color background_selection_color,
		sf::Color inactive_text_selection_color,
		sf::Color inactive_background_selection_color,
		sf::Text::Style style,
		BoxPtr<BaseResizer::Make>&& resizer,
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
	
	Text* Text::Make::make(InitInfo init_info) {
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
		resizer(nullptr),
		text_interaction(nullptr) {
		text_interaction.set(make.text_interaction->make({init_info, *this}));
		for(auto& text_block: this->text_blocks) {
			text_block->set_kerning(text_characters.empty() ? U'\0' : text_characters[text_characters.size() - 1]->get_char());
			std::vector<BaseCharacter*> characters = text_block->get_characters();
			text_characters.insert(text_characters.end(), characters.begin(), characters.end());
		}
		resizer = BoxPtr{make.resizer->make(ResizerInitInfo(text_characters, lines))};
		
		init_info.update_manager.add(*this);
		init_info.draw_manager.add(*this);
	}
	
	Text::Text(
		std::vector<BoxPtr<BaseTextBlock>>&& text_blocks,
		sf::Font*,
		BoxPtr<IUninteractive>&& background,
		int size,
		sf::Color,
		sf::Color,
		sf::Color,
		sf::Color,
		sf::Color,
		sf::Text::Style,
		BoxPtr<BaseResizer>&& resizer,
		BoxPtr<IBasicInteraction<Text&>>&& text_interaction
	) : interaction_manager(nullptr),
		background(std::move(background)),
		size(size),
		text_blocks(std::move(text_blocks)),
		resizer(std::move(resizer)),
		text_interaction(std::move(text_interaction)) {
		for(auto& text_block: this->text_blocks) {
			std::vector<BaseCharacter*> characters = text_block->get_characters();
			text_characters.insert(text_characters.end(), characters.begin(), characters.end());
		}
		this->resizer->init(ResizerInitInfo(text_characters, lines));
	}
	
	void Text::init(InitInfo) {
/*
		this->interaction_manager = &init_info.interaction_manager;
		this->render_target = &init_info.render_target;
		init_info.update_manager.add(*this);
		background->init(init_info);
		init_info.draw_manager.add(*this);
		
		for(auto& text_block: text_blocks) {
			text_block->init({init_info, render_texture, draw_manager, *interaction_manager});
		}
		
		text_interaction->init({init_info, *this});
*/
		throw std::runtime_error("Text::init() not correct");
	}
	
	void Text::set_selection(Text::Selection selection) {
		this->selection = selection;
	}
	
	void Text::set_selection_start(orl::Option<std::vector<BaseCharacter*>::iterator> start) {
		selection.start = start;
	}
	
	void Text::set_selection_end(orl::Option<std::vector<BaseCharacter*>::iterator> end) {
		selection.end = end;
	}
	
	Text::Selection Text::get_selection() const {
		return selection;
	}
	
	std::vector<BaseCharacter*>::iterator Text::get_selection_start() const {
		return selection.start.except();
	}
	
	std::vector<BaseCharacter*>::iterator Text::get_selection_end() const {
		return selection.end.except();
	}
	
	std::u32string Text::get_selection_text() {
		if(selection.start && selection.end) {
			std::u32string SelectionText{};
			std::vector<BaseCharacter*>::iterator local_start;
			std::vector<BaseCharacter*>::iterator local_end;
			if(std::distance(selection.start.some(), selection.end.some()) < 0) {
				local_start = selection.end.some();
				local_end = selection.start.some();
			} else {
				local_start = selection.start.some();
				local_end = selection.end.some();
			}
			SelectionText.resize(std::distance(local_start, local_end));
			
			for(size_t i = 0; i < SelectionText.length(); ++i) {
				SelectionText[i] = (*(local_start + i))->get_char();
			}
			
			return SelectionText;
		}
		return std::u32string{U""};
	}
	
	float get_distance_y(std::vector<BaseCharacter*>::iterator iterator, float mouse_position_y) {
		return std::min(std::abs(mouse_position_y - (*iterator)->get_position().y), std::abs(mouse_position_y - ((*iterator)->get_position().y - (*iterator)->get_height())));
	}
	
	bool min_distance_x(std::vector<BaseCharacter*>::iterator& a, std::vector<BaseCharacter*>::iterator& b, float find) {
		float distance_to_a{std::abs((*a)->get_position().x - find)},
			distance_to_a1{std::abs((*a)->get_position().x + (*a)->get_advance() - find)},
			distance_to_b{std::abs((*b)->get_position().x - find)},
			distance_to_b1{std::abs((*b)->get_position().x + (*b)->get_advance() - find)};
		if(distance_to_a > distance_to_a1)
			std::swap(distance_to_a, distance_to_a1);
		if(distance_to_b > distance_to_b1)
			std::swap(distance_to_b, distance_to_b1);
		
		if(distance_to_a == distance_to_b) {
			return distance_to_a1 < distance_to_b1;
		} else {
			return distance_to_a < distance_to_b;
		}
	}
	
	orl::Option<std::vector<BaseCharacter*>::iterator> Text::get_character(sf::Vector2f mouse_position) {
		orl::Option<std::vector<BaseCharacter*>::iterator> result{};
		
		for(auto iterator = text_characters.begin(); iterator != text_characters.end(); ++iterator) {
			if(result) {
				float DistanceYToIterator{get_distance_y(iterator, mouse_position.y)};
				float DistanceYToResult{get_distance_y(result.some(), mouse_position.y)};
				if(DistanceYToIterator <= DistanceYToResult) {
					if(DistanceYToIterator < DistanceYToResult) {
						result = iterator;
					}
					if(min_distance_x(iterator, result.some(), mouse_position.x)) {
						result = iterator;
					}
				}
			} else {
				result = iterator;
			}
		}
		
		if(mouse_position.x > (*result.except())->get_position().x + (static_cast<float>((*result.except())->get_size_texture().x) / 2.f)) {
			++result.some();
		}
		
		return result;
	}
	
	void Text::update() {
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
	
	bool Text::update_interactions(sf::Vector2f mouse_position) {
		interact = true;
		
		for(auto& text_bock: text_blocks) {
			
			if(text_bock->in(mouse_position))
				if(text_bock->update_interactions(mouse_position))
					return true;
		}
		return background->update_interactions(mouse_position);
	}
	
	void Text::draw() {
		bool rerender{false};
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
			
			for(auto& character: text_characters) {
				character->draw();
			}
			
			for(auto& line: lines) {
				line->draw();
			}
			render_texture.display();
			texture = render_texture.getTexture();
			sprite.setTexture(texture);
		}
		
		render_target->draw(sprite);
	}
	
	void Text::move(sf::Vector2f position) {
		view.reset({get_position() + position, view.getSize()});
		render_texture.setView(view);
		sprite.move(position);
		background->move(position);
		resizer->move(position);
	}
	
	void Text::set_position(sf::Vector2f position) {
		view.reset({position, view.getSize()});
		render_texture.setView(view);
		sprite.setPosition(position);
		background->set_position(position);
		resizer->set_position(position);
	}
	
	void Text::resize(sf::Vector2f size, sf::Vector2f position) {
		resizer->resize(size, position);
		
		size = max(resizer->get_size(), size);
		background->resize(size, position);
		
		view.reset({position, size});
		render_texture.create(size.x, size.y);
		render_texture.setView(view);
		sprite.setTextureRect({{0, 0}, sf::Vector2i(size)});
	}
	
	sf::Vector2f Text::get_area_position() const {
		return background->get_area_position();
	}
	
	sf::Vector2f Text::get_area_size() const {
		return max(background->get_area_size(), resizer->get_size());
	}
	
	sf::Vector2f Text::get_min_size() const {
		return max(resizer->get_min_size(), background->get_min_size());
	}
	
	sf::Vector2f Text::get_normal_size() const {
		return max(resizer->get_normal_size(), background->get_normal_size());
	}
	
	Text* Text::copy() {
		return nullptr;
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<Text>::decode_pointer(const YAML::Node& node, Text*& text) {
		sf::Color text_color{conv_def(node["text-color"], sf::Color::Black)};
		
		text = new Text{
			node["text-block"] ? std::vector{node["text-block"].as <BoxPtr<BaseTextBlock> > ()} : node["text-blocks"].as<std::vector<BoxPtr<BaseTextBlock>>>(),
			node["font"].as<sf::Font*>(),
			conv_def_box_ptr<IUninteractive, FullColor>(node["background"], sf::Color::White),
			conv_def(node["size"], 14),
			text_color,
			conv_def(node["text-selection-color"], sf::Color::White),
			conv_def(node["background-selection-color"], sf::Color::Blue),
			conv_def(node["inactive-text-selection-color"], text_color),
			conv_def(node["inactive-background-selection-color"],sf::Color{150, 150, 150}),
			conv_def<sf::Text::Style>(node["style"], {}),
			conv_def_box_ptr<BaseResizer, Resizer>(node["resizer"], 1.15f, BaseResizer::Align::Left),
			node["text-interaction"] ? node["text-interaction"].as < BoxPtr < IBasicInteraction<Text&>>>() : make_box_ptr<BasicEmptyInteraction<Text&>>()};
		return true;

	}
	*/
	
	void Text::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		for(BaseCharacter*& character: text_characters) {
			character->draw_debug(render_target, indent_addition, hue + hue_offset, hue_offset);
		}
		
		background->draw_debug(render_target, indent, indent_addition, hue + hue_offset, hue_offset);
	}
}