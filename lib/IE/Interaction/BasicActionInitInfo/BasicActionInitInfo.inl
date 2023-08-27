namespace ie {
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(
		sf::RenderWindow& window_,
		sf::RenderTarget& renderTarget_,
		InteractionManager& interactionManager_,
		InteractionStack& interactionStack_,
		IPanelManager& panelManager_,
		T additional_
	) :
		window(window_),
		renderTarget(renderTarget_),
		interactionManager(interactionManager_),
		interactionStack(interactionStack_),
		panelManager(panelManager_),
		additional(additional_){
	}
	
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(ActionInitInfo initInfo, T additional_) :
		BasicActionInitInfo(initInfo.window, initInfo.renderTarget, initInfo.interactionManager, initInfo.interactionStack, initInfo.panelManager, additional_) {
	}
	
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(InitInfo initInfo, T additional_) :
		BasicActionInitInfo(initInfo.window, initInfo.renderTarget, initInfo.interactionManager, initInfo.interactionStack, initInfo.panelManager, additional_) {
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(sf::RenderWindow& window_) const {
		return {window_, renderTarget, interactionManager, interactionStack, panelManager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(sf::RenderTarget& renderTarget_) const {
		return {window, renderTarget_, interactionManager, interactionStack, panelManager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(InteractionManager& interactionManager_) const {
		return {window, renderTarget, interactionManager_, interactionStack, panelManager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(InteractionStack& interactionStack_) const {
		return {window, renderTarget, interactionManager, interactionStack_, panelManager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(IPanelManager& panelManager_) const {
		return {window, renderTarget, interactionManager, interactionStack, panelManager_, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(T additional_) const {
		return {window, renderTarget, interactionManager, interactionStack, panelManager, additional_};
	}
	
	template<typename T>
	ActionInitInfo BasicActionInitInfo<T>::toGeneral() const {
		return {window, renderTarget, interactionManager, interactionStack, panelManager, {}};
	}
}
