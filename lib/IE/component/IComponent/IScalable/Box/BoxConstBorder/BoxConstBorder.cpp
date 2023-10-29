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
		const_object_(make.const_object->make(init_info)),
		second_object_(make.second_object->make(init_info)),
		border_distance_(make.border_distance),
		side_(make.side) {
	}
	
	BoxConstBorder::BoxConstBorder(BoxPtr<IScalable>&& const_object, BoxPtr<IScalable>&& second_object, Side side, float border_distance, sf::Vector2f min_size) :
		Box(min_size), const_object_(std::move(const_object)), second_object_(std::move(second_object)), border_distance_(border_distance), side_(side) {
	}
	
	void BoxConstBorder::init(InitInfo init_info) {
		const_object_->init(init_info);
		second_object_->init(init_info);
	}
	
	void BoxConstBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		
		switch(side_) {
			case Side::Up:
				const_object_->resize({size.x, border_distance_}, position);
				second_object_->resize({size.x, size.y - border_distance_}, position + sf::Vector2f(0, border_distance_));
				break;
			case Side::Down:
				const_object_->resize({size.x, border_distance_}, {position.x, position.y + size.y - border_distance_});
				second_object_->resize({size.x, size.y - border_distance_}, position);
				break;
			case Side::Left:
				const_object_->resize({border_distance_, size.y}, position);
				second_object_->resize({size.x - border_distance_, size.y}, position + sf::Vector2f(border_distance_, 0));
				break;
			case Side::Right:
				const_object_->resize({border_distance_, size.y}, {position.x + size.x - border_distance_, position.y});
				second_object_->resize({size.x - border_distance_, size.y}, position);
				break;
		}
	}
	
	bool BoxConstBorder::update_interactions(sf::Vector2f mouse_position) {
		if(const_object_->in_area(mouse_position)) {
			return const_object_->update_interactions(mouse_position);
		}
		return second_object_->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxConstBorder::get_min_size() const {
		sf::Vector2f const_min_size = const_object_->get_min_size();
		sf::Vector2f second_min_size = second_object_->get_min_size();
		if(side_ == Side::Down || side_ == Side::Up) {
			return {std::max(const_min_size.x, second_min_size.x), second_min_size.y + border_distance_};
		} else {
			return {second_min_size.x + border_distance_, std::max(const_min_size.y, second_min_size.y)};
		}
	}
	
	sf::Vector2f BoxConstBorder::get_normal_size() const {
		sf::Vector2f const_normal_size = const_object_->get_normal_size();
		sf::Vector2f second_normal_size = second_object_->get_normal_size();
		if(side_ == Side::Down || side_ == Side::Up) {
			return {std::max(const_normal_size.x, second_normal_size.x), second_normal_size.y + border_distance_};
		} else {
			return {second_normal_size.x + border_distance_, std::max(const_normal_size.y, second_normal_size.y)};
		}
	}
	
	IScalable& BoxConstBorder::get_first_object() {
		return *const_object_;
	}
	
	const IScalable& BoxConstBorder::get_first_object() const {
		return *const_object_;
	}
	
	IScalable& BoxConstBorder::get_second_object() {
		return *second_object_;
	}
	
	const IScalable& BoxConstBorder::get_second_object() const {
		return *second_object_;
	}
	
	BoxConstBorder* BoxConstBorder::copy() {
		return new BoxConstBorder{*this};
	}
	
	void BoxConstBorder::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		const_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
	
	/*old_yaml_decode_pointer_impl
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
	*/
}