#pragma once

#include "../exception/yamlBuildExceptions.hpp"
#include "../../objectBuffer/objectBuffer.hpp"
#include "../function/funcYamlBuilder.hpp"
#include "../base/baseYamlBuilder.hpp"

namespace ui {
	const sf::Color nullColor{255, 255, 255, 0};
	
	std::string removeNamespace(std::string typeName, std::string nameSpace);
	
	template<typename T>
	bool determine(const YAML::Node& node);
	
	namespace detail {
		using DetermineTypeFunc = std::function<bool(const YAML::Node& node, std::string& type)>;
		using SimpleDetermineTypeFunc = std::function<bool(const YAML::Node& node)>;
	}
	
	template<typename Type>
	class YamlBuilder : public detail::BaseYamlBuilder {
	public:
		template<typename Derived, typename Return>
		using is_derived = std::enable_if_t<std::is_base_of_v<Type, Derived>, Return>;
		using DetermineType = detail::DetermineTypeFunc;
		using SimpleDetermineType = detail::SimpleDetermineTypeFunc;
		
	protected:
		bool build(const YAML::Node& node, void*& object) const override;
		
		detail::IYamlBuilder* getBuilder(const std::string& type) override;
		
		bool determine(const YAML::Node& node, std::string& type) override;
		
		bool build(const YAML::Node& node, const std::string& type, void*& object);
	
	public:
		void addType(IYamlBuilder* builder) override;
	
	public:
		template<typename Derived>
		static is_derived<Derived, void> addType();
		
		static void addType(typename detail::FuncYamlBuilder::BuildFunc<Type> function, std::vector<std::string> aliases = {});
		
		static void addAlias(const std::string& alias);
		
		static void addAliases(std::vector<std::string> aliases);
		
		static void addDetermine(const DetermineType& function);
		
		static void addDetermine(const SimpleDetermineType& function = ui::determine<Type>);
		
		static void determineType(const YAML::Node& node, std::string& type);
		
		static bool build(const YAML::Node& node, const std::string& type, Type*& object);
		
	public:
		static YamlBuilder builder;
	
	protected:
		static std::vector<std::string> names;
		static std::vector<detail::IYamlBuilder*> types;
		static std::vector<DetermineType> determiners;
	};
	
	template<typename T>
	void addToYamlBuilders();
}

#include "yamlBuilder.inl"
