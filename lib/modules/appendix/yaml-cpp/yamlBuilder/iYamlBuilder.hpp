#pragma once
#include "../yaml.hpp"

namespace ui {
	std::string removeNamespace(std::string name, std::string nameSpace);
	
	namespace detail {
		class IYamlBuilder {
		public:
			using TypeNameDeformer = std::function<std::string(std::string)>;
		
		public:
			static TypeNameDeformer typeNameDeform;
		
		public:
			static void setTypeNameDeformer(const TypeNameDeformer &typeNameDeform);
			
			virtual bool build(const YAML::Node &node, void *&object) const = 0;
			
			virtual IYamlBuilder *getBuilder(const std::string &type) = 0;
			
			virtual bool determine(const YAML::Node& node, std::string &type) = 0;
			
			virtual bool isExists();
			
			explicit operator bool();
			
		};
	}
	
	void setTypeNameDeformer(const detail::IYamlBuilder::TypeNameDeformer &typeNameDeform);
}
