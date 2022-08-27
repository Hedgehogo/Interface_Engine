#pragma once
#include <any>
#include <iostream>
#include <functional>
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
	
	class Buffer {
	protected:
		static std::vector<std::map<std::string, std::shared_ptr<IWith>>> objectsLevels;
		
		static std::map<std::string, std::shared_ptr<IWith>>& getObjects();
		
		template<typename T>
		static void addObject(const std::string& name, const YAML::Node &node);
		
		static std::shared_ptr<IWith> getAxis(const std::shared_ptr<IWith>& vector, const std::string& name);
		
		static std::shared_ptr<IWith> getVariable(const std::shared_ptr<IWith>& var, std::vector<std::string>& names);
	
	public:
		Buffer() = default;
		
		static bool existObject(const std::string& name);
		
		static bool existObject(const YAML::Node &node);
		
		static void raiseNestingLevel();
		
		static void lowerNestingLevel();
		
		static void readLevel(std::function<void()> function);
		
		template<typename T, typename... A>
		static void addObject(const std::string& name, A&&... args);
		
		template<typename T>
		static void addObject(const YAML::Node &node);
		
		template<typename T>
		static std::shared_ptr<T> getObject(const std::string& name);
		
		template<typename T>
		static std::shared_ptr<T> getObject(const YAML::Node &node, bool createIfNotExist = true);
	};
	
	template<typename T>
	std::shared_ptr<T> getRef(std::string name);
	
	template<typename T, typename... A>
	void add(const std::string& name, A&&... args);
}

#include "buffer.inl"