namespace ie {
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(
		sf::RenderWindow& window_,
		sf::RenderTarget& render_target_,
		DynBuffer& dyn_buffer_,
		EventHandler& event_handler_,
		UpdateManager& update_manager_,
		TriggerManager& trigger_manager_,
		IPanelManager& panel_manager_,
		T additional_
	) :
		window(window_),
		render_target(render_target_),
		dyn_buffer(dyn_buffer_),
		event_handler(event_handler_),
		update_manager(update_manager_),
		trigger_manager(trigger_manager_),
		panel_manager(panel_manager_),
		additional(additional_) {
	}
	
	template<typename T>
	BasicActionInitInfo<T>::BasicActionInitInfo(ActionInitInfo init_info, T additional_) :
		BasicActionInitInfo(
			init_info.window,
			init_info.render_target,
			init_info.dyn_buffer,
			init_info.event_handler,
			init_info.update_manager,
			init_info.trigger_manager,
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
			init_info.event_handler,
			init_info.update_manager,
			init_info.trigger_manager,
			init_info.panel_manager,
			additional_
		) {
	}
	
	template<typename T>
	auto BasicActionInitInfo<T>::copy(sf::RenderWindow& window_) const -> BasicActionInitInfo<T> {
		return {window_, render_target, dyn_buffer, event_handler, update_manager, trigger_manager, panel_manager, additional};
	}
	
	template<typename T>
	auto BasicActionInitInfo<T>::copy(sf::RenderTarget& render_target_) const -> BasicActionInitInfo<T> {
		return {window, render_target_, dyn_buffer, event_handler, update_manager, trigger_manager, panel_manager, additional};
	}
	
	template<typename T>
	auto BasicActionInitInfo<T>::copy(DynBuffer& dyn_buffer_) const -> BasicActionInitInfo<T> {
		return {window, render_target, dyn_buffer_, event_handler, update_manager, trigger_manager, panel_manager, additional};
	}
	
	template<typename T>
	auto BasicActionInitInfo<T>::copy(EventHandler& event_handler_) const -> BasicActionInitInfo<T> {
		return {window, render_target, dyn_buffer, event_handler_, update_manager, trigger_manager, panel_manager, additional};
	}
	
	template<typename T>
	auto BasicActionInitInfo<T>::copy(UpdateManager& update_manager_) const -> BasicActionInitInfo<T> {
		return {window, render_target, dyn_buffer, event_handler, update_manager_, trigger_manager, panel_manager, additional};
	}
	
	template<typename T>
	auto BasicActionInitInfo<T>::copy(TriggerManager& trigger_manager_) const -> BasicActionInitInfo<T> {
		return {window, render_target, dyn_buffer, event_handler, update_manager, trigger_manager_, panel_manager, additional};
	}
	
	template<typename T>
	auto BasicActionInitInfo<T>::copy(IPanelManager& panel_manager_) const -> BasicActionInitInfo<T> {
		return {window, render_target, dyn_buffer, event_handler, update_manager, trigger_manager, panel_manager_, additional};
	}
	
	template<typename T>
	auto BasicActionInitInfo<T>::copy(T additional_) const -> BasicActionInitInfo<T> {
		return {window, render_target, dyn_buffer, event_handler, update_manager, trigger_manager, panel_manager, additional_};
	}
	
	template<typename T>
	auto BasicActionInitInfo<T>::to_general() const -> ActionInitInfo {
		return {window, render_target, dyn_buffer, event_handler, update_manager, trigger_manager, panel_manager, {}};
	}
}
