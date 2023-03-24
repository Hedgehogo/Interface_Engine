#pragma once
#include "../iYamlBuilder.hpp"

namespace ui::detail {
	class EmptyYamlBuilder : public IYamlBuilder {
	public:
		static EmptyYamlBuilder builder;
	
	public:
		bool build(const YAML::Node &node, void *&object) const override;
		
		IYamlBuilder *getBuilder(const std::string &type) override;
		
		bool determine(const YAML::Node& node, std::string &type) override;
		
		bool isExists() override;
	};
}
