#pragma once

#include "IE/enums/Location2/Location2.hpp"
#include "../IPositioning/IPositioning.hpp"
#include "../IPositioning/InternalPositioning/InternalPositioning.hpp"
#include "../IPositioning/InternalTargetPositioning/InternalTargetPositioning.hpp"
#include "../IPositioning/MatchPositioning/MatchPositioning.hpp"
#include "../IPositioning/MatchSidesPositioning/MatchSidesPositioning.hpp"
#include "../IPositioning/MatchTargetPositioning/MatchTargetPositioning.hpp"
#include "IE/sizing-positioning/IPositioning/FnPositioning/FnPositioning.hpp"
#include "Positioning2initInfo/Positioning2InitInfo.hpp"

namespace ie {
	class IPositioning2 {
	public:
		struct Make {
			virtual IPositioning2* make(Positioning2InitInfo init_info) = 0;
			
			virtual ~Make() = default;
		};
		
		virtual ~IPositioning2() = default;
		
		virtual void init(sf::RenderTarget& render_target) = 0;
		
		virtual sf::Vector2f find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size) = 0;
		
		virtual sf::Vector2f operator()(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size);
		
		virtual IPositioning2* copy() = 0;
	};
}