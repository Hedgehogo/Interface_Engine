#include "ieml-basic.hpp"
#include <localisation/system.hpp>

namespace ieml {
	auto Decode<char, ie::ParseString>::decode(ieml::Node const& node) -> orl::Option<ie::ParseString> {
		auto& clear_node{node.get_clear()};
		for(auto map: clear_node.get_map_view().ok_or_none()) {
			for(auto& key: map.at("key").ok_or_none()) {
				for(auto& directory: node.at("directory").ok_or_none()) {
					loc::system.load_from_directory(directory.get_string().except());
				}
				for(auto& default_language: node.at("default-language").ok_or_none()) {
					loc::system.set_default_language(default_language.get_string().except());
				}
				for(auto& language: node.at("language").ok_or_none()) {
					loc::system.set_now_language(language.get_string().except());
				}
				return {{loc::system.get_text(key.get_string().except())}};
			}
		}
		return {{clear_node.get_string().except()}};
	}
	
	auto Decode<char, std::filesystem::path>::decode(ieml::Node const& node) -> orl::Option<std::filesystem::path>{
		return std::filesystem::path{
			node.as<ie::ParseString>().except().str
		};
	}
	
}
