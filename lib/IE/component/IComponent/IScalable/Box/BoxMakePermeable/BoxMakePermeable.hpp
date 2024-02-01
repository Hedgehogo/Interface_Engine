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
			
			BoxMakePermeable* make(InitInfo init_info) override;
		};
		
		BoxMakePermeable(Make&& make, InitInfo init_info);
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
	protected:
		BoxPtr<IScalable> object_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxMakePermeable::Make> {
	static orl::Option<ie::BoxMakePermeable::Make> decode(ieml::Node const& node);
};
