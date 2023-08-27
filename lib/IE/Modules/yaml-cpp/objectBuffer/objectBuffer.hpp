#pragma once

#include "../yaml.hpp"

namespace ui {
	class IComponent;
	
	class ObjectBuffer {
	public:
		static void add(const std::string& name, const YAML::Node& node);
		
		static const YAML::Node& get(std::string name);
		
		static bool has(const std::string& name);
	
	protected:
		static std::map<std::string, const YAML::Node> nodes;
	};
}