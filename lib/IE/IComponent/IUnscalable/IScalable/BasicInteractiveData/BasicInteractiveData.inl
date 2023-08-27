namespace ie {
	template<typename T>
	BasicInteractiveData<T>::BasicInteractiveData(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction, InitInfo initInfo, T additional) :
		interactionStack(&initInfo.interactionStack),
		interactionManager(&initInfo.interactionManager),
		interaction(interaction->make({initInfo, additional})),
		interact(false),
		oldInteract(false) {
	}
	
	template<typename T>
	BasicInteractiveData<T>::BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo initInfo, T additional) :
		interactionStack(&initInfo.interactionStack),
		interactionManager(&initInfo.interactionManager),
		interaction(std::move(interaction)),
		interact(false),
		oldInteract(false) {
		this->interaction->init({initInfo, additional});
	}
	
	template<typename T>
	BasicInteractiveData<T>::BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction) :
		interactionStack(nullptr), interactionManager(nullptr), interaction(std::move(interaction)), interact(false), oldInteract(false) {
	}
	
	template<typename T>
	void BasicInteractiveData<T>::init(InitInfo initInfo, T additional) {
		this->interactionStack = &initInfo.interactionStack;
		this->interactionManager = &initInfo.interactionManager;
		interaction->init({initInfo, additional});
	}
	
	template<typename T>
	void BasicInteractiveData<T>::update() {
		if(interact != oldInteract) {
			oldInteract = interact;
			if(interact) {
				interactionManager->addInteraction(*interaction);
			} else {
				interactionManager->deleteInteraction(*interaction);
			}
		}
		interact = false;
	}
	
	template<typename T>
	void BasicInteractiveData<T>::updateInteractions() {
		interact = true;
	}
}
