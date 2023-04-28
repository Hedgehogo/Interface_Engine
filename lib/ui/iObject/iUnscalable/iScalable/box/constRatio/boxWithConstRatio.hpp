#pragma once

#include "../box.hpp"
#include "../../uninteractive/onlyDrawable/empty/empty.hpp"
#include "../../../../layout/background/layoutWithBackground.hpp"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.hpp"
#include "../../../../../enums/corner/corner.hpp"

namespace ui {
	class BoxWithConstRatio : public Box, public LayoutWithBackground, public LayoutWithTwoObjects, public IDrawable {
	protected:
		DrawManager secondDrawManager;
		bool verticalSide, horizontalSide;      //true = up   true = left
		bool renderSecond;
		float aspectRatio;
		
		void copy(BoxWithConstRatio *boxWithConstRatio);
	
	public:
		BoxWithConstRatio(IScalable *constObject, IScalable *secondObject, IUninteractive *background, float aspectRatio, Corner corner = Corner::upLeft, sf::Vector2f minSize = {0, 0});
		
		void init(InitInfo initInfo) override;
		
		Corner getCorner();
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		BoxWithConstRatio *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, BoxWithConstRatio *&boxWithConstRatio);
	
	template<>
	struct DecodePointer<BoxWithConstRatio> {
		static bool decodePointer(const YAML::Node &node, BoxWithConstRatio *&boxWithConstRatio);
	};
	
	using BoxWCRatio = BoxWithConstRatio;
	using BWCR = BoxWithConstRatio;
}