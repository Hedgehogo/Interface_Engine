#include "baseYamlException.hpp"

namespace ui {
	BaseYamlException::BaseYamlException(YAML::Mark mark, const std::string& description) :
		BaseException(std::to_string(mark.line) + std::string(", ") + std::to_string(mark.column) + description), mark(mark) {}
	
	YAML::Mark BaseYamlException::getMark() { return mark; }
}