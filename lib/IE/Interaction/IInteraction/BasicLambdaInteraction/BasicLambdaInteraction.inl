namespace ui {
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
