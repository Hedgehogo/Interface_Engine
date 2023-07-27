#pragma once

#include "../box.hpp"
#include "../../uninteractive/uninteractive.hpp"
#include "../../uninteractive/onlyDrawable/empty/empty.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"
#include "../../../../layout/background/layoutWithBackground.hpp"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.hpp"
#include "../../uninteractive/onlyDrawable/empty/empty.hpp"

namespace ui {
	class BoxWithConstRatioCenter : public Box, public LayoutWithObject, public LayoutWithBackground, public LayoutWithTwoObjects, public IDrawable {
	public:
		BoxWithConstRatioCenter(IScalable* object, IUninteractive* background, float aspectRatio, sf::Vector2f minSize = {});
		
		BoxWithConstRatioCenter(IScalable* object, IScalable* firstObject, IScalable* secondObject, IUninteractive* background, float aspectRatio, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void setAspectRatio(float aspectRatio);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		BoxWithConstRatioCenter* copy() override;
		
		void draw() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		float aspectRatio;
		bool renderFirst;
		bool renderSecond;
		DrawManager firstDrawManager;
		DrawManager secondDrawManager;
	};
	
	template<>
	struct DecodePointer<BoxWithConstRatioCenter> {
		static bool decodePointer(const YAML::Node& node, BoxWithConstRatioCenter*& boxWithConstRatioCenter);
	};
	
	using BoxWCRCenter = BoxWithConstRatioCenter;
	using BWCRC = BoxWithConstRatioCenter;
}
