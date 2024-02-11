#include "Sizing2.hpp"
#include "IE/sizing-positioning/ISizing/Functions/make_size_make/make_size_make.hpp"

namespace ie {
	Sizing2::Make::Make(BoxPtr<ISizing::Make>&& horizontal, BoxPtr<ISizing::Make>&& vertical) :
		horizontal(std::move(horizontal)), vertical(std::move(vertical)) {
	}
	
	Sizing2::Make::Make(bool relative_parent) :
		horizontal(make_size_make(relative_parent)), vertical(make_size_make(relative_parent)) {
	}
	
	Sizing2::Make::Make(sf::Vector2f const_size) :
		horizontal(make_size_make(const_size.x)), vertical(make_size_make(const_size.y)) {
	}
	
	Sizing2::Make::Make(sf::Vector2f coefficient, sf::Vector2f addition, bool relative_target) :
		horizontal(make_size_make(coefficient.x, addition.x, relative_target)),
		vertical(make_size_make(coefficient.y, addition.y, relative_target)) {
	}
	
	Sizing2::Make::Make(sf::Vector2f target_coefficient, sf::Vector2f parent_coefficient, sf::Vector2f addition) :
		horizontal(make_size_make(target_coefficient.x, parent_coefficient.x, addition.x)),
		vertical(make_size_make(target_coefficient.y, parent_coefficient.y, addition.y)) {
	}
	
	Sizing2* Sizing2::Make::make(Sizing2InitInfo init_info) {
		return new Sizing2{std::move(*this), init_info};
	}
	
	Sizing2::Sizing2(Make&& make, Sizing2InitInfo init_info) :
		horizontal_(make.horizontal->make(init_info.normal_size.x)),
		vertical_(make.vertical->make(init_info.normal_size.y)),
		render_target_(&init_info.render_target) {
	}
	
	sf::Vector2f Sizing2::find_size(sf::Vector2f parent_size) {
		sf::Vector2f target_size{render_target_->getSize()};
		return {horizontal_->find_size(parent_size.x, target_size.x), vertical_->find_size(parent_size.y, target_size.y)};
	}
	
	sf::Vector2f Sizing2::get_parent_size(sf::Vector2f object_size) {
		return {horizontal_->get_parent_size(object_size.x), vertical_->get_parent_size(object_size.y)};
	}
}

orl::Option<ie::Sizing2::Make> ieml::Decode<char, ie::Sizing2::Make>::decode(ieml::Node const& node) {
	auto& clear_node{node.get_clear()};
	for(auto result: clear_node.as<sf::Vector2f>().ok_or_none()) {
		return {{result}};
	}
	auto map{clear_node.get_map_view().except()};
	for(auto& relative: map.at("relative-parent").ok_or_none()) {
		return {{relative.as<bool>().except()}};
	}
	for(auto& const_size: map.at("const-size").ok_or_none()) {
		return {{const_size.as<sf::Vector2f>().except()}};
	}
	auto target_coefficient_node{map.at("target-coefficient").ok_or_none()};
	auto parent_coefficient_node{map.at("parent-coefficient").ok_or_none()};
	for(auto& [target_coefficient, parent_coefficient]: target_coefficient_node && parent_coefficient_node) {
		return ie::Sizing2::Make{
			target_coefficient.as<sf::Vector2f>().except(),
			parent_coefficient.as<sf::Vector2f>().except(),
			map.get_as<sf::Vector2f>("addition").ok_or({})
		};
	}
	for(auto& coefficient: target_coefficient_node || parent_coefficient_node) {
		auto relative_target{target_coefficient_node.is_some()};
		return ie::Sizing2::Make{
			coefficient.as<sf::Vector2f>().except(),
			map.get_as<sf::Vector2f>("addition").ok_or({}),
			relative_target
		};
	}
	return ie::Sizing2::Make{
		map.at("horizontal").except().as<ie::BoxPtr<ie::ISizing::Make> >().except(),
		map.at("vertical").except().as<ie::BoxPtr<ie::ISizing::Make> >().except(),
	};
}
