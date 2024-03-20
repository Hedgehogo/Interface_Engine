namespace ie {
	template<size_t size_>
	ArrayException<size_>::ArrayException(ieml::Mark mark) : NodeException(mark) {
	}
	
	template<size_t size_>
	auto ArrayException<size_>::get_description() const -> ieml::String{
		return std::string("The array size must be equal to ") + std::to_string(size_);
	}
	
	template<size_t size_>
	auto ArrayException<size_>::clone() const -> ArrayException<size_>*{
		return new ArrayException{*this};
	}
}