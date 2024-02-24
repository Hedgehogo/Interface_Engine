//included into ieml-basic.hpp

namespace ieml {
	template<typename T>
	Option<bp::BoxPtr<T> > Decode<char, bp::BoxPtr<T> >::decode(const Node& node) {
		return Decode<char, T*>::decode(node).map([](auto& value) {
			return bp::BoxPtr<T>{value};
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
			result.push_back(item.template as<T>().except());
		}
		return result;
	}
	
	template<typename T>
	Option<absl::flat_hash_map<std::string, T> > Decode<char, absl::flat_hash_map<std::string, T> >::decode(const Node& node) {
		auto& map = node.get_map().except();
		absl::flat_hash_map<std::string, T> result{};
		result.reserve(map.size());
		for(auto& [key, value]: map) {
			result.insert(std::make_pair(key, value.template as<T>().except()));
		}
		return result;
	}
}
