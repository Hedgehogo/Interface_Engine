#pragma once

#include "../box.hpp"
#include "../../../../iLayout/objectsArray/iLayoutWithObjectsArray.hpp"
#include "../../../../../interaction/interactionStack/interactionStack.hpp"
#include "../../../../../interaction/interactionManager/interactionManager.hpp"

namespace ui {
	class BoxWithBorderVertical : public Box, public ILayoutWithObjectsArray {
	public:
		BoxWithBorderVertical(std::vector<BoxPtr<IScalable> >&& objects, std::vector<float> bounds, sf::Vector2f minSize = {0, 0});
		
		BoxWithBorderVertical(std::vector<BoxPtr<IScalable> >&& objects, sf::Vector2f minSize = {0, 0});
		
		BoxWithBorderVertical(BoxPtr<IScalable>&& firstObject, BoxPtr<IScalable>&& secondObject, float bound = 0.5f, sf::Vector2f minSize = {0, 0});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		std::size_t getArraySize() const override;
		
		IScalable& getObjectAt(std::size_t index) override;
		
		const IScalable& getObjectAt(std::size_t index) const override;
		
		BoxWithBorderVertical* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		std::vector<BoxPtr<IScalable> > objects;
		std::vector<float> bounds;
	};
	
	template<>
	struct DecodePointer<BoxWithBorderVertical> {
		static bool decodePointer(const YAML::Node& node, BoxWithBorderVertical*& boxWithBorderVertical);
	};
	
	using BoxWBorderV = BoxWithBorderVertical;
	using BWBV = BoxWithBorderVertical;
}
