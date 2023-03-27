#pragma once

#include "../box.hpp"
#include "../../../../layout/objectsArray/layoutWithObjectsArray.hpp"

namespace ui {
	class BoxWithChangeableObjects : public Box, public LayoutWithObjectsArray, public IDrawable {
	protected:
		std::shared_ptr<SValue<uint>> value;
		std::vector<IScalable *> objects;
		std::vector<DrawManager> drawManagers;
		
	public:
		BoxWithChangeableObjects(std::vector<IScalable *> objects, std::shared_ptr<SValue<uint>> value, sf::Vector2f minSize = {0, 0});
		
		BoxWithChangeableObjects(std::vector<IScalable *> objects, uint index = 0, sf::Vector2f minSize = {0, 0});
		
		void init(InitInfo initInfo) override;
		
		void setValue(std::shared_ptr<SValue<uint>> index);
		
		std::shared_ptr<SValue<uint>> getValue();
		
		void setIndex(uint index);
		
		uint getIndex();
		
		IScalable *getObject();
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxWithChangeableObjects *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, BoxWithChangeableObjects *&boxWithChangeableObjects);
}