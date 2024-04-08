//included into ieml-basic.hpp

#include "exception/Array/ArrayException.hpp"
#include "IE/utils/array/array.hpp"

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
	
	template<typename T_, size_t size_>
	auto TypeName<std::array<T_, size_> >::type_name() -> StringView {
		static auto name{[] {
			auto name{tnl::type_name<T_>()};
			return String{"Array("} + String{name.begin(), name.end()} + String {", "} + std::to_string(size_) + String{")"};
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
	auto Decode<char, bp::BoxPtr<T> >::decode(const Node& node) -> Option<bp::BoxPtr<T> > {
		return Decode<char, T*>::decode(node).map([](auto& value) {
			return bp::BoxPtr<T>{value};
		});
	}
	
	template<typename T>
	auto Decode<char, orl::Option<T> >::decode(ieml::Node const& node) -> orl::Option<orl::Option<T> > {
		if(!node.is_null()) {
			return orl::Option<T>{node.as<T>().except()};
		}
		return orl::Option<T>{};
	}
	
	template<typename T>
	auto Decode<char, std::vector<T> >::decode(ieml::Node const& node) -> orl::Option<std::vector<T> > {
		auto& list = node.get_list().except();
		auto result{std::vector<T>{}};
		result.reserve(list.size());
		for(auto& item: list) {
			result.push_back(item.template as<T>().except());
		}
		return result;
	}
	
	template<typename T, size_t size_>
	auto Decode<char, std::array<T, size_> >::decode(ieml::Node const& node) -> orl::Option<std::array<T, size_> > {
		auto list = node.get_list_view().except();
		if(list.get_size() != size_){
			throw ie::ArrayException<size_>{node.get_mark()};
		}
		
		return ie::array_from_fn<size_>([&list](auto i){
			return list.at(i).except().template as<T>().except();
		});
	}
	
	template<typename T>
	auto Decode<char, absl::flat_hash_map<std::string, T> >::decode(const Node& node) -> Option<absl::flat_hash_map<std::string, T> > {
		auto& map = node.get_map().except();
		auto result{absl::flat_hash_map<std::string, T>{}};
		result.reserve(map.size());
		for(auto& [key, value]: map) {
			result.insert(std::make_pair(key, value.template as<T>().except()));
		}
		return result;
	}
}
