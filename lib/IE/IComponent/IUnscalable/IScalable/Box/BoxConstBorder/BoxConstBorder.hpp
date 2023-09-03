#pragma once

#include "../Box.hpp"
#include "../../IScalable.hpp"
#include "../../../../ILayout/ILayoutTwoObjects/ILayoutTwoObjects.hpp"
#include "../../../../../Interaction/InteractionStack/InteractionStack.hpp"
#include "../../../../../Enums/Side/Side.hpp"

namespace ie {
	class BoxConstBorder : public Box, public virtual ILayoutTwoObjects {
	public:
		struct Make : public virtual Box::Make, public virtual ILayoutTwoObjects::Make {
			BoxPtr<IScalable::Make> constObject;
			BoxPtr<IScalable::Make> secondObject;
			float borderDistance;
			Side side;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& constObject, BoxPtr<IScalable::Make>&& secondObject, float borderDistance, Side side, sf::Vector2f minSize = {});
			
			BoxConstBorder* make(InitInfo initInfo) override;
		};
		
		BoxConstBorder(Make&& make, InitInfo initInfo);
		
		BoxConstBorder(BoxPtr<IScalable>&& constObject, BoxPtr<IScalable>&& secondObject, Side side, float borderDistance, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getFirstObject() override;
		
		const IScalable& getFirstObject() const override;
		
		IScalable& getSecondObject() override;
		
		const IScalable& getSecondObject() const override;
		
		BoxConstBorder* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IScalable> constObject;
		BoxPtr<IScalable> secondObject;
		float borderDistance;
		Side side;
	};
	
	template<>
	struct DecodePointer<BoxConstBorder> {
		static bool decodePointer(const YAML::Node& node, BoxConstBorder*& boxWithConstBorder);
	};
}