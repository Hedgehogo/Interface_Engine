#pragma once

#include "../BasicFnInteraction/BasicFnInteraction.hpp"
#include "../IBasicMouseInteraction/IBasicMouseInteraction.hpp"

namespace ie {
	template<typename T>
	class BasicMouseFnInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicMouseFnInteraction : public BasicFnInteraction<T>, public virtual IBasicMouseInteraction<T> {
			using FnType = typename BasicFnInteraction<T>::FnType;
			
			BoxPtr<BasicKeyAction<T> > left_button_action;
			BoxPtr<BasicKeyAction<T> > right_button_action;
			
			BasicMouseFnInteraction() = default;
			
			BasicMouseFnInteraction(
				BoxPtr<BasicKeyAction<T> >&& left_button_action,
				BoxPtr<BasicKeyAction<T> >&& right_button_action,
				FnType start_fn,
				FnType finish_fn
			);
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicMouseFnInteraction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicMouseFnInteraction : public BasicFnInteraction<T>, public virtual IBasicMouseInteraction<T> {
	public:
		using FnType = typename BasicFnInteraction<T>::FnType;
		using Make = make_system::BasicMouseFnInteraction<T>;
		
		BasicMouseFnInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		auto get_left_button_action() -> BasicKeyAction<T>& override;
		
		auto get_left_button_action() const -> BasicKeyAction<T> const& override;
		
		auto get_right_button_action() -> BasicKeyAction<T>& override;
		
		auto get_right_button_action() const -> BasicKeyAction<T> const& override;
		
	protected:
		BoxPtr<BasicKeyAction<T> > left_button_action_;
		BoxPtr<BasicKeyAction<T> > right_button_action_;
	};
	
	using MouseFnInteraction = BasicMouseFnInteraction<>;
}

#include "BasicMouseFnInteraction.inl"