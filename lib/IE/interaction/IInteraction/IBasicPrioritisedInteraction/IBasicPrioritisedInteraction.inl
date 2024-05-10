namespace ie {
	template<typename A_>
	auto IBasicPrioritisedInteraction<A_>::is_prioritised() const -> bool {
		return true;
	}
	
	/*old_action
	template<typename A_>
	auto IBasicPrioritisedInteraction<A_>::handle_event_prioritised(Event event) -> bool {
		return handle_event(event);
	}
	*/
}
