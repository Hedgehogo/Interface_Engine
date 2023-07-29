#pragma once

#include "../box.hpp"
#include "../../../../iLayout/objectsArray/iLayoutWithObjectsArray.hpp"

namespace ui {
	class BoxWithChangeableObjects : public Box, public ILayoutWithObjectsArray, public IDrawable {
	public:
		BoxWithChangeableObjects(std::vector<BoxPtr<IScalable> >&& objects, PSValue<uint> value, sf::Vector2f minSize = {});
		
		BoxWithChangeableObjects(std::vector<BoxPtr<IScalable> >&& objects, uint index = 0, sf::Vector2f minSize = {});
		
		BoxWithChangeableObjects(const BoxWithChangeableObjects& other);
		
		void init(InitInfo initInfo) override;
		
		void setValue(PSValue<uint> index);
		
		PSValue<uint> getValue();
		
		void setIndex(uint index);
		
		uint getIndex();
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		std::size_t getArraySize() const override;
		
		IScalable& getObjectAt(std::size_t index) override;
		
		const IScalable& getObjectAt(std::size_t index) const override;
		
		BoxWithChangeableObjects* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		std::vector<BoxPtr<IScalable> > objects;
		std::vector<DrawManager> drawManagers;
		PSValue<uint> value;
	};
	
	template<>
	struct DecodePointer<BoxWithChangeableObjects> {
		static bool decodePointer(const YAML::Node& node, BoxWithChangeableObjects*& boxWithChangeableObjects);
	};
}
