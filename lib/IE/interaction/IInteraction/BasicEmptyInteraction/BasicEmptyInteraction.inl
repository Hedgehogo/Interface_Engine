namespace ie {
	namespace make_system {
		template<typename T>
		auto BasicEmptyInteraction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicEmptyInteraction<T>* {
			return new ie::BasicEmptyInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicEmptyInteraction<T>::BasicEmptyInteraction(Make&&, BasicActionInitInfo<T>) {
	}
	
	template<typename T>
	BasicEmptyInteraction<T>::BasicEmptyInteraction() {
	}
	
	template<typename T>
	auto BasicEmptyInteraction<T>::start(sf::Vector2i) -> void {
	}
	
	template<typename T>
	auto BasicEmptyInteraction<T>::update(sf::Vector2i) -> void {
	}
	
	template<typename T>
	auto BasicEmptyInteraction<T>::finish(sf::Vector2i) -> void {
	}
}

template<typename T>
auto ieml::Decode<char, ie::BasicEmptyInteraction<T> >::decode(ieml::Node const&) -> orl::Option<ie::BasicEmptyInteraction<T> > {
	return ie::BasicEmptyInteraction<T>{};
}
