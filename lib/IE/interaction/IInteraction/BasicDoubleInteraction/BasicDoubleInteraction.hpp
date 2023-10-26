#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T>
	class BasicDoubleInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicDoubleInteraction : public virtual IBasicInteraction<T> {
			BoxPtr<IBasicInteraction<T> > first;
			BoxPtr<IBasicInteraction<T> > second;
			
			BasicDoubleInteraction(
				BoxPtr<IBasicInteraction<T> >&& first,
				BoxPtr<IBasicInteraction<T> >&& second
			);
			
			ie::BasicDoubleInteraction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicDoubleInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicDoubleInteraction<T>;
		
		BasicDoubleInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicDoubleInteraction(BoxPtr<IBasicInteraction<T> >&& first, BoxPtr<IBasicInteraction<T> >&& second);
		
		void set_first(BoxPtr<IBasicInteraction<T> >&& first);
		
		void set_second(BoxPtr<IBasicInteraction<T> >&& second);
		
		IBasicInteraction<T>& get_first();
		
		const IBasicInteraction<T>& get_first() const;
		
		IBasicInteraction<T>& get_second();
		
		const IBasicInteraction<T>& get_second() const;
		
		void start(sf::Vector2i mouse_position) override;
		
		void update(sf::Vector2i mouse_position) override;
		
		void finish(sf::Vector2i mouse_position) override;
		
		BasicDoubleInteraction<T>* copy() override;
	
	protected:
		BoxPtr<IBasicInteraction<T> > first_;
		BoxPtr<IBasicInteraction<T> > second_;
	};
	
	using DoubleInteraction = BasicDoubleInteraction<>;
}

#include "BasicDoubleInteraction.inl"
