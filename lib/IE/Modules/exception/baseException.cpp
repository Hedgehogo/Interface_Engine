#include "baseException.hpp"

namespace ui {
	BaseException::BaseException(std::string description) : description(std::move(description)) {
	}
	
	const char* BaseException::what() const noexcept {
		return description.c_str();
	}
	
	std::string BaseException::getDescription() {
		return description;
	}
}