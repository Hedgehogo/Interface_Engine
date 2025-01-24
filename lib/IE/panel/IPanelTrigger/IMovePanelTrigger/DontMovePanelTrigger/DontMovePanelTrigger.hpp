#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/trigger/ITrigger/BasicEmptyTrigger/BasicEmptyTrigger.hpp"
#include "../IMovePanelTrigger.hpp"

namespace ie {
	class DontMovePanelTrigger : public virtual IMovePanelTrigger {
	public:
		struct Make : public virtual IMovePanelTrigger::Make {
			auto make(PanelActionInitInfo init_info) -> DontMovePanelTrigger* override;
		};
		
		DontMovePanelTrigger(Make&& make, PanelActionInitInfo init_info);
		
		DontMovePanelTrigger() = default;
		
		auto set_panel(Panel&) -> void override;
		
		auto move(sf::Vector2i) -> void override;
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
	};
}

template<>
struct ieml::Decode<char, ie::DontMovePanelTrigger::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::DontMovePanelTrigger::Make>;
};
