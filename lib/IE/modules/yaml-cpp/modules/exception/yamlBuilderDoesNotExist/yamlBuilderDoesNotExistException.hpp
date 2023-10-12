#pragma once

#include "IE/Modules/exception/baseException.hpp"

namespace ie {
	class YamlBuilderDoesNotExistException : public BaseException {
	public:
		explicit YamlBuilderDoesNotExistException(const std::string& yamlBuilderName);
	};
}
