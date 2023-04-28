#include "bufferException.hpp"

namespace ui {
	BufferNonExistentNestingLevelException::BufferNonExistentNestingLevelException(YAML::Mark mark, const std::string& name, lSize level) :
		BaseYamlException(mark, std::string("An attempt was made to put the Buffer variable '") + name + std::string("' on a non-existent nesting level, the '") + std::to_string(level) + std::string("' level")),
		name(name), level(level) {
	}
	
	std::string BufferNonExistentNestingLevelException::getName() const {
		return name;
	}
	
	BufferNonExistentNestingLevelException::lSize BufferNonExistentNestingLevelException::getLevel() const {
		return level;
	}
	
	BufferVariableNotFoundException::BufferVariableNotFoundException(const std::string& name, const std::string& type) :
		BaseException(std::string("Failed to read buffer variable '") + name + std::string("' as '") + type + std::string("' type")),
		name(name), type(type) {
	}
	
	std::string BufferVariableNotFoundException::getName() const {
		return name;
	}
	
	std::string BufferVariableNotFoundException::getType() const {
		return type;
	}
	
	YamlBufferVariableNotFoundException::YamlBufferVariableNotFoundException(YAML::Mark mark, const BufferVariableNotFoundException& exception) :
		BaseYamlException(mark, std::string("Failed to read buffer variable '") + exception.getName() + std::string("' as '") + exception.getType() + std::string("' type")),
		exception(exception) {
	}
	
	BufferVariableNotFoundException YamlBufferVariableNotFoundException::getException() const {
		return exception;
	}
	
	std::string YamlBufferVariableNotFoundException::getName() const {
		return exception.getName();
	}
	
	std::string YamlBufferVariableNotFoundException::getType() const {
		return exception.getType();
	}
}