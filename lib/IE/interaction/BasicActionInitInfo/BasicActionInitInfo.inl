namespace ie {
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(
		sf::RenderWindow& window_,
		sf::RenderTarget& render_target_,
		InteractionManager& interaction_manager_,
		InteractionStack& interaction_stack_,
		IPanelManager& panel_manager_,
		T additional_
	) :
		window(window_),
		render_target(render_target_),
		interaction_manager(interaction_manager_),
		interaction_stack(interaction_stack_),
		panel_manager(panel_manager_),
		additional(additional_){
	}
	
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(ActionInitInfo init_info, T additional_) :
		BasicActionInitInfo(init_info.window, init_info.render_target, init_info.interaction_manager, init_info.interaction_stack, init_info.panel_manager, additional_) {
	}
	
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(InitInfo init_info, T additional_) :
		BasicActionInitInfo(init_info.window, init_info.render_target, init_info.interaction_manager, init_info.interaction_stack, init_info.panel_manager, additional_) {
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(sf::RenderWindow& window_) const {
		return {window_, render_target, interaction_manager, interaction_stack, panel_manager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(sf::RenderTarget& render_target_) const {
		return {window, render_target_, interaction_manager, interaction_stack, panel_manager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(InteractionManager& interaction_manager_) const {
		return {window, render_target, interaction_manager_, interaction_stack, panel_manager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(InteractionStack& interaction_stack_) const {
		return {window, render_target, interaction_manager, interaction_stack_, panel_manager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(IPanelManager& panel_manager_) const {
		return {window, render_target, interaction_manager, interaction_stack, panel_manager_, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(T additional_) const {
		return {window, render_target, interaction_manager, interaction_stack, panel_manager, additional_};
	}
	
	template<typename T>
	ActionInitInfo BasicActionInitInfo<T>::to_general() const {
		return {window, render_target, interaction_manager, interaction_stack, panel_manager, {}};
	}
}
