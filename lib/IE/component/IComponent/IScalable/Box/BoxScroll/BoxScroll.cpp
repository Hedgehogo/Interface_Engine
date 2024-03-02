#include "BoxScroll.hpp"

namespace ie {
	BoxScroll::Make::Make(BoxPtr<IComponent::Make>&& object, MakeDyn<ISRVec2F> normal_object_position, sf::Vector2f min_size) :
		object(std::move(object)), normal_object_position(std::move(normal_object_position)), min_size(min_size) {
	}
	
	auto BoxScroll::Make::make(InitInfo init_info) -> BoxScroll* {
		return new BoxScroll{std::move(*this), init_info};
	}
	
	BoxScroll::BoxScroll(Make&& make, InitInfo init_info) :
		BoxView(make.min_size, init_info),
		object_(make.object->make(init_info.copy(this->draw_manager_))),
		normal_object_position_(
			make.normal_object_position.make(SInitInfo{init_info}),
			[&](sf::Vector2f value) {
				this->object_->set_position(get_new_object_position(value));
			}
		) {
		normal_object_position_.get().get_x().set_bounds(0, 1);
		normal_object_position_.get().get_y().set_bounds(0, 1);
	}
	
	auto BoxScroll::get_min_size() const -> sf::Vector2f {
		return max(minimum_size_, object_->get_min_size());
	}
	
	auto BoxScroll::get_normal_size() const -> sf::Vector2f {
		return object_->get_normal_size();
	}
	
	auto BoxScroll::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		BoxView::resize(size, position);
		
		object_->set_size(size);
		
		auto object_size{object_->get_size()};
		if(object_size.x == size.x && object_size.y == size.y) {
			return object_->set_position(position);
		}
		object_->set_position(get_new_object_position(normal_object_position_.get().get()));
	}
	
	auto BoxScroll::update_interactions(sf::Vector2f mouse_position) -> bool {
		return object_->update_interactions(mouse_position);
	}
	
	auto BoxScroll::get_new_object_position(sf::Vector2f normal_object_position) -> sf::Vector2f {
		auto max_offset{object_->get_size() - layout_.size};
		auto offset{mul_xy(max_offset, normal_object_position)};
		return layout_.position - offset;
	}
}

auto ieml::Decode<char, ie::BoxScroll::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxScroll::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxScroll::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IComponent::Make> >().except(),
		map.at("normal-object-position").except().as<ie::MakeDyn<ie::ISRVec2F> >().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({}),
	};
}
