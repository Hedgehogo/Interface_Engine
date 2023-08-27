#pragma once

#include "../../exception/baseYamlException.hpp"

namespace ie {
	class BufferNonExistentNestingLevelException : public BaseYamlException {
	public:
		BufferNonExistentNestingLevelException(YAML::Mark mark, const std::string& name, std::size_t level);
		
		std::string getName() const;
		
		std::size_t getLevel() const;
	
	protected:
		std::string name;
		std::size_t level;
	};
	
	class BufferVariableNotFoundException : public BaseException {
	public:
		BufferVariableNotFoundException(const std::string& name, const std::string& type);
		
		std::string getName() const;
		
		std::string getType() const;
	
	protected:
		std::string name;
		std::string type;
	};
	
	class YamlBufferVariableNotFoundException : public BaseYamlException {
	public:
		YamlBufferVariableNotFoundException(YAML::Mark mark, const BufferVariableNotFoundException& exception);
		
		BufferVariableNotFoundException getException() const;
		
		std::string getName() const;
		
		std::string getType() const;
	
	protected:
		BufferVariableNotFoundException exception;
	};
}
