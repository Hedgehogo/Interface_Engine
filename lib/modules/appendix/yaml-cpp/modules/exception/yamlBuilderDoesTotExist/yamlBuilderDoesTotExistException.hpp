#pragma once

#include "modules/appendix/exception/baseException.hpp"

namespace ui {
	class YamlBuilderDoesTotExistException : public BaseException{
	public:
		explicit YamlBuilderDoesTotExistException(const std::string& yamlBuilderName);
	};
}
