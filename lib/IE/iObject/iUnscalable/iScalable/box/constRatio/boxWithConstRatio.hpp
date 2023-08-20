#pragma once

#include "../box.hpp"
#include "../../uninteractive/onlyDrawable/empty/empty.hpp"
#include "../../../../iLayout/background/iLayoutWithBackground.hpp"
#include "../../../../iLayout/twoObjects/iLayoutWithTwoObjects.hpp"
#include "../../../../../Enums/Corner/Corner.hpp"

namespace ui {
	class BoxWithConstRatio : public Box, public ILayoutWithBackground, public ILayoutWithTwoObjects, public IDrawable {
	public:
		struct Make : public Box::Make, public ILayoutWithBackground::Make, public ILayoutWithTwoObjects::Make {
			BoxPtr<IScalable::Make> constObject;
			BoxPtr<IScalable::Make> secondObject;
			BoxPtr<IUninteractive::Make> background;
			float aspectRatio;
			Corner corner = Corner::upLeft;
			sf::Vector2f minSize = {};
			
			Make(
				BoxPtr<IScalable::Make>&& constObject,
				BoxPtr<IScalable::Make>&& secondObject,
				BoxPtr<IUninteractive::Make>&& background,
				float aspectRatio = 1.f,
				Corner corner = Corner::upLeft,
				sf::Vector2f minSize = {}
			);
			
			BoxWithConstRatio* make(InitInfo initInfo) override;
		};
		
		BoxWithConstRatio(Make&& make, InitInfo initInfo);
		
		BoxWithConstRatio(
			BoxPtr<IScalable>&& constObject,
			BoxPtr<IScalable>&& secondObject,
			BoxPtr<IUninteractive>&& background,
			float aspectRatio,
			Corner corner = Corner::upLeft,
			sf::Vector2f minSize = {}
		);
		
		BoxWithConstRatio(const BoxWithConstRatio& other);
		
		void init(InitInfo initInfo) override;
		
		Corner getCorner();
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IUninteractive& getBackground() override;
		
		const IUninteractive& getBackground() const override;
		
		IScalable& getFirstObject() override;
		
		const IScalable& getFirstObject() const override;
		
		IScalable& getSecondObject() override;
		
		const IScalable& getSecondObject() const override;
		
		BoxWithConstRatio* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		DrawManager secondDrawManager;
		BoxPtr<IUninteractive> background;
		BoxPtr<IScalable> constObject;
		BoxPtr<IScalable> secondObject;
		bool verticalSide, horizontalSide;      //true = up   true = left
		bool renderSecond;
		float aspectRatio;
	};
	
	template<>
	struct DecodePointer<BoxWithConstRatio> {
		static bool decodePointer(const YAML::Node& node, BoxWithConstRatio*& boxWithConstRatio);
	};
	
	using BoxWCRatio = BoxWithConstRatio;
	using BWCR = BoxWithConstRatio;
}