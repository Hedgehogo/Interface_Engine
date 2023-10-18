namespace ie {
	namespace make_system {
		template<typename T>
		ie::BasicEmptyInteraction<T>* BasicEmptyInteraction<T>::make(BasicActionInitInfo<T> init_info) {
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
	void BasicEmptyInteraction<T>::start(sf::Vector2i) {
	}
	
	template<typename T>
	void BasicEmptyInteraction<T>::update(sf::Vector2i) {
	}
	
	template<typename T>
	void BasicEmptyInteraction<T>::finish(sf::Vector2i) {
	}
	
	template<typename T>
	BasicEmptyInteraction<T>* BasicEmptyInteraction<T>::copy() {
		return new BasicEmptyInteraction<T>{};
	}
	
	template<typename T>
	bool DecodePointer<BasicEmptyInteraction<T> >::decode_pointer(const YAML::Node&, BasicEmptyInteraction<T>*& empty_interaction) {
		empty_interaction = new BasicEmptyInteraction<T>{};
		return true;
	}
}
