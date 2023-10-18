#include "YamlBuilderDoesNotExistException.hpp"

namespace ie {
	YamlBuilderDoesNotExistException::YamlBuilderDoesNotExistException(const std::string& yaml_builder_name) :
		BaseException("BaseYamlBuilder: '" + yaml_builder_name + "' does not exist, but was requested by the module") {}
}