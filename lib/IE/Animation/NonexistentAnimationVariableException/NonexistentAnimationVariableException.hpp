#pragma once

#include "../../Modules/exception/baseException.hpp"

namespace ui {
	class NonexistentAnimationVariableException : public BaseException {
	public:
		NonexistentAnimationVariableException(std::string name);
	};
}