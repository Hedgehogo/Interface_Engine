#pragma once

#include "ui/iObject/iUnscalable/iScalable/box/box.hpp"
#include "../../../../layout/objectsArray/layoutWithObjectsArray.hpp"
#include "ui/iObject/iUnscalable/iScalable/interactive/simple/interactiveSimple.hpp"
#include "ui/enums/keyHandler/keyHandler.hpp"

namespace ui {
	class BoxSwitcherTabs : public Box, public LayoutWithObjectsArray, public Interactive_Simple {
	public:
		BoxSwitcherTabs(std::vector<IScalable*> objects, PSint value, Key key, bool isHorizontal, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		int getTab(sf::Vector2f position);
		
		BoxSwitcherTabs* copy() override;
	
	protected:
		bool isHorizontal;
		PSint value;
	};
	
	template<>
	struct DecodePointer<BoxSwitcherTabs> {
		static bool decodePointer(const YAML::Node& node, BoxSwitcherTabs*& switcherTabs);
	};
}
