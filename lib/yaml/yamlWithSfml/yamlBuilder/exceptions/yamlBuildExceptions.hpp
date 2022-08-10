#pragma once
#include <string>
#include <exception>
#include <utility>

namespace ui {
	class AbstractTypeYamlException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	
	class NonexistentTypeYamlException : public std::exception {
	protected:
		std::string str;
		
	public:
		NonexistentTypeYamlException(std::string type);
		
		virtual const char* what() const throw();
	};
}
