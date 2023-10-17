#pragma once

#include "../IYamlBuilder.hpp"

namespace ie::detail {
	class BaseYamlBuilder : public IYamlBuilder {
	public:
		virtual void addType(IYamlBuilder* builder) = 0;
	};
	
	extern std::unordered_map<std::string, BaseYamlBuilder*> yamlBuilders;
}
