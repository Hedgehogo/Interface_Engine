#include "BasicOpenUrlAction.hpp"
#include "IE/ieml/determine/determine.hpp"

namespace ie {
	auto determine_url(ieml::Node const& node) -> bool {
		for(auto& url_str: node.get_string().ok_or_none()) {
			auto url{std::string_view{url_str}};
			return
				url.substr(0, 7) == std::string_view{"file://"} ||
				url.substr(0, 7) == std::string_view{"http://"} ||
				url.substr(0, 8) == std::string_view{"https://"};
		}
		return false;
	}
}