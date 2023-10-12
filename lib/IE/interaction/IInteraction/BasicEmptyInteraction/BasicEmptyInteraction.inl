namespace ie {
	namespace make_system {
		template<typename T>
		ie::BasicEmptyInteraction<T>* BasicEmptyInteraction<T>::make(BasicActionInitInfo<T> initInfo) {
			return new ie::BasicEmptyInteraction<T>{std::move(*this), initInfo};
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
	bool DecodePointer<BasicEmptyInteraction<T> >::decodePointer(const YAML::Node&, BasicEmptyInteraction<T>*& emptyInteraction) {
		emptyInteraction = new BasicEmptyInteraction<T>{};
		return true;
	}
}
