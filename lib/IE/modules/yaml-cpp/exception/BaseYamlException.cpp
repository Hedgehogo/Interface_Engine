#include "BaseYamlException.hpp"

namespace ie {
	BaseYamlException::BaseYamlException(YAML::Mark mark) :
		mark_(mark) {
	}
	
	std::string BaseYamlException::get_note() const {
		return std::to_string(mark_.line) + std::string(", ") + std::to_string(mark_.column) + std::string(": ");
	}
	
	YAML::Mark BaseYamlException::get_mark() const {
		return mark_;
	}
}