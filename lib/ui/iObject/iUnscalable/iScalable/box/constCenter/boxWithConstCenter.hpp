#pragma once

#include "../box.hpp"
#include "ui/iObject/layout/twoObjects/layoutWithTwoObjects.hpp"

namespace ui {
	class BoxWithConstCenter : public Box, public LayoutWithTwoObjects{
	protected:
		sf::Vector2f constSize;
		
	public:
		BoxWithConstCenter(IScalable* constObject, IScalable* background, const sf::Vector2f& constSize, const sf::Vector2f& minSize = {});
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxWithConstCenter* copy() override;
	};
	
	template<>
	struct DecodePointer<BoxWithConstCenter> {
		static bool decodePointer(const YAML::Node& node, BoxWithConstCenter*& boxWithConstCenter);
	};
}
