#include "BoxMovableBorder.hpp"
#include "IE/interaction/IAction/BasicKeyAction/BasicAddInteractionAction/BasicAddBlockInteractionAction/BasicAddBlockInteractionAction.hpp"
#include <algorithm>

namespace ie {
	BoxMovableBorder::Make::Make(
		BoxPtr<IScalable::Make>&& first_object,
		BoxPtr<IScalable::Make>&& second_object,
		bool is_horizontal_border,
		PSCoefficient border_value,
		int border_interaction_size,
		Key key,
		sf::Vector2f min_size
	) :
		first_object(std::move(first_object)),
		second_object(std::move(second_object)),
		is_horizontal_border(is_horizontal_border),
		border_value(border_value),
		border_interaction_size(border_interaction_size),
		key(key),
		min_size(min_size) {
	}
	
	BoxMovableBorder* BoxMovableBorder::Make::make(InitInfo init_info) {
		return new BoxMovableBorder{std::move(*this), init_info};
	}
	
	BoxMovableBorder::BoxMovableBorder(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		interactive(make_box_ptr<BasicOneKeyInteraction<BoxMovableBorder&>::Make>(
			make_box_ptr<BasicAddBlockInteractionAction<BoxMovableBorder&>::Make>(
				make_box_ptr<BasicOneKeyInteraction<BoxMovableBorder&>::Make, BasicPressedInteraction<BoxMovableBorder&>::Make>(
					make_box_ptr<MovableBorderAction::Make>(), make.key
				)
			), make.key
		), init_info, *this),
		first_object(make.first_object->make(init_info)),
		second_object(make.second_object->make(init_info)),
		border_value(make.border_value),
		border_value_now(border_value->get_value()),
		border_interaction_size(make.border_interaction_size),
		is_horizontal_border(make.is_horizontal_border) {
		border_value->add_setter([&](float) {
			this->resize(layout.size, layout.position);
		});
		init_info.update_manager.add(*this);
	}
	
	BoxMovableBorder::BoxMovableBorder(
		BoxPtr<IScalable>&& first_object,
		BoxPtr<IScalable>&& second_object,
		bool is_horizontal_border,
		PSCoefficient border_value,
		int border_interaction_size,
		sf::Vector2f min_size
	) :
		Box(min_size),
		interactive(make_box_ptr<BasicOneKeyInteraction<BoxMovableBorder&> >(
			make_box_ptr<BasicAddBlockInteractionAction<BoxMovableBorder&> >(
				make_box_ptr<BasicPressedInteraction<BoxMovableBorder&> >(
					make_box_ptr<MovableBorderAction>(), Key::MouseLeft
				)
			), Key::MouseLeft
		)),
		first_object(std::move(first_object)),
		second_object(std::move(second_object)),
		border_value(border_value),
		border_value_now(border_value->get_value()),
		border_interaction_size(border_interaction_size),
		is_horizontal_border(is_horizontal_border) {
		border_value->add_setter([&](float) {
			this->resize(layout.size, layout.position);
		});
	}
	
	void BoxMovableBorder::init(InitInfo init_info) {
		interactive.init(init_info, *this);
		first_object->init(init_info);
		second_object->init(init_info);
		init_info.update_manager.add(*this);
	}
	
	float BoxMovableBorder::get_border_value() {
		return border_value->get_value();
	}
	
	void BoxMovableBorder::set_border_value(float border_value) {
		this->border_value->set_value(border_value);
	}
	
	float BoxMovableBorder::get_border_value_now() {
		return this->border_value_now;
	}
	
	int BoxMovableBorder::get_border_interaction_size() {
		return this->border_interaction_size;
	}
	
	void BoxMovableBorder::set_border_interaction_size(int size) {
		this->border_interaction_size = size;
	}
	
	bool BoxMovableBorder::is_in_border(sf::Vector2f point_position) {
		if(
			point_position.x < layout.position.x ||
			point_position.x > layout.position.x + layout.size.x ||
			point_position.y < layout.position.y ||
			point_position.y > layout.position.y + layout.size.y
			) {
			return false;
		}
		if(this->is_horizontal_border) {
			int border_position = layout.size.x * border_value_now + layout.position.x;
			return point_position.x > border_position - border_interaction_size && point_position.x < border_position + border_interaction_size;
		}
		int border_position = layout.size.y * border_value_now + layout.position.y;
		return point_position.y > border_position - border_interaction_size && point_position.y < border_position + border_interaction_size;
	}
	
	bool BoxMovableBorder::get_is_horizontal_border() {
		return this->is_horizontal_border;
	}
	
	void BoxMovableBorder::update() {
		interactive.update();
	}
	
	bool BoxMovableBorder::update_interactions(sf::Vector2f mouse_position) {
		if(!this->is_in_border(mouse_position)) {
			if(this->is_horizontal_border) {
				float split_position = layout.position.x + layout.size.x * this->border_value_now;
				if(split_position > mouse_position.x) {
					return first_object->update_interactions(mouse_position);
				}
				return second_object->update_interactions(mouse_position);
			} else {
				float split_position = layout.position.y + layout.size.y * this->border_value_now;
				if(split_position > mouse_position.y) {
					return first_object->update_interactions(mouse_position);
				}
				return second_object->update_interactions(mouse_position);
			}
		} else {
			interactive.update_interactions();
		}
		return true;
	}
	
	void BoxMovableBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		
		sf::Vector2f first_object_size;
		sf::Vector2f second_object_size;
		
		sf::Vector2f first_object_min_size = first_object->get_min_size();
		sf::Vector2f second_object_min_size = second_object->get_min_size();
		
		sf::Vector2f second_position = position;
		
		if(this->is_horizontal_border) {
			float c = second_object_min_size.x / first_object_min_size.x;
			float min_size_border = 1 - c / (c + 1);
			
			if(min_size_border > border_value->get_value()) {
				border_value_now = std::max({first_object_min_size.x / size.x, border_value->get_value()});
			} else {
				float diff = size.x - get_min_size().x;
				border_value_now = std::min({(diff + first_object_min_size.x) / size.x, border_value->get_value()});
			}
			
			first_object_size = {size.x * border_value_now, size.y};
			second_object_size = {size.x - first_object_size.x, size.y};
			second_position.x += first_object_size.x;
			
		} else {
			float c = second_object_min_size.y / first_object_min_size.y;
			float min_size_border = 1 - c / (c + 1);
			
			if(min_size_border > border_value->get_value()) {
				border_value_now = std::max({first_object_min_size.y / size.y, border_value->get_value()});
			} else {
				float diff = size.y - get_min_size().y;
				border_value_now = std::min({(diff + first_object_min_size.y) / size.y, border_value->get_value()});
			}
			
			first_object_size = {size.x, size.y * border_value_now};
			second_object_size = {size.x, size.y - first_object_size.y};
			second_position.y += first_object_size.y;
		}
		first_object->resize(first_object_size, position);
		second_object->resize(second_object_size, second_position);
	}
	
