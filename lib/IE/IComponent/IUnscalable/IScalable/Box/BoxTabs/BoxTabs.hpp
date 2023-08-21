#pragma once

#include "IE/IComponent/IUnscalable/IScalable/Box/Box.hpp"
#include "IE/IComponent/ILayout/ILayoutObjectsArray/ILayoutObjectsArray.hpp"

namespace ui {
	class BoxTabs : public Box, public ILayoutObjectsArray, public IDrawable {
	public:
		struct Make : public Box::Make, public ILayoutObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			PISint value;
			sf::Vector2f minSize = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PISint value, sf::Vector2f minSize = {});
			
			BoxTabs* make(InitInfo initInfo) override;
		};
		
		BoxTabs(Make&& make, InitInfo initInfo);
		
		BoxTabs(std::vector<BoxPtr<IScalable> >&& objects, PISint value, sf::Vector2f minSize = {});
		
		BoxTabs(const BoxTabs& other);
		
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
		
		BoxTabs* copy() override;
	
	protected:
		std::vector<DrawManager> drawManagers;
		std::vector<BoxPtr<IScalable> > objects;
		PISint value;
	};
	
	template<>
	struct DecodePointer<BoxTabs> {
		static bool decodePointer(const YAML::Node& node, BoxTabs*& boxWithTabs);
	};
}
