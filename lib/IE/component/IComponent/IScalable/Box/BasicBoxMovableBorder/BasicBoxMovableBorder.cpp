#include "BasicBoxMovableBorder.hpp"

auto ieml::Decode<char, ie::BoxMovableBorder::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxMovableBorder::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxMovableBorder::Make{
		map.at("first-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("second-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<bool>("border-horizontal").except().ok_or(false),
		map.at("border-value").except().as<ie::MakeDyn<ie::ISRFloat> >().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
