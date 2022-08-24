#pragma once
#include <string>
#include <exception>
#include <utility>

namespace ui {
	class AbstractTypeYamlException : public std::exception {
	public:
		const char* what() const noexcept override;
	};
	
	class NonexistentTypeYamlException : public std::exception {
	protected:
		std::string str;
		
	public:
		NonexistentTypeYamlException(std::string type);
		
		const char* what() const noexcept override;
	};
}
