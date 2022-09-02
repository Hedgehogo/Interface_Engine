#pragma once
#include <any>
#include <iostream>
#include <functional>
#include <regex>
#include "../with/list/general/withList.hpp"
#include "../with/vector/general/withVector2.hpp"
#include "exception/bufferException.hpp"

namespace ui {
	template <bool Condition, typename TrueType, typename FalseType>
	struct select_if_ { using type = TrueType; };
	template <typename TrueType, typename FalseType>
	struct select_if_<false, TrueType, FalseType> { using type = FalseType; };
	
	template <bool Condition, typename TrueType, typename FalseType>
	using select_if = typename select_if_<Condition, TrueType, FalseType>::type;
}

namespace ui {
	std::vector<std::string> splitByDelimiter(const std::string& str, char delimiter);
	
	std::shared_ptr<IWith> getVectorAxis(const std::shared_ptr<IWith>& vector, const std::string& name);
	
	class Buffer {
	public:
		typedef std::function<std::shared_ptr<IWith>(const std::shared_ptr<IWith>&, const std::string&)> getOption;
	
	protected:
		static std::vector<std::map<std::string, std::shared_ptr<IWith>>> objectsLevels;
		static std::vector<std::pair<std::regex, getOption>> options;
		
		static std::map<std::string, std::shared_ptr<IWith>>& getLevel();
		
		template<typename T>
		static void insert(const std::string& name, const YAML::Node &node);
		
		static std::shared_ptr<IWith> getVariable(const std::shared_ptr<IWith>& var, std::vector<std::string>& names);
		
	public:
		Buffer() = default;
		
		static bool existAtLevel(const std::string& name);
		
		static bool exist(const YAML::Node &node);
		
		static void raiseNestingLevel();
		
		static void lowerNestingLevel();
		
		static void readLevel(std::function<void()> function);
		
		template<typename T, typename... A>
		static void emplace(const std::string& name, A&&... args);
		
		template<typename T>
		static void insert(const YAML::Node &node);
		
		template<typename T>
		static std::shared_ptr<T> at(const std::string& fullName);
		
		template<typename T>
		static std::shared_ptr<T> get(const YAML::Node &node, bool createIfNotExist = true);
	};
	
	template<typename T>
	std::shared_ptr<T> atYaml(std::string name);
	
	template<typename T, typename... A>
	void insertYaml(const std::string& name, A&&... args);
}

#include "buffer.inl"