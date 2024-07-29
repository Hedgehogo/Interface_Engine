#include "TextStyle.hpp"

#include "../BaseLine/StrikeThrough/StrikeThrough.hpp"
#include "../BaseLine/Underline/Underline.hpp"
#include "IE/initialization/make/make.hpp"

namespace ie {
	TextStyleParameterException::TextStyleParameterException(
		std::string const& name
	) : 
		str(
			"it is not possible you maintain `" + 
			name + 
			"` because you have not specified a base style or you have not specified `" + 
			name + 
			"` explicitly"
		) {
	}
	
	auto TextStyleParameterException::what() const noexcept -> char const* {
		return str.c_str();
	}
	
	template<typename T>
	auto get_param(
		orl::Option<TextStyle> const& base,
		orl::Option<T> const& param,
		std::string const& name,
		std::function<T const&(TextStyle const&)> fn
	) -> const T& {
		return param.some_or_else([&fn, &base, &name]{
			return fn(base.except(TextStyleParameterException{name}));
		});
	}
	
	
	TextStyle::TextStyle(
		orl::Option<TextStyle> const& base_stile,
		orl::Option<sf::Color> const& text_color,
		orl::Option<sf::Color> const& text_selection_color,
		orl::Option<sf::Color> const& background_selection_color,
		orl::Option<sf::Color> const& inactive_text_selection_color,
		orl::Option<sf::Color> const& inactive_background_selection_color,
		orl::Option<size_t> const& size,
		orl::Option<sf::Font&> const& font,
		orl::Option<bool> const& bold,
		orl::Option<bool> const& italic,
		orl::Option<std::vector<bp::BoxPtr<BaseLine::Make> > >&& lines,
		sf::Text::Style const& style
	) :
		text_color(
			get_param<sf::Color>(
				base_stile,
				text_color,
				"text_color",
				[&](auto const& param) {
					return param.text_color;
				}
			)
		),
		text_selection_color(
			get_param<sf::Color>(
				base_stile,
				text_selection_color,
				"text_selection_color",
				[](auto const& param) {
					return param.text_selection_color;
				}
			)
		),
		background_selection_color(
			get_param<sf::Color>(
				base_stile,
				background_selection_color,
				"background_selection_color",
				[](auto const& param) {
					return param.background_selection_color;
				}
			)
		),
		inactive_text_selection_color(
			get_param<sf::Color>(
				base_stile,
				inactive_text_selection_color,
				"inactive_text_selection_color",
				[](auto const& param) {
					return param.inactive_text_selection_color;
				}
			)
		),
		inactive_background_selection_color(
			get_param<sf::Color>(
				base_stile,
				inactive_background_selection_color,
				"inactive_background_selection_color",
				[](auto const& param) {
					return param.inactive_background_selection_color;
				}
			)
		),
		size(
			get_param<size_t>(
				base_stile,
				size,
				"size",
				[](auto const& param) {
					return param.size;
				}
			)
		),
		font(
			font.some_or_else([&base_stile]() -> sf::Font&{
				return base_stile.except(TextStyleParameterException{"font"}).font;
			})
		),
		bold(
			get_param<bool>(
				base_stile,
				bold,
				"bold",
				[&style](auto const& param) {
					return style & sf::Text::Style::Bold || param.bold;
				}
			)
		),
		italic(
			get_param<bool>(
				base_stile,
				italic,
				"italic",
				[&style](auto const& param) {
					return style & sf::Text::Style::Italic || param.italic;
				}
			)
		),
		lines(
			[this, &lines, &base_stile, &style] {
				auto lines_init_info{LineInitInfo{this->size, this->font, this->text_color}};
				auto result{
					lines.map([&lines_init_info](auto lines) {
						return map_make(std::move(lines), lines_init_info);
					}).some_or_else([&] {
						return base_stile.except(TextStyleParameterException{"lines"}).lines;
					})
				};
				if(style & sf::Text::Style::Underlined){
					result.emplace_back(bp::make_box_ptr<ie::Underline>(ie::Underline::Make{}, lines_init_info));
				}
				if(style & sf::Text::Style::StrikeThrough){
					result.emplace_back(bp::make_box_ptr<ie::StrikeThrough>(ie::StrikeThrough::Make{}, lines_init_info));
				}
				return result;
			}()
		){
	}
}

auto ieml::Decode<char, ie::TextStyle>::decode(ieml::Node const& node) -> orl::Option<ie::TextStyle>{
	auto map{node.get_map_view().except()};
	return ie::TextStyle{
		map.get_as<orl::Option<ie::TextStyle> >("base-style").except().ok_or({}),
		map.get_as<orl::Option<sf::Color> >("text-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Color> >("text-selection-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Color> >("background-selection-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Color> >("inactive-text-selection-color").except().ok_or({}),
		map.get_as<orl::Option<sf::Color> >("inactive-background-selection-color").except().ok_or({}),
		map.get_as<orl::Option<size_t> >("font-size").except().ok_or({}),
		map.get_as<orl::Option<sf::Font&> >("font").except().ok_or({}),
		map.get_as<orl::Option<bool> >("bold").except().ok_or({}),
		map.get_as<orl::Option<bool> >("italic").except().ok_or({}),
		map.get_as<orl::Option<std::vector<bp::BoxPtr<ie::BaseLine::Make> > > >("lines").except().ok_or({}),
		map.get_as<ie::LoadTextStyle>("style").except().map_ok([](auto style){return style.style;}).ok_or(sf::Text::Style::Regular)
	};
}
