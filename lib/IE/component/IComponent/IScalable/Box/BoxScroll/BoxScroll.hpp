#pragma once

#include "../BoxView/BoxView.hpp"
#include "IE/Modules/yaml-cpp/shared/vector/general/sVector2.hpp"

namespace ie {
	class BoxScroll : public BoxWithView {
	protected:
		sf::Vector2f getNewObjectPosition(sf::Vector2f normalObjectPosition);
	
	public:
		struct Make : public virtual Box::Make {
			BoxPtr<IComponent::Make> object;
			PSRVec2f normalObjectPosition;
			sf::Vector2f minSize;
			
			Make(BoxPtr<IComponent::Make>&& object, PSRVec2f normalObjectPosition, sf::Vector2f minSize = {});
			
			BoxScroll* make(InitInfo initInfo) override;
		};
		
		BoxScroll(Make&& make, InitInfo initInfo);
		
		BoxScroll(BoxPtr<IComponent>&& object, const PSRVec2f& normalObjectPosition, const sf::Vector2f& minSize = {});
		
		void init(InitInfo initInfo) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxScroll* copy() override;
	
	protected:
		BoxPtr<IComponent> object;
		PSRVec2f normalObjectPosition;
	};
	
	template<>
	struct DecodePointer<BoxScroll> {
		static bool decodePointer(const YAML::Node& node, BoxScroll*& boxScroll);
	};
}