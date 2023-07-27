#pragma once

#include "ui/iObject/iUnscalable/iScalable/box/box.hpp"
#include "ui/iObject/layout/twoObjects/layoutWithTwoObjects.hpp"

namespace ui {
	class BoxSwitcher : public Box, public LayoutWithTwoObjects, public IDrawable {
	protected:
		DrawManager firstDrawManager;
		DrawManager secondDrawManager;
		PSbool value;
		
	public:
		BoxSwitcher(IScalable* firstObject, IScalable* secondObject, PSbool value, const sf::Vector2f& minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void draw() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxSwitcher* copy() override;
	};
	
	template<>
	struct DecodePointer<BoxSwitcher> {
		static bool decodePointer(const YAML::Node& node, BoxSwitcher*& boxSwitcher);
	};
}
