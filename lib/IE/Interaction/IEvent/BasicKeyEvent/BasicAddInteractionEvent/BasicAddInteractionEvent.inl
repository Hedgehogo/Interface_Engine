namespace ui {
	template<typename T>
	BasicAddInteractionEvent<T>::BasicAddInteractionEvent(IBasicInteraction<T>& interaction) :
		interactionManager(nullptr), interaction(&interaction) {
	}
	
	template<typename T>
	void BasicAddInteractionEvent<T>::init(BasicInteractionInitInfo<T> initInfo) {
		interactionManager = &initInfo.interactionManager;
	}
	
	template<typename T>
	void BasicAddInteractionEvent<T>::setInteraction(IBasicInteraction<T>& interaction) {
		this->interaction = &interaction;
	}
	
	template<typename T>
	BasicAddInteractionEvent<T>* BasicAddInteractionEvent<T>::copy() {
		return new BasicAddInteractionEvent<T>{*this};
	}
	
	template<typename T>
	void BasicAddInteractionEvent<T>::startPressed() {
		interactionManager->addInteraction(*interaction);
	}
	
	template<typename T>
	void BasicAddInteractionEvent<T>::stopPressed() {
		interactionManager->deleteInteraction(*interaction);
	}
	
	template<typename T>
	void BasicAddInteractionEvent<T>::whilePressed() {
	}
	
	template<typename T>
	void BasicAddInteractionEvent<T>::whileNotPressed() {
	}
}
