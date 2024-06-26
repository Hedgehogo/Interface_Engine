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
			
			auto make(Positioning2InitInfo init_info) -> Positioning2* override;
		};
		
		Positioning2(Make&& make, Positioning2InitInfo init_info);
		
		auto find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size) -> sf::Vector2f override;
		
	protected:
		BoxPtr<IPositioning> horizontal_;
		BoxPtr<IPositioning> vertical_;
		sf::RenderTarget* render_target_;
	};
}

template<>
struct ieml::Decode<char, ie::Positioning2::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Positioning2::Make>;
};
