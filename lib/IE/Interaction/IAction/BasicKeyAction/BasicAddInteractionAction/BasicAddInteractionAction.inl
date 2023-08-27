namespace ie {
	template<typename T>
	BasicAddInteractionAction<T>::BasicAddInteractionAction(IBasicInteraction<T>& interaction) :
		interactionManager(nullptr), interaction(&interaction) {
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::init(BasicInteractionInitInfo<T> initInfo) {
		interactionManager = &initInfo.interactionManager;
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::setInteraction(IBasicInteraction<T>& interaction) {
		this->interaction = &interaction;
	}
	
	template<typename T>
	BasicAddInteractionAction<T>* BasicAddInteractionAction<T>::copy() {
		return new BasicAddInteractionAction<T>{*this};
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::startPressed() {
		interactionManager->addInteraction(*interaction);
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::stopPressed() {
		interactionManager->deleteInteraction(*interaction);
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::whilePressed() {
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::whileNotPressed() {
	}
}
