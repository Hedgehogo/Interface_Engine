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
		first_(make.first_->make(init_info)), second_(make.second_->make(init_info)) {
	}
	
	template<typename T>
	IBasicInteraction<T>& BasicDoubleInteraction<T>::get_first() {
		return *first_;
	}
	
	template<typename T>
	const IBasicInteraction<T>& BasicDoubleInteraction<T>::get_first() const {
		return *first_;
	}
	
	template<typename T>
	IBasicInteraction<T>& BasicDoubleInteraction<T>::get_second() {
		return *second_;
	}
	
	template<typename T>
	const IBasicInteraction<T>& BasicDoubleInteraction<T>::get_second() const {
		return *second_;
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::start(sf::Vector2i mouse_position) {
		first_->start(mouse_position);
		second_->start(mouse_position);
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::update(sf::Vector2i mouse_position) {
		first_->update(mouse_position);
		second_->update(mouse_position);
	}
	
	template<typename T>
	void BasicDoubleInteraction<T>::finish(sf::Vector2i mouse_position) {
		second_->finish(mouse_position);
		first_->finish(mouse_position);
	}
}
