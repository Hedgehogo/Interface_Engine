#pragma once

#include <regex>
#include "../shared/IShared.hpp"
#include "BufferException/BufferException.hpp"

namespace ie {
	std::vector<std::string> split_by_delimiter(const std::string& str, char delimiter);
	
	std::vector<std::string> split_string(const std::string& str, const std::function<bool(char, size_t)>& divider);
	
	PIShared get_vector_axis(const PIShared& vector, const std::string& name);
	
	class Buffer {
	protected:
		static std::map<std::string, PIShared>& get_level();
		
		template<typename T>
		static void insert(const std::string& name, const YAML::Node& node);
		
		static PIShared get_variable(const PIShared& var, std::vector<std::string>& names);
	
	public:
		using GetOption = std::function<PIShared(const PIShared&, const std::string&)>;
		
		Buffer() = default;
		
		static bool exist_at_level(const std::string& name);
		
		static bool exist(const YAML::Node& node);
		
		static void raise_nesting_level();
		
		static void lower_nesting_level();
		
		static void read_level(std::function<void()> function);
		
		template<typename T, typename... A>
		static void emplace(const std::string& name, A&& ... args);
		
		template<typename T>
		static void insert(const YAML::Node& node);
		
		template<typename T>
		static std::shared_ptr<T> at(const std::string& full_name);
		
		template<typename T>
		static std::shared_ptr<T> get(const YAML::Node& node, bool create_if_not_exist = true);
		
	protected:
		static std::vector<std::map<std::string, PIShared> > objects_levels_;
		static std::vector<std::pair<std::regex, GetOption> > options_;
	};
	
	template<typename T>
	std::shared_ptr<T> at_s_value(std::string name);
	
	template<typename T, typename... A>
	void emplace_s_value(const std::string& name, A&& ... args);
}

#include "Buffer.inl"