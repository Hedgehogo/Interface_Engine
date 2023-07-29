#pragma once

#include "../view/boxWithView.hpp"
#include "modules/appendix/yaml-cpp/shared/vector/general/sVector2.hpp"

namespace ui {
	class BoxScroll : public BoxWithView {
	public:
		BoxScroll(BoxPtr<IUnscalable>&& object, const PSRVec2f& normalObjectPosition, const sf::Vector2f& minSize);
		
		void init(InitInfo initInfo) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
	
	protected:
		sf::Vector2f getNewObjectPosition(sf::Vector2f normalObjectPosition);
	
	public:
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxScroll* copy() override;
	
	protected:
		BoxPtr<IUnscalable> object;
		PSRVec2f normalObjectPosition;
	};
	
	template<>
	struct DecodePointer<BoxScroll> {
		static bool decodePointer(const YAML::Node& node, BoxScroll*& boxScroll);
	};
}