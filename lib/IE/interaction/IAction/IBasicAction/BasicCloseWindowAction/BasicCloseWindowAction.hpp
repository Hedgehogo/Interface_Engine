#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IBasicAction.hpp"

namespace ie {
	template<typename A_>
	class BasicCloseWindowAction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicCloseWindowAction : public virtual IBasicAction<A_> {
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicCloseWindowAction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicCloseWindowAction : public virtual IBasicAction<A_> {
	public:
		using Make = make_system::BasicCloseWindowAction<A_>;
		
		BasicCloseWindowAction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto update(bool active) -> void override;
	
	protected:
		sf::RenderWindow* window_;
	};
	
	using CloseWindowAction = BasicCloseWindowAction<std::monostate>;
}

template<typename A_>
struct ieml::Decode<char, ie::BasicCloseWindowAction<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BasicCloseWindowAction<A_> >;
};

#include "BasicCloseWindowAction.inl"
