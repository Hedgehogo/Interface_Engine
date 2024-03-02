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
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicDoubleInteraction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicDoubleInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicDoubleInteraction<T>;
		
		BasicDoubleInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		auto get_first() -> IBasicInteraction<T>&;
		
		auto get_first() const -> IBasicInteraction<T> const&;
		
		auto get_second() -> IBasicInteraction<T>&;
		
		auto get_second() const -> IBasicInteraction<T> const&;
		
		auto start(sf::Vector2i mouse_position) -> void override;
		
		auto update(sf::Vector2i mouse_position) -> void override;
		
		auto finish(sf::Vector2i mouse_position) -> void override;
		
	protected:
		BoxPtr<IBasicInteraction<T> > first_;
		BoxPtr<IBasicInteraction<T> > second_;
	};
	
	using DoubleInteraction = BasicDoubleInteraction<>;
}

#include "BasicDoubleInteraction.inl"
