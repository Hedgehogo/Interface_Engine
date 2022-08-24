#include "bufferException.hpp"

namespace ui {
	BufferVariableNotFoundException::BufferVariableNotFoundException(std::string name, const std::type_info& type) : str(
		std::string("Failed to read buffer variable '") + name + std::string("' as '") + std::string(type.name()) + std::string("' type")) {
	}
	
	const char *BufferVariableNotFoundException::what() const noexcept {
		return str.c_str();
	}
	
	BufferNonExistentNestingLevelException::BufferNonExistentNestingLevelException(std::string name, long long int level) : str(
		std::string("An attempt was made to put the Buffer variable '") + name + std::string("' on a non-existent nesting level, the '") + std::to_string(level) + std::string("' level")) {}
	
	const char *BufferNonExistentNestingLevelException::what() const noexcept {
		return str.c_str();
	}
}