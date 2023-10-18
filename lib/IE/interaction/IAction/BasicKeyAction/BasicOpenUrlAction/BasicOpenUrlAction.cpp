#include "BasicOpenUrlAction.hpp"

namespace ie {
	bool determine_url(const YAML::Node& node) {
		if(node.IsScalar()) {
			std::string url{node.as<std::string>()};
			return url.substr(0, 7) == "file://" || url.substr(0, 7) == "http://" || url.substr(0, 8) == "https://";
		}
		return false;
	}
}