//included into ieml-sfml.hpp

namespace tnl {
	template<typename T>
	auto tnl::TypeName<sf::Vector2<T> >::type_name() -> StringView {
		static auto name{[] {
			auto name{tnl::type_name<T>()};
			return String{"Vector2("} + String{name.begin(), name.end()} + String{")"};
		}()};
		return {name};
	}
	
	template<typename T>
	auto tnl::TypeName<sf::Rect<T> >::type_name() -> StringView {
		static auto name{[] {
			auto name{tnl::type_name<T>()};
			return String{"Rect("} + String{name.begin(), name.end()} + String{")"};
		}()};
		return {name};
	}
}

namespace ieml {
	namespace detail {
		template<typename T>
		auto decode_vector2_str(
			BasicStringCIter<char> first, BasicStringCIter<char> last
		) -> std::enable_if_t<std::is_arithmetic_v<T>, orl::Option<sf::Vector2<T> > > {
			auto x_parser{number::Parser<char, T>{std::move(first), std::move(last)}};
			auto x{x_parser.parse_number_scientific()};
			if(x.is_some() && first != last && *first == ',' && (first + 1) != last && *(first + 1) == ' ') {
				auto y_parser{number::Parser<char, T>{std::move(x_parser.pos() + 2), std::move(last)}};
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
	auto Decode<char, sf::Vector2<T> >::decode(ieml::Node const& node) -> orl::Option<sf::Vector2<T> > {
		auto& clear_node = node.get_clear();
		if constexpr(std::is_arithmetic_v<T>) {
			for(auto& raw: clear_node.get_raw().ok_or_none()) {
				return detail::decode_vector2_str<T>(raw.str.cbegin(), raw.str.cend());
			}
		}
		auto list{clear_node.get_list_view().except()};
		return sf::Vector2<T>{
			list.at(0).except().as<T>().except(),
			list.at(1).except().as<T>().except(),
		};
	}
	
	template<typename T>
	auto Decode<char, sf::Rect<T> >::decode(ieml::Node const& node) -> orl::Option<sf::Rect<T> > {
		auto map{node.get_map_view().except()};
		auto position{map.at("position").except().as<sf::Vector2<T> >().except()};
		auto size{map.at("size").except().as<sf::Vector2<T> >().except()};
		return sf::Rect<T>{std::move(position), std::move(size)};
	}
}