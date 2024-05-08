#pragma once

#include "../IBasicAction.hpp"
#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"

namespace ie {
	template<typename A_>
	class BasicStopActivityAction : public virtual IBasicAction<A_> {
	public:
		BasicStopActivityAction(BoxPtr<IBasicAction<A_> > action);
		
		auto start() -> void override;
		
		auto update(bool active) -> void override;
		
		auto finish() -> void override;
	
	protected:
		BoxPtr<IBasicAction<A_> > action;
		ActiveTracker tracker;
	};
}

#include "BasicStopActivityAction.inl"
