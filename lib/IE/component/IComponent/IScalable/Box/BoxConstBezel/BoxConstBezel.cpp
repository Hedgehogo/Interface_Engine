#include "BoxConstBezel.hpp"

namespace ie {
	BoxConstBezel::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& bezel, float thickness, sf::Vector2f min_size) :
		object(std::move(object)), bezel(std::move(bezel)), thickness(thickness), min_size(min_size) {
	}
	
	BoxConstBezel* BoxConstBezel::Make::make(InitInfo init_info) {
		return new BoxConstBezel{std::move(*this), init_info};
	}
	
	BoxConstBezel::BoxConstBezel(Make&& make, InitInfo init_info) :
		Box(make.min_size), bezel_(make.bezel->make(init_info)), object_(make.object->make(init_info)), thickness_(make.thickness) {
	}
	
	BoxConstBezel::BoxConstBezel(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& bezel, float thickness, sf::Vector2f min_size) :
		Box(min_size), bezel_(std::move(bezel)), object_(std::move(object)), thickness_(thickness) {
	}
	
	void BoxConstBezel::init(InitInfo init_info) {
		bezel_->init(init_info);
		object_->init(init_info);
	}
	
	void BoxConstBezel::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		bezel_->resize(size, position);
		object_->resize(size - sf::Vector2f(thickness_ * 2.0f, thickness_ * 2.0f), position + sf::Vector2f(thickness_, thickness_));
	}
	
	bool BoxConstBezel::update_interactions(sf::Vector2f mouse_position) {
		if(object_->in_area(mouse_position)) {
			return object_->update_interactions(mouse_position);
		}
		return bezel_->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxConstBezel::get_min_size() const {
		return max(object_->get_min_size() + sf::Vector2f{thickness_ * 2, thickness_ * 2}, bezel_->get_min_size(), minimum_size_);
	}
	
	sf::Vector2f BoxConstBezel::get_normal_size() const {
		return max(object_->get_normal_size() + sf::Vector2f{thickness_ * 2, thickness_ * 2}, bezel_->get_normal_size());
	}
	
	IScalable& BoxConstBezel::get_object() {
		return *object_;
	}
	
	const IScalable& BoxConstBezel::get_object() const {
		return *object_;
	}
	
	BoxConstBezel* BoxConstBezel::copy() {
		return new BoxConstBezel{*this};
	}
	
	void BoxConstBezel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		bezel_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		object_->draw_debug(render_target, indent, indent_addition, hue + hue_offset, hue_offset);
	}
}

orl::Option<ie::BoxConstBezel::Make> ieml::Decode<char, ie::BoxConstBezel::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::BoxConstBezel::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		map.at("bezel").except().as<ie::BoxPtr<ie::IUninteractive::Make> >().move_except(),
		map.at("thickness").except().as<float>().except(),
		map.get_as<sf::Vector2f>("min-size").ok_or({})
	};
}
