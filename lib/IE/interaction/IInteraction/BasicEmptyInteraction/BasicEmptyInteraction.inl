namespace ie {
	namespace make_system {
		template<typename A_>
		auto BasicEmptyInteraction<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicEmptyInteraction<A_>* {
			return new ie::BasicEmptyInteraction<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicEmptyInteraction<A_>::BasicEmptyInteraction(Make&&, BasicActionInitInfo<A_>) {
	}
	
	template<typename A_>
	BasicEmptyInteraction<A_>::BasicEmptyInteraction() {
	}
	
	template<typename A_>
	auto BasicEmptyInteraction<A_>::start(sf::Vector2i) -> void {
	}
	
	template<typename A_>
	auto BasicEmptyInteraction<A_>::handle_event(Event event) -> bool {
		return false;
	}
	
	template<typename A_>
	auto BasicEmptyInteraction<A_>::update(sf::Vector2i) -> void {
	}
	
	template<typename A_>
	auto BasicEmptyInteraction<A_>::finish(sf::Vector2i) -> void {
	}
}

template<typename A_>
auto ieml::Decode<char, ie::BasicEmptyInteraction<A_> >::decode(ieml::Node const&) -> orl::Option<ie::BasicEmptyInteraction<A_> > {
	return ie::BasicEmptyInteraction<A_>{};
}
