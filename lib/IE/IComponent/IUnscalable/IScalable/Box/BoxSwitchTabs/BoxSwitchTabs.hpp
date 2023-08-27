#pragma once

#include "../Box.hpp"
#include "../../../../ILayout/ILayoutObjectsArray/ILayoutObjectsArray.hpp"

namespace ie {
	class BoxSwitchTabs : public Box, public ILayoutObjectsArray, public IDrawable {
	public:
		struct Make : public Box::Make, public ILayoutObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			PSValue<uint> value;
			sf::Vector2f minSize = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSValue<uint> value, sf::Vector2f minSize = {});
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, uint index = 0, sf::Vector2f minSize = {});
			
			BoxSwitchTabs* make(InitInfo initInfo) override;
		};
		
		BoxSwitchTabs(Make&& make, InitInfo initInfo);
		
		BoxSwitchTabs(std::vector<BoxPtr<IScalable> >&& objects, PSValue<uint> value, sf::Vector2f minSize = {});
		
		BoxSwitchTabs(std::vector<BoxPtr<IScalable> >&& objects, uint index = 0, sf::Vector2f minSize = {});
		
		BoxSwitchTabs(const BoxSwitchTabs& other);
		
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
		
		BoxSwitchTabs* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		std::vector<DrawManager> drawManagers;
		std::vector<BoxPtr<IScalable> > objects;
		PSValue<uint> value;
	};
	
	template<>
	struct DecodePointer<BoxSwitchTabs> {
		static bool decodePointer(const YAML::Node& node, BoxSwitchTabs*& boxWithChangeableObjects);
	};
}
