#pragma once

#include "../box.hpp"
#include "../../uninteractive/uninteractive.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"
#include "../../../../../interaction/interactionStack/interactionStack.hpp"
#include "../../../../../interaction/interactionManager/interactionManager.hpp"

namespace ui {
	class BoxWithConstBezel : public Box, public LayoutWithObject {
	protected:
		IUninteractive *bezel;
		float thickness;
	
	public:
		void init(InitInfo initInfo) override;
		
		BoxWithConstBezel(IScalable *object, IUninteractive *bezel, float thickness, sf::Vector2f minSize = {0, 0});
		
		~BoxWithConstBezel() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		BoxWithConstBezel *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, BoxWithConstBezel *&boxWithConstBezel);
	
	using BoxWCBezel = BoxWithConstBezel;
	using BWCBe = BoxWithConstBezel;
}
