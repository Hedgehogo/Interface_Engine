#include "BoxConstBorder.hpp"

namespace ie {
	BoxConstBorder::Make::Make(
		BoxPtr<IScalable::Make>&& const_object,
		BoxPtr<IScalable::Make>&& second_object,
		float border_distance,
		Side side,
		sf::Vector2f min_size
	) : const_object(std::move(const_object)), second_object(std::move(second_object)), border_distance(border_distance), side(side), min_size(min_size) {
	}
	
	BoxConstBorder* BoxConstBorder::Make::make(InitInfo init_info) {
		return new BoxConstBorder{std::move(*this), init_info};
	}
	
	BoxConstBorder::BoxConstBorder(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		const_object(make.const_object->make(init_info)),
		second_object(make.second_object->make(init_info)),
		border_distance(make.border_distance),
		side(make.side) {
	}
	
	BoxConstBorder::BoxConstBorder(BoxPtr<IScalable>&& const_object, BoxPtr<IScalable>&& second_object, Side side, float border_distance, sf::Vector2f min_size) :
		Box(min_size), const_object(std::move(const_object)), second_object(std::move(second_object)), border_distance(border_distance), side(side) {
	}
	
	void BoxConstBorder::init(InitInfo init_info) {
		const_object->init(init_info);
		second_object->init(init_info);
	}
	
	void BoxConstBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		
		switch(side) {
			case Side::Up:
				const_object->resize({size.x, border_distance}, position);
				second_object->resize({size.x, size.y - border_distance}, position + sf::Vector2f(0, border_distance));
				break;
			case Side::Down:
				const_object->resize({size.x, border_distance}, {position.x, position.y + size.y - border_distance});
				second_object->resize({size.x, size.y - border_distance}, position);
				break;
			case Side::Left:
				const_object->resize({border_distance, size.y}, position);
				second_object->resize({size.x - border_distance, size.y}, position + sf::Vector2f(border_distance, 0));
				break;
			case Side::Right:
				const_object->resize({border_distance, size.y}, {position.x + size.x - border_distance, position.y});
				second_object->resize({size.x - border_distance, size.y}, position);
				break;
		}
	}
	
	bool BoxConstBorder::update_interactions(sf::Vector2f mouse_position) {
		if(const_object->in_area(mouse_position)) {
			return const_object->update_interactions(mouse_position);
		}
		return second_object->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxConstBorder::get_min_size() const {
		sf::Vector2f const_min_size = const_object->get_min_size();
		sf::Vector2f second_min_size = second_object->get_min_size();
		if(side == Side::Down || side == Side::Up) {
			return {std::max(const_min_size.x, second_min_size.x), second_min_size.y + border_distance};
		} else {
			return {second_min_size.x + border_distance, std::max(const_min_size.y, second_min_size.y)};
		}
	}
	
	sf::Vector2f BoxConstBorder::get_normal_size() const {
		sf::Vector2f const_normal_size = const_object->get_normal_size();
		sf::Vector2f second_normal_size = second_object->get_normal_size();
		if(side == Side::Down || side == Side::Up) {
			return {std::max(const_normal_size.x, second_normal_size.x), second_normal_size.y + border_distance};
		} else {
			return {second_normal_size.x + border_distance, std::max(const_normal_size.y, second_normal_size.y)};
		}
	}
	
	IScalable& BoxConstBorder::get_first_object() {
		return *const_object;
	}
	
	const IScalable& BoxConstBorder::get_first_object() const {
		return *const_object;
	}
	
	IScalable& BoxConstBorder::get_second_object() {
		return *second_object;
	}
	
	const IScalable& BoxConstBorder::get_second_object() const {
		return *second_object;
	}
	
	BoxConstBorder* BoxConstBorder::copy() {
		return new BoxConstBorder{*this};
	}
	
	void BoxConstBorder::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		const_object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
	
	bool DecodePointer<BoxConstBorder>::decode_pointer(const YAML::Node& node, BoxConstBorder*& box_with_const_border) {
		box_with_const_border = new BoxConstBorder{
			node["const-object"].as<BoxPtr<IScalable> >(),
			node["second-object"].as<BoxPtr<IScalable> >(),
			node["side"].as<Side>(),
			node["border-distance"].as<float>(),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}