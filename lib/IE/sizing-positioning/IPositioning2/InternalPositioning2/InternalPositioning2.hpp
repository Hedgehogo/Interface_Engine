#pragma once

#include "../IPositioning2.hpp"
#include "../../IPositioning/InternalPositioning/InternalPositioning.hpp"

namespace ie {
	class InternalPositioning2 : public virtual IPositioning2 {
	public:
		struct Make : public virtual IPositioning2::Make {
			sf::Vector2f coefficient;
			
			Make(sf::Vector2f coefficient);
		
			InternalPositioning2* make(Positioning2InitInfo init_info) override;
		};
		
		InternalPositioning2(Make&& make, Positioning2InitInfo init_info);
		
		InternalPositioning2(sf::Vector2f coefficient);
		
		sf::Vector2f find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size);
	
	protected:
		InternalPositioning vertical_;
		InternalPositioning horizontal_;
	};
}

template<>
struct ieml::Decode<char, ie::InternalPositioning2::Make> {
	static orl::Option<ie::InternalPositioning2::Make> decode(ieml::Node const& node);
};
