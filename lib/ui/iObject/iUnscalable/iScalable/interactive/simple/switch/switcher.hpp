#pragma once

#include "../interactiveSimple.hpp"
#include "../../../../../layout/layout.hpp"
#include "../../../../../../drawable/iDrawable/iDrawable.hpp"

#include "../../../uninteractive/uninteractive.hpp"
#include "../../../../../../enums/keyHandler/keyHandler.hpp"

namespace ui {
	class Switcher : public Interactive_Simple, public Layout, public IDrawable {
	protected:
		IScalable* activeBackground;
		IScalable* inactiveBackground;
		DrawManager activeDrawManager;
		DrawManager inactiveDrawManager;
		PSbool active;
	
	public:
		Switcher(IScalable* inactiveBackground, IScalable* activeBackground, PSbool value, Key key = Key::mouseLeft);
		
		Switcher(IScalable* inactiveBackground, IScalable* activeBackground, Key key = Key::mouseLeft, bool startActive = false);
		
		void init(InteractiveInitInfo interactiveInitInfo) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		Switcher* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
		
		~Switcher();
	};
	
	template<>
	struct DecodePointer<Switcher> {
		static bool decodePointer(const YAML::Node& node, Switcher*& switcher);
	};
}