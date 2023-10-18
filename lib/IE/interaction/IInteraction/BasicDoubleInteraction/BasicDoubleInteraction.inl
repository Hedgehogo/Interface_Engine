namespace ie {
	namespace make_system {
		template<typename T>
		BasicDoubleInteraction<T>::BasicDoubleInteraction(
			BoxPtr<IBasicInteraction<T> >&& first,
			BoxPtr<IBasicInteraction<T> >&& second
		) : first(std::move(first)), second(std::move(second)) {
		}
		
		template<typename T>
		ie::BasicDoubleInteraction<T>* BasicDoubleInteraction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicDoubleInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicDoubleInteraction<T>::BasicDoubleInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		first(make.first->make(init_info)), second(make.second->make(init_info)) {
	}
	
	template<typename T>
	BasicDoubleInteraction<T>::BasicDoubleInteraction(BoxPtr<IBasicInteraction<T> >&& first, BoxPtr<IBasicInteraction<T> >&& second) :
		first(std::move(first)), second(std::move(second)) {
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::set_first(BoxPtr<IBasicInteraction<T> >&& first) {
		this->first = std::move(first);
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::set_second(BoxPtr<IBasicInteraction<T> >&& second) {
		this->second = std::move(second);
	}
	
	template<typename T>
	IBasicInteraction<T>& BasicDoubleInteraction<T>::get_first() {
		return *first;
	}
	
	template<typename T>
	const IBasicInteraction<T>& BasicDoubleInteraction<T>::get_first() const {
		return *first;
	}
	
	template<typename T>
	IBasicInteraction<T>& BasicDoubleInteraction<T>::get_second() {
		return *second;
	}
	
	template<typename T>
	const IBasicInteraction<T>& BasicDoubleInteraction<T>::get_second() const {
		return *second;
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::start(sf::Vector2i mouse_position) {
		first->start(mouse_position);
		second->start(mouse_position);
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::update(sf::Vector2i mouse_position) {
		first->update(mouse_position);
		second->update(mouse_position);
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::finish(sf::Vector2i mouse_position) {
		second->finish(mouse_position);
		first->finish(mouse_position);
	}
	
	template<typename T>
	BasicDoubleInteraction<T>* BasicDoubleInteraction<T>::copy() {
		return new BasicDoubleInteraction<T>{*this};
	}
}
