#pragma once

#include "modules/appendix/exception/baseException.hpp"

namespace ui {
	class YamlBuilderDoesNotExistException : public BaseException {
	public:
		explicit YamlBuilderDoesNotExistException(const std::string& yamlBuilderName);
	};
}
