#pragma once

#include "IE/modules/exception/baseException.hpp"

namespace ie {
	class YamlBuilderDoesNotExistException : public BaseException {
	public:
		explicit YamlBuilderDoesNotExistException(const std::string& yamlBuilderName);
	};
}