#pragma once

#include "../IInteraction.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	template<typename T>
	class BasicOneKeyInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicOneKeyInteraction : public virtual IBasicInteraction<T> {
			BoxPtr<BasicKeyAction<T> > action;
			Key key;
			
			BasicOneKeyInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key);
			
			ie::BasicOneKeyInteraction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicOneKeyInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicOneKeyInteraction<T>;
		
		BasicOneKeyInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicOneKeyInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key);
		
		void init(BasicActionInitInfo<T> init_info) override;
		
		Key get_key();
		
		BasicKeyAction<T>& get_action();
		
		const BasicKeyAction<T>& get_action() const;
		
		void set_action(BoxPtr<BasicKeyAction<T> >&& action);
		
		void start(sf::Vector2i mouse_position) override;
		
		void update(sf::Vector2i mouse_position) override;
		
		void finish(sf::Vector2i) override;
		
		BasicOneKeyInteraction<T>* copy() override;
	
	protected:
		BoxPtr<BasicKeyAction<T> > action;
		Key key;
	};
	
	using OneKeyInteraction = BasicOneKeyInteraction<>;
	
	template<typename T>
	struct DecodePointer<BasicOneKeyInteraction<T> > {
		static bool decode_pointer(const YAML::Node& node, BasicOneKeyInteraction<T>*& one_key_interaction);
	};
}

#include "BasicOneKeyInteraction.inl"