#pragma once

#include "IE/IComponent/IUnscalable/IScalable/Box/Box.hpp"
#include "../../../../ILayout/ILayoutObjectsArray/ILayoutObjectsArray.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IInteractive/BasicBaseInteractive/BasicBaseInteractive.hpp"
#include "IE/Enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	class BoxSwitcherTabs : public Box, public IInteractive, public IUpdatable, public ILayoutObjectsArray {
	public:
		struct Make : public Box::Make, public ILayoutObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			PSint value;
			Key key;
			bool isHorizontal;
			sf::Vector2f minSize = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSint value, Key key = Key::mouseLeft, bool isHorizontal = true, sf::Vector2f minSize = {});
			
			BoxSwitcherTabs* make(InitInfo initInfo) override;
		};
		
		BoxSwitcherTabs(Make&& make, InitInfo initInfo);
		
		BoxSwitcherTabs(std::vector<BoxPtr<IScalable> >&& objects, PSint value, Key key, bool isHorizontal, sf::Vector2f minSize = {});
		
		void init(InitInfo initInfo) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		std::size_t getArraySize() const override;
		
		IScalable& getObjectAt(std::size_t index) override;
		
		const IScalable& getObjectAt(std::size_t index) const override;
		
		int getTab(sf::Vector2f position);
		
		BoxSwitcherTabs* copy() override;
	
	protected:
		BaseInteractiveData interactive;
		std::vector<BoxPtr<IScalable> > objects;
		bool isHorizontal;
		PSint value;
	};
	
	template<>
	struct DecodePointer<BoxSwitcherTabs> {
		static bool decodePointer(const YAML::Node& node, BoxSwitcherTabs*& switcherTabs);
	};
}
