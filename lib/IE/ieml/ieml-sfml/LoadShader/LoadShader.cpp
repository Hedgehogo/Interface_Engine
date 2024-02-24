#include "LoadShader.hpp"

namespace ie {
	LoadShader::LoadShader(std::string vert, std::string frag) : vert_(std::move(vert)), frag_(std::move(frag)) {
	}
	
	orl::Option<LoadShader> LoadShader::decode(const ieml::Node& node) {
		auto map{node.get_map_view().except()};
		auto frag_str_result{map.at("frag").map_ok([](auto& frag) -> auto& {
			return frag.get_string().except();
		})};
		return map.at("vert").map_ok([&](auto& vert) {
			auto& vert_str{vert.get_string().except()};
			return frag_str_result.map_ok([&](auto& frag_str) {
				return LoadShader{vert_str, frag_str};
			}).ok_or_else([&] {
				return LoadShader{vert_str, std::string{}};
			});
		}).ok_or_else([&] {
			auto& frag_str{frag_str_result.except()};
			return LoadShader{std::string{}, frag_str};
		});
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