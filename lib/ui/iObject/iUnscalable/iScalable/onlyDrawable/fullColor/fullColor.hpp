#pragma once
#include "../onlyDrawable.hpp"
#include "../../../../../../yaml/yamlWithSfml/yamlBuilder/yamlBuilder.hpp"

namespace ui {
    class FullColor : public OnlyDrawable {
	protected:
		sf::RectangleShape rectangle;
		sf::Vector2f normalSize;

	public:
		explicit FullColor(sf::Color color, sf::Vector2f normalSize = {0, 0});
	
		void draw() override;
	
		void resize(sf::Vector2f size, sf::Vector2f position) override;
	
		sf::Vector2f getAreaPosition() override;
	
		sf::Vector2f getAreaSize() override;
	
		sf::Vector2f getMinSize() override;
	
		sf::Vector2f getNormalSize() override;
	
		FullColor* copy() override;
	
		static FullColor* createFromYaml(const YAML::Node &node);
	};
}

