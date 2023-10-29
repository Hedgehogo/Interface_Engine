#pragma once

#include "IE/modules/exception/BaseException.hpp"

namespace ie {
	class NonexistentAnimationVariableException : public BaseException {
	public:
		NonexistentAnimationVariableException(std::string name);
		
		std::string get_description() const override;
	
	protected:
		std::string name_;
	};
}