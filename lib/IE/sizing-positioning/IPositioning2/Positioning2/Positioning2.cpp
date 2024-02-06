#include "Positioning2.hpp"
#include "IE/sizing-positioning/IPositioning/Functions/make_position/make_position.hpp"

namespace ie {
	Positioning2::Make::Make(BoxPtr<IPositioning>&& horizontal, BoxPtr<IPositioning>&& vertical) :
		horizontal(std::move(horizontal)), vertical(std::move(vertical)) {
	}
	
	Positioning2::Make::Make(sf::Vector2f coefficient, sf::Vector2f offset, bool relative_target) :
		horizontal(make_position(coefficient.x, offset.x, relative_target)),
		vertical(make_position(coefficient.y, offset.y, relative_target)) {
	}
	
	Positioning2::Make::Make(Location2 parent_location, Location2 object_location, sf::Vector2f offset) :
		horizontal(new MatchSidesPositioning{
			get_horizontal_location(parent_location),
			get_horizontal_location(object_location),
			offset.x
		}),
		vertical(new MatchSidesPositioning{
			get_vertical_location(parent_location),
			get_vertical_location(object_location),
			offset.y
		}) {
	}
	
	Positioning2::Make::Make(sf::Vector2f coefficient, sf::Vector2f object_coefficient, sf::Vector2f offset, bool relative_target) :
		horizontal(make_position(coefficient.x, object_coefficient.x, offset.x, relative_target)),
		vertical(make_position(coefficient.y, object_coefficient.y, offset.y, relative_target)) {
	}
	
	Positioning2* Positioning2::Make::make(Positioning2InitInfo init_info) {
		return new Positioning2{std::move(*this), init_info};
	}
	
	Positioning2::Positioning2(Make&& make, Positioning2InitInfo init_info) :
		horizontal_(std::move(make.horizontal)), vertical_(std::move(make.vertical)), render_target_(&init_info.render_target) {
	}
	
	sf::Vector2f Positioning2::find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size) {
		sf::Vector2f target_size{static_cast<sf::Vector2f>(render_target_->getSize())};
		return {horizontal_->find_position(parent_position.x, object_size.x, parent_size.x, target_size.x),
				vertical_->find_position(parent_position.y, object_size.y, parent_size.y, target_size.y)};
	}
}

orl::Option<ie::Positioning2::Make> ieml::Decode<char, ie::Positioning2::Make>::decode(ieml::Node const& node) {
	auto& clear_node{node.get_clear()};
	if(auto result{clear_node.as<sf::Vector2f>()}) {
		return {{result.ok()}};
	}
	auto map{clear_node.get_map_view().except()};
	auto target_coefficient{map.at("target-coefficient")};
	auto parent_coefficient{map.at("parent-coefficient")};
	if(target_coefficient.is_ok() || parent_coefficient.is_ok()) {
		auto relative_target{target_coefficient.is_ok()};
		auto& coefficient_node{relative_target ? target_coefficient.ok() : parent_coefficient.ok()};
		auto coefficient{coefficient_node.as<sf::Vector2f>().except()};
		auto offset{map.get_as<sf::Vector2f>("offset").ok_or({})};
		if(auto object_coefficient_node{map.at("object-coefficient")}) {
			auto object_coefficient{object_coefficient_node.ok().as<sf::Vector2f>().except()};
			return {{coefficient, object_coefficient, offset, relative_target}};
		} else {
			return {{coefficient, offset, relative_target}};
		}
	}
	auto parent_location{map.at("parent-location")};
	auto object_location{map.at("object-location")};
	if(parent_location.is_ok() && object_location.is_ok()) {
		return ie::Positioning2::Make{
			parent_location.ok().as<ie::Location2>().except(),
			object_location.ok().as<ie::Location2>().except(),
			map.get_as<sf::Vector2f>("offset").ok_or({})
		};
	}
	return ie::Positioning2::Make{
		map.at("horizontal").except().as<ie::BoxPtr<ie::IPositioning> >().move_except(),
		map.at("vertical").except().as<ie::BoxPtr<ie::IPositioning> >().move_except(),
	};
}