	sf::Vector2f BoxMovableBorder::get_min_size() const {
		sf::Vector2f first_min_size = first_object->get_min_size();
		sf::Vector2f second_min_size = second_object->get_min_size();
		if(this->is_horizontal_border)
			return {first_min_size.x + second_min_size.x, std::max(first_min_size.y, second_min_size.y)};
		return {std::max(first_min_size.x, second_min_size.x), std::max(first_min_size.y + second_min_size.y, this->minimum_size.y)};
	}
	
	sf::Vector2f BoxMovableBorder::get_normal_size() const {
		sf::Vector2f first_normal_size = first_object->get_normal_size();
		sf::Vector2f second_normal_size = second_object->get_normal_size();
		if(this->is_horizontal_border)
			return {first_normal_size.x + second_normal_size.x, std::max(first_normal_size.y, second_normal_size.y)};
		return {std::max(first_normal_size.x, second_normal_size.x), first_normal_size.y + second_normal_size.y};
	}
	
	IScalable& BoxMovableBorder::get_first_object() {
		return *first_object;
	}
	
	const IScalable& BoxMovableBorder::get_first_object() const {
		return *first_object;
	}
	
	IScalable& BoxMovableBorder::get_second_object() {
		return *second_object;
	}
	
	const IScalable& BoxMovableBorder::get_second_object() const {
		return *second_object;
	}
	
	BoxMovableBorder* BoxMovableBorder::copy() {
		return new BoxMovableBorder{*this};
	}
	
	void BoxMovableBorder::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		first_object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
	
	bool DecodePointer<BoxMovableBorder>::decode_pointer(const YAML::Node& node, BoxMovableBorder*& box_with_movable_border) {
		box_with_movable_border = new BoxMovableBorder{
			node["first-object"].as < BoxPtr < IScalable > > (),
			node["first-object"].as < BoxPtr < IScalable > > (),
			conv_bool_def(node["border-direction"], "horizontal", "vertical", false),
			Buffer::get<SCoefficientValue>(node["border-value"]),
			conv_def(node["border-interaction-size"], 5),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}