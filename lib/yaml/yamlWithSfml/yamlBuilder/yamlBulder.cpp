#include "yamlBuilder.hpp"

namespace ui {
	std::string removeNamespace(std::string typeName, std::string nameSpace) {
		std::string nameSpaceName = std::string("::") + nameSpace;
		if(typeName.size() >= nameSpaceName.size() && typeName.substr(0, nameSpaceName.size()) == nameSpaceName) {
			return typeName.substr(nameSpaceName.size());
		}
		return typeName;
	}
}