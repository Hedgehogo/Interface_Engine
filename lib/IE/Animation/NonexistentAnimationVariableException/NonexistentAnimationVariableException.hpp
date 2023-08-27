#pragma once

#include "../../Modules/exception/baseException.hpp"

namespace ie {
	class NonexistentAnimationVariableException : public BaseException {
	public:
		NonexistentAnimationVariableException(std::string name);
	};
}