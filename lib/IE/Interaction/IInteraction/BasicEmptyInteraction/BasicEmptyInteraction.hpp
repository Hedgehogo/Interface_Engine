#pragma once

#include "../IInteraction.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicEmptyInteraction : public virtual IBasicInteraction<T> {
	public:
		BasicEmptyInteraction();
		
		void start(sf::Vector2i) override;
		
		void update(sf::Vector2i) override;
		
		void finish(sf::Vector2i) override;
		
		BasicEmptyInteraction<T>* copy() override;
	};
	
	using EmptyInteraction = BasicEmptyInteraction<>;
	
	template<typename T>
	struct DecodePointer<BasicEmptyInteraction<T> > {
		static bool decodePointer(const YAML::Node&, BasicEmptyInteraction<T>*& emptyInteraction);
	};
}

#include "BasicEmptyInteraction.inl"