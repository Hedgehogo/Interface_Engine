#include "yamlBuilderDoesTotExistException.hpp"

namespace ui {
	YamlBuilderDoesTotExistException::YamlBuilderDoesTotExistException(const std::string& yamlBuilderName) :
		BaseException("BaseYamlBuilder: '" + yamlBuilderName + "' does not exist, but was requested by the module") {}
} // ui