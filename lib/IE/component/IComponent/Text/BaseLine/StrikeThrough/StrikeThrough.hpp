#pragma once

#include "../BaseLine.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class StrikeThrough : public BaseLine {
	public:
		struct Make : public BaseLine::Make {
			orl::Option<sf::Color> color = {};
			float strike_through_offset;
			
			Make(orl::Option<sf::Color> color = {}, float strike_through_offset = 0.3);
			
			auto copy() ->Make* override;
			
			auto make(LineInitInfo init_info) -> BaseLine* override;
		};
		
		StrikeThrough(Make&& make, LineInitInfo init_info);

		auto resize(float start, float end, float height) -> void override;
		
		auto copy() const -> StrikeThrough* override;
	
	protected:
		float strike_through_offset_;
		float underline_thickness_;
	};
}

template<>
struct ieml::Decode<char, ie::StrikeThrough::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::StrikeThrough::Make>;
};