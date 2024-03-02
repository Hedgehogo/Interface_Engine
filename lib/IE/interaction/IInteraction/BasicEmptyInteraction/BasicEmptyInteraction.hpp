#pragma once

#include "../IInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	template<typename T>
	class BasicEmptyInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicEmptyInteraction : public virtual IBasicInteraction<T> {
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicEmptyInteraction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicEmptyInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicEmptyInteraction<T>;
		
		BasicEmptyInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicEmptyInteraction();
		
		auto start(sf::Vector2i) -> void override;
		
		auto update(sf::Vector2i) -> void override;
		
		auto finish(sf::Vector2i) -> void override;
	};
	
	using EmptyInteraction = BasicEmptyInteraction<>;
	
	template<typename T>
	struct DecodePointer<BasicEmptyInteraction<T> > {
		static auto decode_pointer(const YAML::Node&, BasicEmptyInteraction<T>*& empty_interaction) -> bool;
	};
}

#include "BasicEmptyInteraction.inl"