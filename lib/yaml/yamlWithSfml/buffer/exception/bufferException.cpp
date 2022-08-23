#include "bufferException.hpp"

namespace ui {
	BufferBadCastException::BufferBadCastException(std::string name, const std::type_info& type) : str(
		std::string("Failed to read buffer variable '") + name + std::string("' as '") + std::string(type.name()) + std::string("' type")) {
	}
	
	const char *BufferBadCastException::what() const throw() {
		return str.c_str();
	}
}