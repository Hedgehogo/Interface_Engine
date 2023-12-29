#pragma once

#include "../../../object-buffer/ObjectBuffer.hpp"
#include "../../exception/exception.hpp"
#include "../FuncYamlBuilder/FuncYamlBuilder.hpp"
#include "../BaseYamlBuilder/BaseYamlBuilder.hpp"

namespace ie {
	const sf::Color null_color{255, 255, 255, 0};
	
	std::string remove_namespace(std::string type_name, std::string name_space);
	
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
		
		detail::IYamlBuilder* get_builder(const std::string& type) override;
		
		bool determine(const YAML::Node& node, std::string& type) override;
		
		bool build(const YAML::Node& node, const std::string& type, void*& object);
	
	public:
		void add_type(IYamlBuilder* builder) override;
	
	public:
		template<typename Derived>
		static is_derived<Derived, void> add_type();
		
		static void add_type(typename detail::FuncYamlBuilder::BuildFunc<Type> function, std::vector<std::string> aliases = {});
		
		static void add_alias(const std::string& alias);
		
		static void add_aliases(std::vector<std::string> aliases);
		
		static void add_determine(const DetermineType& function);
		
		static void add_determine(const SimpleDetermineType& function = ie::determine<Type>);
		
		static void determine_type(const YAML::Node& node, std::string& type);
		
		static bool build(const YAML::Node& node, const std::string& type, Type*& object);
		
	public:
		static YamlBuilder builder;
	
	protected:
		static std::vector<std::string> names_;
		static std::vector<detail::IYamlBuilder*> types_;
		static std::vector<DetermineType> determiners_;
	};
	
	template<typename T>
	void add_to_yaml_builders();
}

#include "YamlBuilder.inl"
