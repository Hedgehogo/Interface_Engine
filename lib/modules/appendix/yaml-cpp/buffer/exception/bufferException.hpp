#pragma once

#include "../../exception/baseYamlException.hpp"

namespace ui {
	class BufferNonExistentNestingLevelException : public BaseYamlException {
	protected:
		std::string name;
		std::size_t level;
	
	public:
		BufferNonExistentNestingLevelException(YAML::Mark mark, const std::string& name, std::size_t level);
		
		std::string getName() const;
		
		std::size_t getLevel() const;
	};
	
	class BufferVariableNotFoundException : public BaseException {
	protected:
		std::string name;
		std::string type;
	
	public:
		BufferVariableNotFoundException(const std::string& name, const std::string& type);
		
		std::string getName() const;
		
		std::string getType() const;
	};
	
	class YamlBufferVariableNotFoundException : public BaseYamlException {
	protected:
		BufferVariableNotFoundException exception;
	
	public:
		YamlBufferVariableNotFoundException(YAML::Mark mark, const BufferVariableNotFoundException& exception);
		
		BufferVariableNotFoundException getException() const;
		
		std::string getName() const;
		
		std::string getType() const;
	};
}
