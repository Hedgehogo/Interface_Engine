#pragma once

#include "IE/modules/exception/BaseException.hpp"

namespace ie {
	class YamlBuilderDoesNotExistException : public BaseException {
	public:
		explicit YamlBuilderDoesNotExistException(const std::string& yaml_builder_name);
	};
}