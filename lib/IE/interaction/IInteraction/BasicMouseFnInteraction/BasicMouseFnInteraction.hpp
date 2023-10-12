#pragma once

#include "IE/Interaction/IInteraction/BasicFnInteraction/BasicFnInteraction.hpp"
#include "../IBasicMouseInteraction/IBasicMouseInteraction.hpp"

namespace ie {
	template<typename T>
	class BasicMouseFnInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicMouseFnInteraction : public BasicFnInteraction<T>, public virtual IBasicMouseInteraction<T> {
			using FnType = typename BasicFnInteraction<T>::FnType;
			
			BoxPtr<BasicKeyAction<T> > leftButtonAction;
			BoxPtr<BasicKeyAction<T> > rightButtonAction;
			
			BasicMouseFnInteraction() = default;
			
			BasicMouseFnInteraction(
				BoxPtr<BasicKeyAction<T> >&& leftButtonAction,
				BoxPtr<BasicKeyAction<T> >&& rightButtonAction,
				FnType startFn,
				FnType finishFn
			);
			
			ie::BasicMouseFnInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicMouseFnInteraction : public BasicFnInteraction<T>, public virtual IBasicMouseInteraction<T> {
	public:
		using FnType = typename BasicFnInteraction<T>::FnType;
		using Make = make_system::BasicMouseFnInteraction<T>;
		
		BasicMouseFnInteraction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicMouseFnInteraction(
			BoxPtr<BasicKeyAction<T> >&& leftButtonAction,
			BoxPtr<BasicKeyAction<T> >&& rightButtonAction,
			FnType startFn,
			FnType finishFn
		);
		
		BasicKeyAction<T>& getLeftButtonAction() override;
		
		const BasicKeyAction<T>& getLeftButtonAction() const override;
		
		BasicKeyAction<T>& getRightButtonAction() override;
		
		const BasicKeyAction<T>& getRightButtonAction() const override;
		
		BasicMouseFnInteraction<T>* copy() override;
	
		static BasicMouseFnInteraction debug;
		
	protected:
		BoxPtr<BasicKeyAction<T> > leftButtonAction;
		BoxPtr<BasicKeyAction<T> > rightButtonAction;
	};
	
	using MouseFnInteraction = BasicMouseFnInteraction<>;
}

#include "BasicMouseFnInteraction.inl"
