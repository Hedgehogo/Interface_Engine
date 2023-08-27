#pragma once

#include "../BasicBaseInteractive.hpp"
#include "IE/IComponent/ILayout/ILayout.hpp"
#include "../../../../../../IDrawable/IDrawable/IDrawable.hpp"

#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/IUninteractive.hpp"
#include "../../../../../../Enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	class Switcher : public BaseInteractive, public ILayout, public IDrawable {
	public:
		struct Make : public IScalable::Make, public ILayout::Make {
			BoxPtr<IScalable::Make> inactiveBackground;
			BoxPtr<IScalable::Make> activeBackground;
			PSbool value;
			Key key = Key::mouseLeft;
			
			Make(BoxPtr<IScalable::Make>&& inactiveBackground, BoxPtr<IScalable::Make>&& activeBackground, PSbool value, Key key = Key::mouseLeft);
			
			Make(BoxPtr<IScalable::Make>&& inactiveBackground, BoxPtr<IScalable::Make>&& activeBackground, Key key = Key::mouseLeft, bool startActive = false);
			
			Switcher* make(InitInfo initInfo) override;
		};
		
		Switcher(Make&& make, InitInfo initInfo);
		
		Switcher(BoxPtr<IScalable>&& inactiveBackground, BoxPtr<IScalable>&& activeBackground, PSbool value, Key key = Key::mouseLeft);
		
		Switcher(BoxPtr<IScalable>&& inactiveBackground, BoxPtr<IScalable>&& activeBackground, Key key = Key::mouseLeft, bool startActive = false);
		
		void init(InitInfo initInfo) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		Switcher* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		LayoutData& layoutGetData() override;
		
		const LayoutData& layoutGetData() const override;
		
		LayoutData layout;
		DrawManager inactiveDrawManager;
		DrawManager activeDrawManager;
		BoxPtr<IScalable> inactiveBackground;
		BoxPtr<IScalable> activeBackground;
		PSbool active;
	};
	
	template<>
	struct DecodePointer<Switcher> {
		static bool decodePointer(const YAML::Node& node, Switcher*& switcher);
	};
}