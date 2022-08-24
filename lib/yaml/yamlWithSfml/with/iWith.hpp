#pragma once
#include "../yaml.hpp"

namespace ui {
	class IWith {
	public:
		virtual ~IWith() = default;
		
		static IWith *createFromYaml(const YAML::Node &node) { return nullptr; };
	};
}
