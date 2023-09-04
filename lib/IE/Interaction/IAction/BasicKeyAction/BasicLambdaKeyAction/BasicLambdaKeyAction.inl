namespace ie {
	namespace make_system {
		template<typename T>
		BasicLambdaKeyAction<T>::BasicLambdaKeyAction(
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
		ie::BasicLambdaKeyAction<T>* BasicLambdaKeyAction<T>::make(BasicActionInitInfo<T> initInfo) {
			return new ie::BasicLambdaKeyAction<T>{std::move(*this), initInfo};
		}
	}
	
	template<typename T>
	BasicLambdaKeyAction<T>::BasicLambdaKeyAction(Make&& make, BasicActionInitInfo<T>) :
		startPressedLambda(make.startPressedLambda),
		whilePressedLambda(make.whilePressedLambda),
		stopPressedLambda(make.stopPressedLambda),
		whileNotPressedLambda(make.whileNotPressedLambda) {
	}
	
	template<typename T>
	BasicLambdaKeyAction<T>::BasicLambdaKeyAction(
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
	void BasicLambdaKeyAction<T>::startPressed() {
		startPressedLambda(this->mousePosition);
	}
	
	template<typename T>
	void BasicLambdaKeyAction<T>::stopPressed() {
		stopPressedLambda(this->mousePosition);
	}
	
	template<typename T>
	void BasicLambdaKeyAction<T>::whilePressed() {
		whilePressedLambda(this->mousePosition);
	}
	
	template<typename T>
	void BasicLambdaKeyAction<T>::whileNotPressed() {
		whileNotPressedLambda(this->mousePosition);
	}
	
	template<typename T>
	BasicLambdaKeyAction<T>* BasicLambdaKeyAction<T>::copy() {
		return new BasicLambdaKeyAction<T>{*this};
	}
}

