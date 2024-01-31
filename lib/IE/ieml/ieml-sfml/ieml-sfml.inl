//included into ieml-sfml.hpp

namespace ieml {
	namespace detail {
		template<typename T>
		std::enable_if_t<std::is_arithmetic_v<T>, orl::Option<sf::Vector2<T> > >
		decode_vector2_str(BasicStringCIter<char> first, BasicStringCIter<char> last) {
			number::Parser<char, T> x_parser{std::move(first), std::move(last)};
			auto x{x_parser.parse_number_scientific()};
			if(x.is_some() && first != last && *first == ',' && (first + 1) != last && *(first + 1) == ' ') {
				number::Parser<char, T> y_parser{std::move(x_parser.pos() + 2), std::move(last)};
				auto y{y_parser.parse_number_scientific()};
				y_parser.skip_blank_line();
				if(y.is_some() && y_parser.is_complete()) {
					return sf::Vector2<T>{x.some(), y.some()};
				}
			}
			return {};
		}
	}
	
	template<typename T>
	Option<bp::BoxPtr<T> > Decode<char, bp::BoxPtr<T> >::decode(const Node& node) {
		return Decode<char, T*>::decode(node).map([](auto& value) {
			return bp::BoxPtr{value};
		});
	}
	
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
			result.push_back(item.template as<T>().move_except());
		}
		return result;
	}
	
	template<typename T>
	Option<absl::flat_hash_map<std::string, T> > Decode<char, absl::flat_hash_map<std::string, T> >::decode(const Node& node) {
		auto& map = node.get_map().except();
		absl::flat_hash_map<std::string, T> result{};
		result.reserve(map.size());
		for(auto& [key, value]: map) {
			result.insert(std::make_pair(key, value.template as<T>().move_except()));
		}
		return result;
	}
	
	template<typename T>
	orl::Option<sf::Vector2<T> > Decode<char, sf::Vector2<T> >::decode(ieml::Node const& node) {
		auto& clear_node = node.get_clear();
		if constexpr(std::is_arithmetic_v<T>) {
			if(auto raw{clear_node.get_raw()}) {
				return detail::decode_vector2_str<T>(raw.ok().str.cbegin(), raw.ok().str.cend());
			}
		}
		auto list{clear_node.get_list_view().except()};
		return sf::Vector2<T>{
			list.at(0).except().as<T>().move_except(),
			list.at(1).except().as<T>().move_except(),
		};
	}
	
	template<typename T>
	orl::Option<sf::Rect<T> > Decode<char, sf::Rect<T> >::decode(ieml::Node const& node) {
		auto map{node.get_map_view().except()};
		auto position{map.at("position").except().as<sf::Vector2<T> >().move_except()};
		auto size{map.at("size").except().as<sf::Vector2<T> >().move_except()};
		return sf::Rect<T>{std::move(position), std::move(size)};
	}
}