#include "IYamlBuilder.hpp"

namespace ie {
	std::string removeNamespace(std::string name, std::string nameSpace) {
		std::string nameSpaceName = nameSpace + std::string("::");
		if(name.size() >= nameSpaceName.size() && name.substr(0, nameSpaceName.size()) == nameSpaceName) {
			return name.substr(nameSpaceName.size());
		}
		return name;
	}
	
	namespace detail {
		IYamlBuilder::TypeNameDeformer IYamlBuilder::typeNameDeform = [](std::string name) -> std::string {
			return removeNamespace(std::move(name), "ui");
		};
		
		void IYamlBuilder::setTypeNameDeformer(const TypeNameDeformer& typeNameDeform) {
			IYamlBuilder::typeNameDeform = typeNameDeform;
		}
		
		bool IYamlBuilder::isExists() {
			return true;
		}
		
		IYamlBuilder::operator bool() {
			return isExists();
		}
	}
	
	void setTypeNameDeformer(const detail::IYamlBuilder::TypeNameDeformer& typeNameDeform) {
		detail::IYamlBuilder::setTypeNameDeformer(typeNameDeform);
	}
}