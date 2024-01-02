#include "BasicOpenUrlAction.hpp"
#include "IE/ieml/determine/determine.hpp"

namespace ie {
	bool determine_url(ieml::Node const& node) {
		if(auto url_result{node.get_string()}) {
			std::string_view url{url_result.ok()};
			return
				url.substr(0, 7) == "file://" ||
				url.substr(0, 7) == "http://" ||
				url.substr(0, 8) == "https://";
		}
		return false;
	}
}