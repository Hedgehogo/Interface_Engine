//included into BasicStopActivityAction.hpp

namespace ie {
	namespace make_system {
		template<typename A_>
		BasicStopActivityAction<A_>::BasicStopActivityAction(BoxPtr<IBasicAction<A_> >&& action) : action(std::move(action)) {
		}
		
		template<typename A_>
		auto BasicStopActivityAction<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::IBasicAction<A_>* {
			return new ie::BasicStopActivityAction<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicStopActivityAction<A_>::BasicStopActivityAction(Make&& make, BasicActionInitInfo<A_> init_info) : action(make.action->make(init_info)) {
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

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicStopActivityAction<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicStopActivityAction<A_> > {
	return {{node.at("action").except().as<ie::BoxPtr<ie::IBasicAction<A_> > >().except()}};
}
