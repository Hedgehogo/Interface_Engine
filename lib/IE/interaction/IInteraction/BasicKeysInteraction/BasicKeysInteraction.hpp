#pragma once

#include "../IInteraction.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	template<typename T>
	class BasicKeysInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicKeysInteraction : public virtual IBasicInteraction<T> {
			BoxPtr<typename ie::BasicKeyAction<T>::Make > action;
			std::vector<Key> keys;
			std::vector<Key> black_list_keys = {};
			
			BasicKeysInteraction(BoxPtr<typename ie::BasicKeyAction<T>::Make >&& action, std::vector<Key> keys, std::vector<Key> black_list_keys = {});
			
			ie::BasicKeysInteraction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicKeysInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicKeysInteraction<T>;
		
		BasicKeysInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicKeysInteraction(BoxPtr<BasicKeyAction<T> >&& action, std::vector<Key> keys, std::vector<Key> black_list_keys = {});
		
		void init(BasicActionInitInfo<T> init_info) override;
		
		bool is_press() const;
		
		std::vector<Key> get_keys();
		
		BasicKeyAction<T>* get_action();
		
		void set_action(BasicKeyAction<T>* action);
		
		void start(sf::Vector2i mouse_position) override;
		
		void update(sf::Vector2i mouse_position) override;
		
		void finish(sf::Vector2i) override;
		
		BasicKeysInteraction<T>* copy() override;
		
	protected:
		BoxPtr<BasicKeyAction<T> > action;
		std::vector<Key> keys;
		std::vector<Key> black_list_keys;
		bool press;
	};
	
	using KeysInteraction = BasicKeysInteraction<>;
	
	template<typename T>
	struct DecodePointer<BasicKeysInteraction<T> > {
		static bool decode_pointer(const YAML::Node& node, BasicKeysInteraction<T>*& keys_interaction);
	};
}

#include "BasicKeysInteraction.inl"