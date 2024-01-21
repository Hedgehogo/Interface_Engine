#pragma once

#include "box-ptr/BoxPtr.hpp"
#include "../IPositioning2.hpp"

namespace ie {
	using namespace bp;
	
	class Positioning2 : public virtual IPositioning2 {
	public:
		struct Make : public virtual IPositioning2::Make {
			BoxPtr<IPositioning> horizontal;
			BoxPtr<IPositioning> vertical;
			
			Make(BoxPtr<IPositioning>&& horizontal, BoxPtr<IPositioning>&& vertical);
			
			Make(sf::Vector2f coefficient, sf::Vector2f offset = {}, bool relative_target = false);
			
			Make(Location2 parent_location, Location2 object_location, sf::Vector2f offset = {});
			
			Make(sf::Vector2f coefficient, sf::Vector2f object_coefficient, sf::Vector2f offset, bool relative_target = false);
			
			Positioning2* make(Positioning2InitInfo init_info) override;
		};
		
		Positioning2(Make&& make, Positioning2InitInfo init_info);
		
		Positioning2(BoxPtr<IPositioning>&& horizontal, BoxPtr<IPositioning>&& vertical);
		
		Positioning2(sf::Vector2f coefficient, sf::Vector2f offset = {}, bool relative_target = false);
		
		Positioning2(Location2 parent_location, Location2 object_location, sf::Vector2f offset = {});
		
		Positioning2(sf::Vector2f coefficient, sf::Vector2f object_coefficient, sf::Vector2f offset, bool relative_target = false);
		
		void init(sf::RenderTarget& render_target) override;
		
		sf::Vector2f find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size) override;
		
		Positioning2* copy() override;
	
	protected:
		BoxPtr<IPositioning> horizontal_;
		BoxPtr<IPositioning> vertical_;
		sf::RenderTarget* render_target_;
	};
}

template<>
struct ieml::Decode<char, ie::Positioning2::Make> {
	static orl::Option<ie::Positioning2::Make> decode(ieml::Node const& node);
};
