#pragma once

#include "../box.hpp"
#include "../../uninteractive/uninteractive.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"
#include "../../../../../Interaction/InteractionStack/InteractionStack.hpp"
#include "../../../../../Interaction/InteractionManager/InteractionManager.hpp"

namespace ui {
	class BoxWithConstBezel : public Box, public ILayoutWithObject {
	public:
		struct Make : public Box::Make, public ILayoutWithObject::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IUninteractive::Make> bezel;
			float thickness;
			sf::Vector2f minSize = {};
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& bezel, float thickness, sf::Vector2f minSize = {});
			
			BoxWithConstBezel* make(InitInfo initInfo) override;
		};
		
		BoxWithConstBezel(Make&& make, InitInfo initInfo);
		
		BoxWithConstBezel(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& bezel, float thickness, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		BoxWithConstBezel* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		BoxPtr<IUninteractive> bezel;
		BoxPtr<IScalable> object;
		float thickness;
	};
	
	template<>
	struct DecodePointer<BoxWithConstBezel> {
		static bool decodePointer(const YAML::Node& node, BoxWithConstBezel*& boxWithConstBezel);
	};
	
	using BoxWCBezel = BoxWithConstBezel;
	using BWCBe = BoxWithConstBezel;
}
