//included into ieml-sfml.hpp

namespace ieml {
	template<typename T>
	orl::Option<orl::Option<T> > Decode<char, orl::Option<T> >::decode(ieml::Node const& node) {
		if(!node.is_null()) {
			return orl::Option<T>{node.as<T>().except()};
		}
		return orl::Option<T>{};
	}
	
	template<typename T>
	orl::Option<std::vector<T> > Decode<char, std::vector<T> >::decode(ieml::Node const& node) {
		auto& list = node.get_list().except();
		std::vector<T> result{};
		result.reserve(list.size());
		for(auto& item: list) {
			result.push_back(item.as<T>());
		}
		return result;
	}
	
	template<typename T>
	orl::Option<sf::Vector2<T> > Decode<char, sf::Vector2<T> >::decode(ieml::Node const& node) {
		return sf::Vector2<T>{
			node.at(0).except().as<T>().except(),
			node.at(1).except().as<T>().except(),
		};
	}
	
	template<typename T>
	orl::Option<sf::Rect<T> > Decode<char, sf::Rect<T> >::decode(ieml::Node const& node) {
		auto map{node.get_map_view().except()};
		auto position{map.at("position").except().as<sf::Vector2<T> >().except()};
		auto size{map.at("size").except().as<sf::Vector2<T> >().except()};
		return sf::Rect<T>{position, size};
	}
}