#pragma once

#include "../IYamlBuilder.hpp"

namespace ie::detail {
	class EmptyYamlBuilder : public IYamlBuilder {
	public:
		bool build(const YAML::Node&, void*&) const override;
		
		IYamlBuilder* get_builder(const std::string&) override;
		
		bool determine(const YAML::Node&, std::string&) override;
		
		bool is_exists() override;
	
	public:
		static EmptyYamlBuilder builder;
	};
}
