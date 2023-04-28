#pragma once

#include "../box.hpp"
#include "../../../../layout/objectsArray/layoutWithObjectsArray.hpp"
#include "../../../../../interaction/interactionStack/interactionStack.hpp"

namespace ui {
	class BoxWithBorderHorizontal : public Box, public LayoutWithObjectsArray {
	protected:
		std::vector<float> bounds;
	
	public:
		BoxWithBorderHorizontal(std::vector<IScalable *> objects, std::vector<float> bounds, sf::Vector2f minSize = {0, 0});
		
		BoxWithBorderHorizontal(std::vector<IScalable *> objects, sf::Vector2f minSize = {0, 0});
		
		BoxWithBorderHorizontal(IScalable *firstObject, IScalable *secondObject, float bound = 0.5f, sf::Vector2f minSize = {0, 0});
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		BoxWithBorderHorizontal *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	
	template<>
	struct DecodePointer<BoxWithBorderHorizontal> {
		static bool decodePointer(const YAML::Node &node, BoxWithBorderHorizontal *&boxWithBorderHorizontal);
	};
	
	using BoxWBorderH = BoxWithBorderHorizontal;
	using BWBH = BoxWithBorderHorizontal;
}
