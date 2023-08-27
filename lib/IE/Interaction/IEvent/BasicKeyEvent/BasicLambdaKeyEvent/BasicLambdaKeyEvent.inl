namespace ie {
	template<typename T>
	BasicLambdaKeyEvent<T>::BasicLambdaKeyEvent(
		void (* startPressedLambda)(sf::Vector2i),
		void (* whilePressedLambda)(sf::Vector2i),
		void (* stopPressedLambda)(sf::Vector2i),
		void (* whileNotPressedLambda)(sf::Vector2i)
	) :
		startPressedLambda(startPressedLambda),
		whilePressedLambda(whilePressedLambda),
		stopPressedLambda(stopPressedLambda),
		whileNotPressedLambda(whileNotPressedLambda) {
	}
	
	template<typename T>
	void BasicLambdaKeyEvent<T>::startPressed() {
		startPressedLambda(this->mousePosition);
	}
	
	template<typename T>
	void BasicLambdaKeyEvent<T>::stopPressed() {
		stopPressedLambda(this->mousePosition);
	}
	
	template<typename T>
	void BasicLambdaKeyEvent<T>::whilePressed() {
		whilePressedLambda(this->mousePosition);
	}
	
	template<typename T>
	void BasicLambdaKeyEvent<T>::whileNotPressed() {
		whileNotPressedLambda(this->mousePosition);
	}
	
	template<typename T>
	BasicLambdaKeyEvent<T>* BasicLambdaKeyEvent<T>::copy() {
		return new BasicLambdaKeyEvent<T>{*this};
	}
}

