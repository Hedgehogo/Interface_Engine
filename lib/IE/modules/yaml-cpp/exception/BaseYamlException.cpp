#include "BaseYamlException.hpp"

namespace ie {
	BaseYamlException::BaseYamlException(YAML::Mark mark) :
		mark_(mark) {
	}
	
	auto BaseYamlException::get_note() const -> std::string {
		return std::to_string(mark_.line) + std::string(", ") + std::to_string(mark_.column) + std::string(": ");
	}
	
	auto BaseYamlException::get_mark() const -> YAML::Mark {
		return mark_;
	}
}