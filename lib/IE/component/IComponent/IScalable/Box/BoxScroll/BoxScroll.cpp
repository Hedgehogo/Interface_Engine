#include "BoxScroll.hpp"

namespace ie {
	BoxScroll::Make::Make(BoxPtr<IComponent::Make>&& object, MakeDyn<ISRVec2F> normal_object_position, sf::Vector2f min_size) :
		object(std::move(object)), normal_object_position(std::move(normal_object_position)), min_size(min_size) {
	}
	
	BoxScroll* BoxScroll::Make::make(InitInfo init_info) {
		return new BoxScroll{std::move(*this), init_info};
	}
	
	BoxScroll::BoxScroll(Make&& make, InitInfo init_info) :
		BoxView(make.min_size, init_info),
		object_(make.object->make(init_info.copy(this->draw_manager_))),
		normal_object_position_(
			make.normal_object_position.make(init_info.dyn_buffer),
			[&](sf::Vector2f value) {
				this->object_->set_position(get_new_object_position(value));
			}
		) {
		normal_object_position_.get().get_x().set_bounds(0, 1);
		normal_object_position_.get().get_y().set_bounds(0, 1);
	}
	
	sf::Vector2f BoxScroll::get_min_size() const {
		return max(minimum_size_, object_->get_min_size());
	}
	
	sf::Vector2f BoxScroll::get_normal_size() const {
		return object_->get_normal_size();
	}
	
	sf::Vector2f BoxScroll::get_new_object_position(sf::Vector2f normal_object_position) {
		sf::Vector2f max_offset{object_->get_size() - layout_.size};
		sf::Vector2f offset{mul_xy(max_offset, normal_object_position)};
		return layout_.position - offset;
	}
	
	void BoxScroll::resize(sf::Vector2f size, sf::Vector2f position) {
		BoxView::resize(size, position);
		
		object_->set_size(size);
		
		sf::Vector2f object_size{object_->get_size()};
		if(object_size.x == size.x && object_size.y == size.y)
			return object_->set_position(position);
		object_->set_position(get_new_object_position(normal_object_position_.get().get()));
	}
	
	bool BoxScroll::update_interactions(sf::Vector2f mouse_position) {
		return object_->update_interactions(mouse_position);
	}
}

orl::Option<ie::BoxScroll::Make> ieml::Decode<char, ie::BoxScroll::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::BoxScroll::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IComponent::Make> >().move_except(),
		map.at("normal-object-position").except().as<ie::MakeDyn<ie::ISRVec2F> >().move_except(),
		map.get_as<sf::Vector2f>("min-size").ok_or({}),
	};
}
