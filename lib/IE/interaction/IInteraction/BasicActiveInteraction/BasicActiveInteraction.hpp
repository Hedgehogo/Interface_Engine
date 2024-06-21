#pragma once

#include "../../InteractionManager/InteractionManager.hpp"
#include "../IBasicPrioritisedInteraction/IBasicPrioritisedInteraction.hpp"

namespace ie {
	template<typename A_>
	class BasicActiveInteraction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicActiveInteraction : public virtual IBasicPrioritisedInteraction<A_> {
			BoxPtr<IBasicInteraction<A_> > interaction;
			
			BasicActiveInteraction(BoxPtr<IBasicInteraction<A_> >&& interaction);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicActiveInteraction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicActiveInteraction : public virtual IBasicPrioritisedInteraction<A_> {
	public:
		using Make = make_system::BasicActiveInteraction<A_>;
		
		BasicActiveInteraction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto handle_event_prioritised(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
		
	private:
		BoxPtr<IBasicInteraction<A_> > interaction_;
		InteractionManager* interaction_manager_;
		bool prioritised_;
		bool active_;
	};
	
	using ActiveInteraction = BasicActiveInteraction<>;
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicActiveInteraction<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicActiveInteraction<A_> >;
};

#include "BasicActiveInteraction.inl"
