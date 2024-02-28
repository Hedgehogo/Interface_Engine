#pragma once

#include <string>

namespace ie::meta {
	std::string& removable_namespace();
	
	std::string_view remove_namespace(std::string_view input);
}
