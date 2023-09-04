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
			
			ie::BasicDoubleInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicDoubleInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicDoubleInteraction<T>;
		
		BasicDoubleInteraction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicDoubleInteraction(BoxPtr<IBasicInteraction<T> >&& first, BoxPtr<IBasicInteraction<T> >&& second);
		
		void setFirst(BoxPtr<IBasicInteraction<T> >&& first);
		
		void setSecond(BoxPtr<IBasicInteraction<T> >&& second);
		
		IBasicInteraction<T>& getFirst();
		
		const IBasicInteraction<T>& getFirst() const;
		
		IBasicInteraction<T>& getSecond();
		
		const IBasicInteraction<T>& getSecond() const;
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		BasicDoubleInteraction<T>* copy() override;
	
	protected:
		BoxPtr<IBasicInteraction<T> > first;
		BoxPtr<IBasicInteraction<T> > second;
	};
	
	using DoubleInteraction = BasicDoubleInteraction<>;
}

#include "BasicDoubleInteraction.inl"
