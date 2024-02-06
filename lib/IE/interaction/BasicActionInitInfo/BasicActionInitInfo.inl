namespace ie {
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(
		sf::RenderWindow& window_,
		sf::RenderTarget& render_target_,
		DynBuffer& dyn_buffer,
		InteractionManager& interaction_manager_,
		IPanelManager& panel_manager_,
		T additional_
	) :
		window(window_),
		render_target(render_target_),
		dyn_buffer(dyn_buffer),
		interaction_manager(interaction_manager_),
		panel_manager(panel_manager_),
		additional(additional_) {
	}
	
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(ActionInitInfo init_info, T additional_) :
		BasicActionInitInfo(
			init_info.window,
			init_info.render_target,
			init_info.dyn_buffer,
			init_info.interaction_manager,
			init_info.panel_manager,
			additional_
		) {
	}
	
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(InitInfo init_info, T additional_) :
		BasicActionInitInfo(
			init_info.window,
			init_info.render_target,
			init_info.dyn_buffer,
			init_info.interaction_manager,
			init_info.panel_manager,
			additional_
		) {
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(sf::RenderWindow& window_) const {
		return {window_, render_target, interaction_manager, panel_manager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(sf::RenderTarget& render_target_) const {
		return {window, render_target_, dyn_buffer, interaction_manager, panel_manager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(DynBuffer& dyn_buffer_) const {
		return {window, render_target, dyn_buffer_, interaction_manager, panel_manager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(InteractionManager& interaction_manager_) const {
		return {window, render_target, dyn_buffer, interaction_manager_, panel_manager, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(IPanelManager& panel_manager_) const {
		return {window, render_target, dyn_buffer, interaction_manager, panel_manager_, additional};
	}
	
	template<typename T>
	BasicActionInitInfo<T> BasicActionInitInfo<T>::copy(T additional_) const {
		return {window, render_target, dyn_buffer, interaction_manager, panel_manager, additional_};
	}
	
	template<typename T>
	ActionInitInfo BasicActionInitInfo<T>::to_general() const {
		return {window, render_target, dyn_buffer, interaction_manager, panel_manager, {}};
	}
}
