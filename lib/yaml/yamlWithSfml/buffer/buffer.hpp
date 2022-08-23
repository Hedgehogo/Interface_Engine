#pragma once
#include <any>
#include "../../../ui/with/iWith.hpp"
#include "exception/bufferException.hpp"

namespace ui {
	template <typename Type, typename Return = Type>
	using if_pointer = std::enable_if_t<std::is_pointer_v<Type>, Return>;
	
	template <typename Type, typename Return = Type>
	using if_no_pointer = std::enable_if_t<!std::is_pointer_v<Type>, Return>;
	
	template <bool Condition, typename TrueType, typename FalseType>
	struct select_if_ { using type = TrueType; };
	template <typename TrueType, typename FalseType>
	struct select_if_<false, TrueType, FalseType> { using type = FalseType; };
	
	template <bool Condition, typename TrueType, typename FalseType>
	using select_if = typename select_if_<Condition, TrueType, FalseType>::type;
}

namespace ui {
	class Buffer {
	protected:
		static std::map<std::string, std::shared_ptr<IWith>> objects;
	
	public:
		Buffer() = default;
		
		static bool existObject(const std::string& name);
		
		template<typename T, typename... A>
		static void addObject(const std::string name, A&&... args);
		
		template<typename T>
		static void addObject(const std::string& name, const YAML::Node &node);
		
		template<typename T>
		static void addObject(const YAML::Node &node);
		
		template<typename T>
		static std::shared_ptr<T> getObject(const std::string& name);
		
		template<typename T>
		static std::shared_ptr<T> getObject(const YAML::Node &node);
	};
	
	template<typename T>
	std::shared_ptr<T> getRef(std::string name);
	
	template<typename T, typename... A>
	void add(const std::string name, A&&... args);
}

#include "buffer.inl"