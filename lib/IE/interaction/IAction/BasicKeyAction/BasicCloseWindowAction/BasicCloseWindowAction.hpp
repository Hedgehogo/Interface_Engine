#pragma once

#include "../BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	template<typename T>
	class BasicCloseWindowAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicCloseWindowAction : public BasicKeyAction<T> {
			ie::BasicCloseWindowAction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicCloseWindowAction : public BasicBaseKeyAction<T> {
	public:
		using Make = make_system::BasicCloseWindowAction<T>;
		
		BasicCloseWindowAction(Make&& make, BasicActionInitInfo<T> init_info);
		
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		sf::RenderWindow* window_;
	};
	
	using CloseWindowAction = BasicCloseWindowAction<std::monostate>;
	
	template<typename T>
	struct DecodePointer<BasicCloseWindowAction<T> > {
		static bool decode_pointer(const YAML::Node&, BasicCloseWindowAction<T>*& close_window_action);
	};
}

#include "BasicCloseWindowAction.inl"