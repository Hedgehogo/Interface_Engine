#pragma once

#include <IEML/helpers/get_type_name/get_type_name.hpp>

namespace ie::meta {
	std::string& removable_namespace();
	
	std::string_view remove_namespace(std::string_view input);
}
