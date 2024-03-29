#include "remove_namespace.hpp"

namespace ie::meta {
	auto removable_namespace() -> std::string& {
		static std::string value{"ie"};
		return value;
	}
	
	auto remove_namespace(std::string_view input) -> std::string_view {
		auto removable_namespace_view{std::string_view{removable_namespace()}};
		if(removable_namespace_view.size() + 2 < input.size()) {
			auto input_namespace = input.substr(0, removable_namespace_view.size());
			if(input_namespace == removable_namespace_view) {
				auto input_colons = input.substr(removable_namespace_view.size(), 2);
				if(input_colons == "::") {
					return input.substr(removable_namespace_view.size() + 2);
				}
			}
		}
		return input;
	}
}
