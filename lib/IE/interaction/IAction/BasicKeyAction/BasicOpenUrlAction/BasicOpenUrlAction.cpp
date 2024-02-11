#include "BasicOpenUrlAction.hpp"
#include "IE/ieml/determine/determine.hpp"

namespace ie {
	bool determine_url(ieml::Node const& node) {
		for(auto& url_str: node.get_string().ok_or_none()) {
			std::string_view url{url_str};
			return
				url.substr(0, 7) == "file://" ||
				url.substr(0, 7) == "http://" ||
				url.substr(0, 8) == "https://";
		}
		return false;
	}
}