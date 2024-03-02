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
	
	template<typename T>
	auto DecodePointer<BasicEmptyInteraction<T> >::decode_pointer(YAML::Node const&, BasicEmptyInteraction<T>*& empty_interaction) -> bool {
		empty_interaction = new BasicEmptyInteraction<T>{};
		return true;
	}
}
