#include "LoadShader.hpp"

namespace ie {
	LoadShader::LoadShader(std::string vert, std::string frag) : vert_(std::move(vert)), frag_(std::move(frag)) {
	}
	
	orl::Option<LoadShader> LoadShader::decode(const ieml::Node& node) {
		auto& clear_node{node.get_clear()};
		auto vert{clear_node.at("vert")};
		auto frag{clear_node.at("frag")};
		if(vert) {
			auto& vert_str{vert.ok().get_string().except()};
			if(frag) {
				auto& frag_str{frag.ok().get_string().except()};
				return LoadShader{vert_str, frag_str};
			}
			return LoadShader{vert_str, std::string{}};
		}
		auto& frag_str{frag.except().get_string().except()};
		return LoadShader{std::string{}, frag_str};
	}
	
	void LoadShader::load(sf::Shader& shader) {
		if(frag_.empty()) {
			shader.loadFromFile(vert_, sf::Shader::Vertex);
			return;
		}
		if(vert_.empty()) {
			shader.loadFromFile(frag_, sf::Shader::Fragment);
			return;
		}
		shader.loadFromFile(vert_, frag_);
	}
}