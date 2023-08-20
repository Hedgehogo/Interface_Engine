#include "notExistAnimationVariable.hpp"

namespace ui {
	NotExistAnimationVariable::NotExistAnimationVariable(std::string name) : BaseException(std::string{"variable '"} + name + std::string{"' does not exist"}) {
	}
}