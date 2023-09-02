namespace ie {
	template<typename T>
	BasicAddInteractionAction<T>::Make::Make(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction) :
		interaction(std::move(interaction)) {
	}
	
	template<typename T>
	BasicAddInteractionAction<T>* BasicAddInteractionAction<T>::Make::make(BasicActionInitInfo<T> initInfo) {
		return new BasicAddInteractionAction<T>{std::move(*this), initInfo};
	}
	
	template<typename T>
	BasicAddInteractionAction<T>::BasicAddInteractionAction(Make&& make, BasicActionInitInfo<T> initInfo) :
		interactionManager(&initInfo.interactionManager), interaction(make.interaction->make(initInfo)) {
	}
	
	template<typename T>
	BasicAddInteractionAction<T>::BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction) :
		interactionManager(nullptr), interaction(std::move(interaction)) {
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::init(BasicActionInitInfo<T> initInfo) {
		interactionManager = &initInfo.interactionManager;
		interaction->init(initInfo);
	}
	
	template<typename T>
	IBasicInteraction<T>& BasicAddInteractionAction<T>::getInteraction() {
		return *interaction;
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
