#pragma once

#include <string>
#include <exception>

namespace ie {
	class BaseException : public std::exception {
	public:
		BaseException(std::string description);
		
		const char* what() const noexcept override;
		
		std::string get_description();
	
	protected:
		std::string description;
	};
}
