#pragma once

#include "../BaseLine.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class Underline : public BaseLine {
	public:
		struct MainLine : public BaseLine::MainLine{
			struct Make : public BaseLine::MainLine::Make {
				explicit Make(orl::Option<sf::Color> color = {});
				
				auto copy() ->Make* override;
				
				auto make(LineInitInfo init_info) -> MainLine* override;
			};
			
			float underline_offset_;
			float underline_thickness_;
			
			MainLine(Make&& make, LineInitInfo init_info);
			
			auto reinit(LineInitInfo init_info) -> void override;
			
			auto copy() -> MainLine* override;
			
			auto make() -> Underline* override;
		};
		
		Underline(MainLine&& main_line);
		
		auto resize(float start, float end, float height) -> void override;
		
		auto copy() const -> Underline* override;
	
	protected:
		float underline_offset_;
		float underline_thickness_;
	};
}

template<>
struct ieml::Decode<char, ie::Underline::MainLine::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Underline::MainLine::Make>;
};