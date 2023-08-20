#pragma once

#include "../../../modules/appendix/exception/baseException.hpp"

namespace ui {
	class NonexistentAnimationVariableException : public BaseException {
	public:
		NonexistentAnimationVariableException(std::string name);
	};
}