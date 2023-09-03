#pragma once

#include "../empty/emptyYamlBuilder.hpp"

namespace ie::detail {
	class FuncYamlBuilder : public IYamlBuilder {
	public:
		template<typename Type>
		using BuildFunc = std::function<bool(const YAML::Node&, Type*&)>;
		
		using VoidBuildFunc = std::function<bool(const YAML::Node&, void*&)>;
		
		FuncYamlBuilder(VoidBuildFunc function, std::vector<std::string> names = {});
		
		bool build(const YAML::Node& node, void*& object) const override;
		
		IYamlBuilder* getBuilder(const std::string& type) override;
		
		bool determine(const YAML::Node&, std::string&) override;
		
		template<typename Type>
		static FuncYamlBuilder& addBuilder(BuildFunc<Type> function, std::vector<std::string> aliases = {});
		
	protected:
		static std::vector<FuncYamlBuilder> builders;
		
		std::vector<std::string> names;
		VoidBuildFunc function;
	};
}

#include "funcYamlBuilder.inl"