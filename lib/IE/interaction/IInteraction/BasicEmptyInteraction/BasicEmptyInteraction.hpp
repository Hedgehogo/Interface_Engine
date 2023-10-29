#pragma once

#include "../IInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	template<typename T>
	class BasicEmptyInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicEmptyInteraction : public virtual IBasicInteraction<T> {
			ie::BasicEmptyInteraction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicEmptyInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicEmptyInteraction<T>;
		
		BasicEmptyInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicEmptyInteraction();
		
		void start(sf::Vector2i) override;
		
		void update(sf::Vector2i) override;
		
		void finish(sf::Vector2i) override;
		
		BasicEmptyInteraction<T>* copy() override;
	};
	
	using EmptyInteraction = BasicEmptyInteraction<>;
	
	template<typename T>
	struct DecodePointer<BasicEmptyInteraction<T> > {
		static bool decode_pointer(const YAML::Node&, BasicEmptyInteraction<T>*& empty_interaction);
	};
}

#include "BasicEmptyInteraction.inl"