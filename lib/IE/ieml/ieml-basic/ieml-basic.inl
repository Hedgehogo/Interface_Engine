//included into ieml-basic.hpp

namespace tnl {
	template<typename T_>
	auto TypeName<bp::BoxPtr<T_> >::type_name() -> StringView {
		return tnl::type_name<T_*>();
	}
	
	template<typename T_>
	auto TypeName<orl::Option<T_> >::type_name() -> StringView {
		static auto name{[] {
			auto name{tnl::type_name<T_>()};
			return String{"Option("} + String{name.begin(), name.end()} + String{")"};
		}()};
		return {name};
	}
	
	template<typename T_>
	auto TypeName<std::vector<T_> >::type_name() -> StringView {
		static auto name{[] {
			auto name{tnl::type_name<T_>()};
			return String{"Vec("} + String{name.begin(), name.end()} + String{")"};
		}()};
		return {name};
	}
	
	template<typename K_, typename V_>
	auto TypeName<absl::flat_hash_map<K_, V_> >::type_name() -> StringView {
		static auto name{[] {
			auto key_name{tnl::type_name<K_>()};
			auto value_name{tnl::type_name<V_>()};
			return
				String{"Map("} + String{key_name.begin(), key_name.end()} +
				String{", "} + String{value_name.begin(), value_name.end()} + String{")"};
		}()};
		return {name};
	}
}

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
