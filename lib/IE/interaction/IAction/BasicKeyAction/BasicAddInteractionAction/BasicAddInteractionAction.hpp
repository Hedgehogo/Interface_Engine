#pragma once

#include "../BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "../../../InteractionManager/InteractionManager.hpp"

namespace ie {
	template<typename T>
	class BasicAddInteractionAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicAddInteractionAction : public BasicKeyAction<T> {
			BoxPtr<IBasicInteraction<T>> interaction;
			
			BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
			
			ie::BasicAddInteractionAction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicAddInteractionAction : public BasicBaseKeyAction<T> {
	public:
		using Make = make_system::BasicAddInteractionAction<T>;
		
		BasicAddInteractionAction(Make&& make, BasicActionInitInfo<T> init_info);
		
		explicit BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction);
		
		void init(BasicActionInitInfo<T> init_info) override;
		
		IBasicInteraction<T>& get_interaction();
		
		BasicAddInteractionAction<T>* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		InteractionManager* interaction_manager_;
		BoxPtr<IBasicInteraction<T> > interaction_;
	};
	
	using AddInteractionAction = BasicAddInteractionAction<>;
}

#include "BasicAddInteractionAction.inl"