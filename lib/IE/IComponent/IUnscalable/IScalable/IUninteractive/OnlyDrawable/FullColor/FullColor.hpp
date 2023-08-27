#pragma once

#include "../OnlyDrawable.hpp"
#include "../../../../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class FullColor : public OnlyDrawable {
	public:
		struct Make : public IUninteractive::Make {
			sf::Color color;
			sf::Vector2f normalSize = {};
			
			Make(sf::Color color, sf::Vector2f normalSize = {0, 0});
			
			FullColor* make(InitInfo initInfo) override;
		};
		
		FullColor(Make&& make, InitInfo initInfo);
		
		explicit FullColor(sf::Color color, sf::Vector2f normalSize = {0, 0});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		FullColor* copy() override;
	
	protected:
		sf::RectangleShape rectangle;
		sf::Vector2f normalSize;
	};
	
	template<>
	struct DecodePointer<FullColor> {
		static bool decodePointer(const YAML::Node& node, FullColor*& fullColor);
	};
	
	template<>
	bool determine<FullColor>(const YAML::Node& node);
}

