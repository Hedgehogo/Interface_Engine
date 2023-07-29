#pragma once

#include "../box.hpp"
#include "../../uninteractive/uninteractive.hpp"
#include "../../../../iLayout/object/iLayoutWithObject.hpp"
#include "../../../../../interaction/interactionStack/interactionStack.hpp"
#include "../../../../../interaction/interactionManager/interactionManager.hpp"

namespace ui {
	class BoxWithConstBezel : public Box, public ILayoutWithObject {
	public:
		BoxWithConstBezel(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& bezel, float thickness, sf::Vector2f minSize = {0, 0});
		
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
		BoxPtr<IScalable> object;
		BoxPtr<IUninteractive> bezel;
		float thickness;
	};
	
	template<>
	struct DecodePointer<BoxWithConstBezel> {
		static bool decodePointer(const YAML::Node& node, BoxWithConstBezel*& boxWithConstBezel);
	};
	
	using BoxWCBezel = BoxWithConstBezel;
	using BWCBe = BoxWithConstBezel;
}
