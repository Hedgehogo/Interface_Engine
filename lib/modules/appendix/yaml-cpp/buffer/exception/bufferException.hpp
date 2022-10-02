#pragma once
#include <string>
#include <exception>

namespace ui {
	class BufferVariableNotFoundException : public std::exception {
	protected:
		std::string str;
	
	public:
		BufferVariableNotFoundException(std::string name, const std::string& type);
		
		const char* what() const noexcept override;
	};
	
	class BufferNonExistentNestingLevelException : public std::exception {
	protected:
		std::string str;
	
	public:
		BufferNonExistentNestingLevelException(std::string name, long long level);
		
		const char* what() const noexcept override;
	};
	
	class BufferRecursionDepthViolationException : public std::exception {
	protected:
		std::string str;
	
	public:
		BufferRecursionDepthViolationException(const std::string& type);
		
		const char* what() const noexcept override;
	};
}
