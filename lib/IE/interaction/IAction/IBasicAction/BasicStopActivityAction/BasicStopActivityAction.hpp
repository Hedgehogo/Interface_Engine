#pragma once

#include "../IBasicAction.hpp"
#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"

namespace ie {
	template<typename A_>
	class BasicStopActivityAction;
	
	namespace make_system {
		template<typename A_>
		struct BasicStopActivityAction : public virtual IBasicAction<A_> {
			BoxPtr<IBasicAction<A_> > action;
			
			BasicStopActivityAction(BoxPtr<IBasicAction<A_> >&& action);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::IBasicAction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicStopActivityAction : public virtual IBasicAction<A_> {
	public:
		using Make = make_system::BasicStopActivityAction<A_>;
		
		BasicStopActivityAction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto start() -> void override;
		
		auto update(bool active) -> void override;
		
		auto finish() -> void override;
	
	protected:
		BoxPtr<IBasicAction<A_> > action;
		ActiveTracker tracker;
	};
	
	using StopActivityAction = BasicStopActivityAction<>;
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicStopActivityAction<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicStopActivityAction<A_> >;
};

#include "BasicStopActivityAction.inl"
