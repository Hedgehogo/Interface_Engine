#pragma once
#include "../yaml.hpp"

namespace ui {
	template <typename T>
	using to_auto = std::remove_const_t<std::remove_reference_t<T>>;
	
	class IWith {
	public:
		virtual ~IWith() = default;
		
		static IWith *createFromYaml(const YAML::Node &node) { return nullptr; };
	};
}
