#pragma once

#include <string>
#include <exception>

namespace ui {
	class BaseException : public std::exception {
	protected:
		std::string description;
	
	public:
		BaseException(std::string description);
		
		const char* what() const noexcept override;
		
		std::string getDescription();
	};
}
