#include "NonexistentAnimationVariableException.hpp"

namespace ui {
	NonexistentAnimationVariableException::NonexistentAnimationVariableException(std::string name) : BaseException(std::string{"variable '"} + name + std::string{"' does not exist"}) {
	}
}