#pragma once

#include "../../exception/BaseYamlException.hpp"

namespace ie {
	class BufferNonExistentNestingLevelException : public BaseYamlException {
	public:
		BufferNonExistentNestingLevelException(YAML::Mark mark, const std::string& name, size_t level);
		
		std::string get_description() const override;
		
		std::string get_name() const;
		
		size_t get_level() const;
	
	protected:
		std::string name_;
		size_t level_;
	};
	
	class BufferVariableNotFoundException : public BaseException {
	public:
		BufferVariableNotFoundException(const std::string& name, const std::string& type);
		
		std::string get_description() const override;
		
		std::string get_name() const;
		
		std::string get_type() const;
	
	protected:
		std::string name_;
		std::string type_;
	};
	
	class YamlBufferVariableNotFoundException : public BaseYamlException {
	public:
		YamlBufferVariableNotFoundException(YAML::Mark mark, const BufferVariableNotFoundException& exception);
		
		std::string get_description() const override;
		
		const BufferVariableNotFoundException& get_exception() const;
		
		std::string get_name() const;
		
		std::string get_type() const;
	
	protected:
		BufferVariableNotFoundException exception_;
	};
}
