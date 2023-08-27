namespace ie {
	template<typename T>
	BasicLambdaInteraction<T>::Make::Make(void (* startPointing)(sf::Vector2i), void (* finishPointing)(sf::Vector2i)) :
		startPointing(startPointing), finishPointing(finishPointing) {
	}
	
	template<typename T>
	BasicLambdaInteraction<T>* BasicLambdaInteraction<T>::Make::make(BasicActionInitInfo<T> initInfo) {
		return new BasicLambdaInteraction<T>{std::move(*this), initInfo};
	}
	
	template<typename T>
	BasicLambdaInteraction<T>::BasicLambdaInteraction(Make&& make, BasicActionInitInfo<T>) :
		startPointing(make.startPointing), finishPointing(make.finishPointing) {
	}
	
	template<typename T>
	BasicLambdaInteraction<T>::BasicLambdaInteraction(void (* startPointing)(sf::Vector2i mousePosition), void (* finishPointing)(sf::Vector2i mousePosition)) :
		startPointing(startPointing), finishPointing(finishPointing) {
	}
	
	template<typename T>
	void BasicLambdaInteraction<T>::start(sf::Vector2i mousePosition) {
		startPointing(mousePosition);
	}
	
	template<typename T>
	void BasicLambdaInteraction<T>::finish(sf::Vector2i mousePosition) {
		finishPointing(mousePosition);
	}
}
