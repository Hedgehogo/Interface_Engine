#include "yamlBuilder.hpp"

namespace ui {
	std::string removeNamespace(std::string typeName, std::string nameSpace) {
		std::string nameSpaceName = nameSpace + std::string("::");
		if(typeName.size() >= nameSpaceName.size() && typeName.substr(0, nameSpaceName.size()) == nameSpaceName) {
			return typeName.substr(nameSpaceName.size());
		}
		return typeName;
	}
}