#pragma once

#include "../box.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"
#include "../../../../layout/background/layoutWithBackground.hpp"

namespace ui {
	class BoxWithBackground : public Box, public LayoutWithBackground, public LayoutWithObject {
	protected:
		sf::Vector2f offset;
	
	public:
		BoxWithBackground(IScalable* object, IUninteractive* background, sf::Vector2f offset = {0, 0}, sf::Vector2f minSize = {0, 0});
		
		void init(InitInfo initInfo) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxWithBackground* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	
	template<>
	struct DecodePointer<BoxWithBackground> {
		static bool decodePointer(const YAML::Node& node, BoxWithBackground*& boxWithBackground);
	};
}