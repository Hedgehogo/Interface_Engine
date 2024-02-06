#pragma once

#include <IEML/node.hpp>
#include <SFML/Graphics.hpp>

namespace ie {
	class LoadShader {
	public:
		static orl::Option<LoadShader> decode(ieml::Node const& node);
		
		void load(sf::Shader& shader);
	
	private:
		LoadShader(std::string vert, std::string frag);
		
		std::string vert_;
		std::string frag_;
	};
}
