#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxAlternative : public Box, public virtual IScalableTwoObjects {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> top_object;
			BoxPtr<IScalable::Make> bottom_object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& top_object, BoxPtr<IScalable::Make>&& bottom_object, sf::Vector2f min_size = {});
			
			BoxAlternative* make(InitInfo init_info) override;
		};
		
		BoxAlternative(Make&& make, InitInfo init_info);
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		IScalable& get_first_object() override;
		
		const IScalable& get_first_object() const override;
		
		IScalable& get_second_object() override;
		
		const IScalable& get_second_object() const override;
		
	protected:
		BoxPtr<IScalable> bottom_object_;
		BoxPtr<IScalable> top_object_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxAlternative::Make> {
	static orl::Option<ie::BoxAlternative::Make> decode(ieml::Node const& node);
};
