#pragma once

#include "../../exception/BaseYamlException.hpp"

namespace ie {
	class BufferNonExistentNestingLevelException : public BaseYamlException {
	public:
		BufferNonExistentNestingLevelException(YAML::Mark mark, const std::string& name, std::size_t level);
		
		std::string get_name() const;
		
		std::size_t get_level() const;
	
	protected:
		std::string name;
		std::size_t level;
	};
	
	class BufferVariableNotFoundException : public BaseException {
	public:
		BufferVariableNotFoundException(const std::string& name, const std::string& type);
		
		std::string get_name() const;
		
		std::string get_type() const;
	
	protected:
		std::string name;
		std::string type;
	};
	
	class YamlBufferVariableNotFoundException : public BaseYamlException {
	public:
		YamlBufferVariableNotFoundException(YAML::Mark mark, const BufferVariableNotFoundException& exception);
		
		BufferVariableNotFoundException get_exception() const;
		
		std::string get_name() const;
		
		std::string get_type() const;
	
	protected:
		BufferVariableNotFoundException exception;
	};
}
