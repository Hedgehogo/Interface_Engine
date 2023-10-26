#include "BaseException.hpp"

namespace ie {
	BaseException::BaseException(std::string description) : description_(std::move(description)) {
	}
	
	const char* BaseException::what() const noexcept {
		return description_.c_str();
	}
	
	std::string BaseException::get_description() {
		return description_;
	}
}