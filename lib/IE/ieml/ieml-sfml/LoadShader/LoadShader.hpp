#pragma once

#include <IEML/node.hpp>
#include <SFML/Graphics.hpp>

namespace ie {
	class LoadShader {
	public:
		static auto decode(ieml::Node const& node) -> orl::Option<LoadShader>;
		
		auto load(sf::Shader& shader) -> void;
	
	private:
		LoadShader(std::string vert, std::string frag);
		
		std::string vert_;
		std::string frag_;
	};
}
