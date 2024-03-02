#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class BoxMakePermeable : public Box, public virtual IScalableObject {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxMakePermeable* override;
		};
		
		BoxMakePermeable(Make&& make, InitInfo init_info);
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
	protected:
		BoxPtr<IScalable> object_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxMakePermeable::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxMakePermeable::Make>;
};
