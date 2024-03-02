#pragma once

#include <string>

namespace ie::meta {
	auto removable_namespace() -> std::string&;
	
	auto remove_namespace(std::string_view input) -> std::string_view;
}
