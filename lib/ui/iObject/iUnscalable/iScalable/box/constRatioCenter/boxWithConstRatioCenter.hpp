#pragma once

#include "../box.hpp"
#include "../../uninteractive/uninteractive.hpp"
#include "../../uninteractive/onlyDrawable/empty/empty.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"
#include "../../../../iLayout/background/iLayoutWithBackground.hpp"
#include "../../../../iLayout/twoObjects/iLayoutWithTwoObjects.hpp"
#include "../../uninteractive/onlyDrawable/empty/empty.hpp"

namespace ui {
	class BoxWithConstRatioCenter : public Box, public ILayoutWithObject, public ILayoutWithBackground, public ILayoutWithTwoObjects, public IDrawable {
	public:
		BoxWithConstRatioCenter(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& background, float aspectRatio, sf::Vector2f minSize = {});
		
		BoxWithConstRatioCenter(
			BoxPtr<IScalable>&& object,
			BoxPtr<IScalable>&& firstObject,
			BoxPtr<IScalable>&& secondObject,
			BoxPtr<IUninteractive>&& background,
			float aspectRatio,
			sf::Vector2f minSize = {}
		);
		
		BoxWithConstRatioCenter(const BoxWithConstRatioCenter& other);
		
		void init(InitInfo initInfo) override;
		
		void setAspectRatio(float aspectRatio);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IUninteractive& getBackground() override;
		
		const IUninteractive& getBackground() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		IScalable& getFirstObject() override;
		
		const IScalable& getFirstObject() const override;
		
		IScalable& getSecondObject() override;
		
		const IScalable& getSecondObject() const override;
		
		BoxWithConstRatioCenter* copy() override;
		
		void draw() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IUninteractive> background;
		BoxPtr<IScalable> object;
		BoxPtr<IScalable> firstObject;
		BoxPtr<IScalable> secondObject;
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
