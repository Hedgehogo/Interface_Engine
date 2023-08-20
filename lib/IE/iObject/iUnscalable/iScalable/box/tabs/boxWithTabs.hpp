#pragma once

#include "IE/iObject/iUnscalable/iScalable/box/box.hpp"
#include "IE/iObject/iLayout/objectsArray/iLayoutWithObjectsArray.hpp"

namespace ui {
	class BoxWithTabs : public Box, public ILayoutWithObjectsArray, public IDrawable {
	public:
		struct Make : public Box::Make, public ILayoutWithObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			PISint value;
			sf::Vector2f minSize = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PISint value, sf::Vector2f minSize = {});
			
			BoxWithTabs* make(InitInfo initInfo) override;
		};
		
		BoxWithTabs(Make&& make, InitInfo initInfo);
		
		BoxWithTabs(std::vector<BoxPtr<IScalable> >&& objects, PISint value, sf::Vector2f minSize = {});
		
		BoxWithTabs(const BoxWithTabs& other);
		
		void init(InitInfo initInfo) override;
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void draw() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		std::size_t getArraySize() const override;
		
		IScalable& getObjectAt(std::size_t index) override;
		
		const IScalable& getObjectAt(std::size_t index) const override;
		
		BoxWithTabs* copy() override;
	
	protected:
		std::vector<DrawManager> drawManagers;
		std::vector<BoxPtr<IScalable> > objects;
		PISint value;
	};
	
	template<>
	struct DecodePointer<BoxWithTabs> {
		static bool decodePointer(const YAML::Node& node, BoxWithTabs*& boxWithTabs);
	};
}
