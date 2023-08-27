namespace ie {
	template<typename T>
	BasicBaseInteractiveData<T>::BasicBaseInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo initInfo, T additional) :
		interactionStack(&initInfo.interactionStack),
		interactionManager(&initInfo.interactionManager),
		interaction(std::move(interaction)),
		interact(false),
		oldInteract(false) {
		this->interaction->init({initInfo, additional});
	}
	
	template<typename T>
	BasicBaseInteractiveData<T>::BasicBaseInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction) :
		interactionStack(nullptr), interactionManager(nullptr), interaction(std::move(interaction)), interact(false), oldInteract(false) {
	}
	
	template<typename T>
	void BasicBaseInteractiveData<T>::init(InitInfo initInfo, T additional) {
		this->interactionStack = &initInfo.interactionStack;
		this->interactionManager = &initInfo.interactionManager;
		interaction->init({initInfo, additional});
	}
	
	template<typename T>
	void BasicBaseInteractiveData<T>::update() {
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
	void BasicBaseInteractiveData<T>::updateInteractions() {
		interact = true;
	}
	
	template<typename T>
	BasicBaseInteractive<T>::BasicBaseInteractive(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo initInfo, T additional) :
		interactive(std::move(interaction), initInfo, additional) {
		initInfo.updateManager.add(*this);
	}
	
	template<typename T>
	BasicBaseInteractive<T>::BasicBaseInteractive(BoxPtr<IBasicInteraction<T> >&& interaction) :
		interactive(std::move(interaction)) {
	}
	
	template<typename T>
	void BasicBaseInteractive<T>::init(InitInfo initInfo, T additional) {
		interactive.init(initInfo, additional);
		initInfo.updateManager.add(*this);
	}
	
	template<typename T>
	void BasicBaseInteractive<T>::update() {
		interactive.update();
	}
	
	template<typename T>
	bool BasicBaseInteractive<T>::updateInteractions(sf::Vector2f) {
		interactive.updateInteractions();
		return true;
	}
}
