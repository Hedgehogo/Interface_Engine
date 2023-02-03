#pragma once

#include "../../../modules/appendix/exception/baseException.hpp"

namespace ui {
	class NotExistAnimationVariable : public BaseException{
	public:
		NotExistAnimationVariable(std::string name);
	};
}