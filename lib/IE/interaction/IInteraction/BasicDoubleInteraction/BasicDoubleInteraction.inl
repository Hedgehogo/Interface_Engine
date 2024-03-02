namespace ie {
	namespace make_system {
		template<typename T>
		BasicDoubleInteraction<T>::BasicDoubleInteraction(
			BoxPtr<IBasicInteraction<T> >&& first,
			BoxPtr<IBasicInteraction<T> >&& second
		) : first(std::move(first)), second(std::move(second)) {
		}
		
		template<typename T>
		auto BasicDoubleInteraction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicDoubleInteraction<T>* {
			return new ie::BasicDoubleInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicDoubleInteraction<T>::BasicDoubleInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		first_(make.first_->make(init_info)), second_(make.second_->make(init_info)) {
	}
	
	template<typename T>
	auto BasicDoubleInteraction<T>::get_first() -> IBasicInteraction<T>& {
		return *first_;
	}
	
	template<typename T>
	auto BasicDoubleInteraction<T>::get_first() const -> IBasicInteraction<T> const& {
		return *first_;
	}
	
	template<typename T>
	auto BasicDoubleInteraction<T>::get_second() -> IBasicInteraction<T>& {
		return *second_;
	}
	
	template<typename T>
	auto BasicDoubleInteraction<T>::get_second() const -> IBasicInteraction<T> const& {
		return *second_;
	}
	
	template<typename T>
	auto BasicDoubleInteraction<T>::start(sf::Vector2i mouse_position) -> void {
		first_->start_(mouse_position);
		second_->start_(mouse_position);
	}
	
	template<typename T>
	auto BasicDoubleInteraction<T>::update(sf::Vector2i mouse_position) -> void {
		first_->update(mouse_position);
		second_->update(mouse_position);
	}
	
	template<typename T>
	auto BasicDoubleInteraction<T>::finish(sf::Vector2i mouse_position) -> void {
		second_->finish(mouse_position);
		first_->finish(mouse_position);
	}
}
