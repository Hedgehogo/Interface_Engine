#pragma once

#include "../BaseLine.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class StrikeThrough : public BaseLine {
	public:
		struct MainLine: public BaseLine::MainLine {
			struct Make : public BaseLine::MainLine::Make {
				orl::Option<sf::Color> color = {};
				float strike_through_coefficient;
				
				Make(orl::Option<sf::Color> color = {}, float strike_through_coefficient = 0.3);
				
				auto copy() -> Make* override;
				
				auto make(LineInitInfo init_info) -> MainLine* override;
			};
			
			float strike_through_coefficient;
			float strike_through_offset;
			float underline_thickness;
			
			MainLine(Make&& make, LineInitInfo init_info);
			
			auto reinit(LineInitInfo init_info) -> void override;
			
			auto copy() -> MainLine* override;
			
			auto make() -> StrikeThrough* override;
		};
		
		StrikeThrough(MainLine&& main_line);

		auto resize(float start, float end, float height) -> void override;
		
		auto copy() const -> StrikeThrough* override;
	
	protected:
		float strike_through_offset_;
		float underline_thickness_;
	};
}

template<>
struct ieml::Decode<char, ie::StrikeThrough::MainLine::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::StrikeThrough::MainLine::Make>;
};