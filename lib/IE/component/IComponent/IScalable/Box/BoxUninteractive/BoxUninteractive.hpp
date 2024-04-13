#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"
#include "../../INonInteractive/INonInteractiveLayout/INonInteractiveObject/INonInteractiveObject.hpp"

namespace ie {
	class BoxUninteractive : public Box, public virtual INonInteractiveObject {
	public:
		struct Make : public virtual Box::Make, public virtual INonInteractiveObject::Make {
			BoxPtr<IScalable::Make> object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxUninteractive* override;
		};
		
		BoxUninteractive(Make&& make, InitInfo init_info);
		
		BoxUninteractive(BoxPtr<IScalable>&& object, sf::Vector2f min_size = {});
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(Event event) -> bool override;
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
	protected:
		BoxPtr<IScalable> object_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxUninteractive::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxUninteractive::Make>;
};
