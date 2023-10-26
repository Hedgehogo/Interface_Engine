#include "BaseYamlException.hpp"

namespace ie {
	BaseYamlException::BaseYamlException(YAML::Mark mark, const std::string& description) :
		BaseException(std::to_string(mark.line) + std::string(", ") + std::to_string(mark.column) + std::string(": ") + description), mark_(mark) {
	}
	
	YAML::Mark BaseYamlException::get_mark() {
		return mark_;
	}
}