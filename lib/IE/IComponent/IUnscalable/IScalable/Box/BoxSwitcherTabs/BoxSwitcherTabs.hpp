#pragma once

#include "IE/Enums/KeyHandler/KeyHandler.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"
#include "../../BasicInteractiveData/BasicInteractiveData.hpp"

namespace ie {
	class BoxSwitcherTabs : public Box, public virtual IScalableObjectsArray, public virtual IUpdatable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			PSint value;
			Key key;
			bool isHorizontal;
			sf::Vector2f minSize = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSint value, Key key = Key::MouseLeft, bool isHorizontal = true, sf::Vector2f minSize = {});
			
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
		BasicInteractiveData<BoxSwitcherTabs&> interactive;
		std::vector<BoxPtr<IScalable> > objects;
		bool isHorizontal;
		PSint value;
	};
	
	template<>
	struct DecodePointer<BoxSwitcherTabs> {
		static bool decodePointer(const YAML::Node& node, BoxSwitcherTabs*& switcherTabs);
	};
}
