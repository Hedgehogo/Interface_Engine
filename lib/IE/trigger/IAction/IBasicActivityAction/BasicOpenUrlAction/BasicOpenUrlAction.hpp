#pragma once

#include <string>
#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "../IBasicActivityAction.hpp"

namespace ie {
	template<typename A_>
	class BasicOpenUrlAction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicOpenUrlAction : public virtual IBasicActivityAction<A_> {
			std::string url;
			
			BasicOpenUrlAction(std::string url);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicOpenUrlAction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicOpenUrlAction : public virtual IBasicActivityAction<A_> {
	public:
		using Make = make_system::BasicOpenUrlAction<A_>;
		
		BasicOpenUrlAction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		BasicOpenUrlAction(std::string url);
		
		auto update(bool active) -> void override;
	
	protected:
		std::string url_;
	};
	
	using OpenUrlAction = BasicOpenUrlAction<>;
	
	auto determine_url(ieml::Node const& node) -> bool;
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicOpenUrlAction<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicOpenUrlAction<A_> >;
};

#include "BasicOpenUrlAction.inl"