#pragma once

#include "IE/modules/exception/baseException.hpp"

namespace ie {
	class NonexistentAnimationVariableException : public BaseException {
	public:
		NonexistentAnimationVariableException(std::string name);
	};
}