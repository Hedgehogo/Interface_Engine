#pragma once

#include "../yaml.hpp"

namespace ui
{
	class IObject;
	class ObjectBuffer
	{
	protected:
		static std::map<std::string, const YAML::Node> nodes;
		
	public:
		static void add(const std::string& name, const YAML::Node& node);

		static const YAML::Node& get(std::string name);

		static bool has(const std::string& name);
	};
}