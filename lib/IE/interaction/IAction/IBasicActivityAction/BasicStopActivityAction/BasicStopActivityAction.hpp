#pragma once

#include "../IBasicActivityAction.hpp"
#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"

namespace ie {
	template<typename A_>
	class BasicStopActivityAction;
	
	namespace make_system {
		template<typename A_>
		struct BasicStopActivityAction : public virtual IBasicActivityAction<A_> {
			BoxPtr<IBasicActivityAction<A_> > action;
			
			BasicStopActivityAction(BoxPtr<IBasicActivityAction<A_> >&& action);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::IBasicActivityAction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicStopActivityAction : public virtual IBasicActivityAction<A_> {
	public:
		using Make = make_system::BasicStopActivityAction<A_>;
		
		BasicStopActivityAction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto start() -> void override;
		
		auto update(bool active) -> void override;
		
		auto finish() -> void override;
	
	protected:
		BoxPtr<IBasicActivityAction<A_> > action;
		ActiveTracker tracker;
	};
	
	using StopActivityAction = BasicStopActivityAction<>;
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicStopActivityAction<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicStopActivityAction<A_> >;
};

#include "BasicStopActivityAction.inl"
