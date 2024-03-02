#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "IE/interaction/IInteraction/BasicPressedInteraction/BasicPressedInteraction.hpp"
#include "MovableBorderAction/MovableBorderAction.hpp"
#include "../Box.hpp"
#include "../../BasicInteractiveData/BasicInteractiveData.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxMovableBorder : public Box, public virtual IScalableTwoObjects, public virtual IUpdatable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> first_object;
			BoxPtr<IScalable::Make> second_object;
			bool is_horizontal_border;
			MakeDyn<ISMRFloat> border_value;
			int border_interaction_size = 5;
			Key key = Key::MouseLeft;
			sf::Vector2f min_size = {};
			
			Make(
				BoxPtr<IScalable::Make>&& first_object,
				BoxPtr<IScalable::Make>&& second_object,
				bool is_horizontal_border,
				MakeDyn<ISMRFloat> border_value,
				int border_interaction_size = 5,
				Key key = Key::MouseLeft,
				sf::Vector2f min_size = {}
			);
			
			auto make(InitInfo init_info) -> BoxMovableBorder* override;
		};
		
		BoxMovableBorder(Make&& make, InitInfo init_info);
		
		auto get_border_value() -> float;
		
		auto set_border_value(float border_value) -> void;
		
		auto get_border_value_now() -> float;
		
		auto get_border_interaction_size() -> int;
		
		auto set_border_interaction_size(int size) -> void;
		
		auto get_is_horizontal_border() -> bool;
		
		auto is_in_border(sf::Vector2f point_position) -> bool;
		
		auto update() -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_first_object() -> IScalable& override;
		
		auto get_first_object() const -> IScalable const& override;
		
		auto get_second_object() -> IScalable& override;
		
		auto get_second_object() const -> IScalable const& override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		BasicInteractiveData<BoxMovableBorder&> interactive_;
		BoxPtr<IScalable> first_object_;
		BoxPtr<IScalable> second_object_;
		SReader<ISMRFloat> border_value_;
		float border_value_now_;
		int border_interaction_size_;
		bool is_horizontal_border_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxMovableBorder::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxMovableBorder::Make>;
};
