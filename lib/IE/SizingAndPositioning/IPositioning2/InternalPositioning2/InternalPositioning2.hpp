#pragma once

#include "../IPositioning2.hpp"
#include "../../IPositioning/InternalPositioning/InternalPositioning.hpp"

namespace ui {
	class InternalPositioning2 : public IPositioning2 {
	public:
		InternalPositioning2(sf::Vector2f coefficient);
		
		void init(sf::RenderTarget&);
		
		sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize);
	
		InternalPositioning2* copy();
	
	protected:
		InternalPositioning vertical;
		InternalPositioning horizontal;
	};
	
	template<>
	struct DecodePointer<InternalPositioning2> {
		static bool decodePointer(const YAML::Node& node, InternalPositioning2*& internalPositioning2);
	};
}