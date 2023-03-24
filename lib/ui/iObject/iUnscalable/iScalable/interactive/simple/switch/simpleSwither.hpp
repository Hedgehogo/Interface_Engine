#pragma once

#include "../interactiveSimple.hpp"
#include "../../../../../layout/layout.hpp"
#include "../../../../../../drawable/iDrawable/iDrawable.hpp"

#include "../../../uninteractive/uninteractive.hpp"
#include "../../../../../../enums/keyHandler/keyHandler.hpp"

namespace ui {
	class SimpleSwitcher : public Interactive_Simple, public Layout, public IDrawable {
	protected:
		IUninteractive *activeBackground;
		IUninteractive *inactiveBackground;
		DrawManager activeDrawManager;
		DrawManager inactiveDrawManager;
		PSbool active;
	
	public:
		SimpleSwitcher(IUninteractive *inactiveBackground, IUninteractive *activeBackground, PSbool value, Key key = Key::mouseLeft);
		
		SimpleSwitcher(IUninteractive *inactiveBackground, IUninteractive *activeBackground, Key key = Key::mouseLeft, bool startActive = false);
		
		void init(InteractiveInitInfo interactiveInitInfo) override;
		
		void switchValue();
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		SimpleSwitcher *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
		
		~SimpleSwitcher();
	};
	
	bool convertPointer(const YAML::Node &node, SimpleSwitcher *&simpleSwitcher);
}