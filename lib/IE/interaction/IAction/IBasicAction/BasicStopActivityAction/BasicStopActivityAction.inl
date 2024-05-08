//included into BasicStopActivityAction.hpp

namespace ie {
	template<typename A_>
	BasicStopActivityAction<A_>::BasicStopActivityAction(BoxPtr<IBasicAction<A_> > action) : action(std::move(action)) {
	}
	
	template<typename A_>
	auto BasicStopActivityAction<A_>::start() -> void {
		action->start();
	}
	
	template<typename A_>
	auto BasicStopActivityAction<A_>::update(bool active) -> void {
		action->update(tracker.update(active).stopped());
	}
	
	template<typename A_>
	auto BasicStopActivityAction<A_>::finish() -> void {
		action->finish();
	}
}
