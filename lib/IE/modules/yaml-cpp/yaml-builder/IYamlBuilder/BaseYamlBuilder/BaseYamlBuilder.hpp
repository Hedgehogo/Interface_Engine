#pragma once

#include "../IYamlBuilder.hpp"

namespace ie::detail {
	class BaseYamlBuilder : public IYamlBuilder {
	public:
		virtual void add_type(IYamlBuilder* builder) = 0;
	};
	
	extern std::unordered_map<std::string, BaseYamlBuilder*> yaml_builders;
}
