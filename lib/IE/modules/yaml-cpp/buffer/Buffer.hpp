#pragma once

#include <regex>
#include "../shared/IShared.hpp"
#include "../yaml-builder/IYamlBuilder/YamlBuilder/YamlBuilder.hpp"
#include "BufferException/BufferException.hpp"

namespace ie {
	std::vector<std::string> splitByDelimiter(const std::string& str, char delimiter);
	
	std::vector<std::string> splitString(const std::string& str, const std::function<bool(char, size_t)>& divider);
	
	PIShared getVectorAxis(const PIShared& vector, const std::string& name);
	
	class Buffer {
	protected:
		static std::map<std::string, PIShared>& getLevel();
		
		template<typename T>
		static void insert(const std::string& name, const YAML::Node& node);
		
		static PIShared getVariable(const PIShared& var, std::vector<std::string>& names);
	
	public:
		using GetOption = std::function<PIShared(const PIShared&, const std::string&)>;
		
		Buffer() = default;
		
		static bool existAtLevel(const std::string& name);
		
		static bool exist(const YAML::Node& node);
		
		static void raiseNestingLevel();
		
		static void lowerNestingLevel();
		
		static void readLevel(std::function<void()> function);
		
		template<typename T, typename... A>
		static void emplace(const std::string& name, A&& ... args);
		
		template<typename T>
		static void insert(const YAML::Node& node);
		
		template<typename T>
		static std::shared_ptr<T> at(const std::string& fullName);
		
		template<typename T>
		static std::shared_ptr<T> get(const YAML::Node& node, bool createIfNotExist = true);
		
	protected:
		static std::vector<std::map<std::string, PIShared>> objectsLevels;
		static std::vector<std::pair<std::regex, GetOption>> options;
	};
	
	template<typename T>
	std::shared_ptr<T> atSValue(std::string name);
	
	template<typename T, typename... A>
	void emplaceSValue(const std::string& name, A&& ... args);
}

#include "Buffer.inl"