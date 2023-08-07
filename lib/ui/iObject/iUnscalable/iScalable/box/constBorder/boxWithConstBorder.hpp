#pragma once

#include "../box.hpp"
#include "../../iScalable.hpp"
#include "../../../../iLayout/twoObjects/iLayoutWithTwoObjects.hpp"
#include "../../../../../interaction/interactionStack/interactionStack.hpp"
#include "../../../../../enums/side/side.hpp"

namespace ui {
	class BoxWithConstBorder : public Box, public ILayoutWithTwoObjects {
	public:
		struct Make : public Box::Make, public ILayoutWithTwoObjects::Make {
			BoxPtr<IScalable::Make> constObject;
			BoxPtr<IScalable::Make> secondObject;
			float borderDistance;
			Side side;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& constObject, BoxPtr<IScalable::Make>&& secondObject, float borderDistance, Side side, sf::Vector2f minSize = {});
			
			BoxWithConstBorder* make(InitInfo initInfo) override;
		};
		
		BoxWithConstBorder(Make&& make, InitInfo initInfo);
		
		BoxWithConstBorder(BoxPtr<IScalable>&& constObject, BoxPtr<IScalable>&& secondObject, Side side, float borderDistance, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getFirstObject() override;
		
		const IScalable& getFirstObject() const override;
		
		IScalable& getSecondObject() override;
		
		const IScalable& getSecondObject() const override;
		
		BoxWithConstBorder* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IScalable> constObject;
		BoxPtr<IScalable> secondObject;
		float borderDistance;
		Side side;
	};
	
	template<>
	struct DecodePointer<BoxWithConstBorder> {
		static bool decodePointer(const YAML::Node& node, BoxWithConstBorder*& boxWithConstBorder);
	};
	
	using BoxWCBorder = BoxWithConstBorder;
	using BWCBo = BoxWithConstBorder;
}