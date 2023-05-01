#pragma once

#include "ui/iObject/iUnscalable/iScalable/box/box.hpp"
#include "ui/iObject/layout/objectsArray/layoutWithObjectsArray.hpp"

namespace ui {
	class BoxWithTabs : public Box, public LayoutWithObjectsArray, public IDrawable{
	protected:
		PISint value;
		std::vector<DrawManager> drawManagers;
	
	public:
		BoxWithTabs(const std::vector<IScalable*>& objects, PISint  value, const sf::Vector2f& minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void draw() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxWithTabs* copy() override;
	};
	
	template<>
	struct DecodePointer<BoxWithTabs> {
		static bool decodePointer(const YAML::Node& node, BoxWithTabs*& boxWithTabs);
	};
}
