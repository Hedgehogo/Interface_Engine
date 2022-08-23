#pragma once
#include <string>
#include <exception>

namespace ui {
	class BufferBadCastException : public std::exception {
	protected:
		std::string str;
	
	public:
		BufferBadCastException(std::string name, const std::type_info& type);
		
		virtual const char* what() const throw();
	};
}
