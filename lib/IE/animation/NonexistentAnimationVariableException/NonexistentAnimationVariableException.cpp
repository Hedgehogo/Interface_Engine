#include "NonexistentAnimationVariableException.hpp"

namespace ie {
	NonexistentAnimationVariableException::NonexistentAnimationVariableException(std::string name) :
		name_(std::move(name)) {
	}
	
	std::string NonexistentAnimationVariableException::get_description() const {
		return std::string{"Variable '"} + name_ + std::string{"' does not exist."};
	}
}