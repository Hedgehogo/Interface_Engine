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
		struct Make : public Box::Make, public ILayoutWithObject::Make, public ILayoutWithBackground::Make, public ILayoutWithTwoObjects::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IScalable::Make> firstObject;
			BoxPtr<IScalable::Make> secondObject;
			BoxPtr<IUninteractive::Make> background;
			float aspectRatio;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, float aspectRatio, sf::Vector2f minSize = {});
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				BoxPtr<IScalable::Make>&& firstObject,
				BoxPtr<IScalable::Make>&& secondObject,
				BoxPtr<IUninteractive::Make>&& background,
				float aspectRatio = 1.f,
				sf::Vector2f minSize = {}
			);
			
			BoxWithConstRatioCenter* make(InitInfo initInfo) override;
		};
		
		BoxWithConstRatioCenter(Make&& make, InitInfo initInfo);
		
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
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
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
		DrawManager firstDrawManager;
		DrawManager secondDrawManager;
		BoxPtr<IUninteractive> background;
		BoxPtr<IScalable> object;
		BoxPtr<IScalable> firstObject;
		BoxPtr<IScalable> secondObject;
		float aspectRatio;
		bool renderFirst;
		bool renderSecond;
	};
	
	template<>
	struct DecodePointer<BoxWithConstRatioCenter> {
		static bool decodePointer(const YAML::Node& node, BoxWithConstRatioCenter*& boxWithConstRatioCenter);
	};
	
	using BoxWCRCenter = BoxWithConstRatioCenter;
	using BWCRC = BoxWithConstRatioCenter;
}
