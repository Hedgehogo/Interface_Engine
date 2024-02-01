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
			
			ConstPanel* make(InitInfo init_info) override;
		};
		
		ConstPanel(Make&& make, InitInfo init_info);
		
		bool is_independent() override;
		
		bool is_free() override;
	};
}

template<>
struct ieml::Decode<char, ie::ConstPanel::Make> {
	static orl::Option<ie::ConstPanel::Make> decode(ieml::Node const& node);
};
