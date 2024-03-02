#pragma once

#include "../BasePanel.hpp"

namespace ie {
	class ConstPanel : public BasePanel {
	public:
		struct Make : public virtual BasePanel::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<ISizing2::Make> sizing;
			BoxPtr<IPositioning2::Make> positioning;
			bool displayed = false;
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<ISizing2::Make> sizing, BoxPtr<IPositioning2::Make> positioning, bool displayed = false);
			
			auto make(InitInfo init_info) -> ConstPanel* override;
		};
		
		ConstPanel(Make&& make, InitInfo init_info);
		
		auto is_independent() -> bool override;
		
		auto is_free() -> bool override;
	};
}

template<>
struct ieml::Decode<char, ie::ConstPanel::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ConstPanel::Make>;
};
