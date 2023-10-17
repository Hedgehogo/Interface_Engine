#pragma once

#include "IE/modules/exception/BaseException.hpp"

namespace ie {
	class NonexistentAnimationVariableException : public BaseException {
	public:
		NonexistentAnimationVariableException(std::string name);
	};
}