#pragma once

#include "../onlyDrawable.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class FullColor : public OnlyDrawable {
	protected:
		sf::RectangleShape rectangle;
		sf::Vector2f normalSize;
	
	public:
		explicit FullColor(sf::Color color, sf::Vector2f normalSize = {0, 0});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		FullColor* copy() override;
	};
	
	
	template<>
	struct DecodePointer<FullColor> {
		static bool decodePointer(const YAML::Node& node, FullColor*& fullColor);
	};
	
	template<>
	bool determine<FullColor>(const YAML::Node& node);
}

