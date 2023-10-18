#pragma once

#include "../../yaml.hpp"

namespace ie {
	std::string remove_namespace(std::string name, std::string name_space);
	
	namespace detail {
		class IYamlBuilder {
		public:
			using TypeNameDeformer = std::function<std::string(std::string)>;
		
			static void set_type_name_deformer(const TypeNameDeformer& type_name_deform);
			
			virtual bool build(const YAML::Node& node, void*& object) const = 0;
			
			virtual IYamlBuilder* get_builder(const std::string& type) = 0;
			
			virtual bool determine(const YAML::Node& node, std::string& type) = 0;
			
			virtual bool is_exists();
			
			explicit operator bool();
			
			virtual ~IYamlBuilder() = default;
		
		public:
			static TypeNameDeformer type_name_deform;
		};
	}
	
	void set_type_name_deformer(const detail::IYamlBuilder::TypeNameDeformer& type_name_deform);
}