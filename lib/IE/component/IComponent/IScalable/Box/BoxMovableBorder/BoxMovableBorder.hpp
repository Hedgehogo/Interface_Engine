#pragma once

#include "IE/modules/yaml-cpp/file-buffer/FileBuffer.hpp"
#include "IE/modules/yaml-cpp/shared/ISValue/ISCoefficientValue/SCoefficientValue/SCoefficientValue.hpp"
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
			PSCoefficient border_value;
			int border_interaction_size = 5;
			Key key = Key::MouseLeft;
			sf::Vector2f min_size = {};
			
			Make(
				BoxPtr<IScalable::Make>&& first_object,
				BoxPtr<IScalable::Make>&& second_object,
				bool is_horizontal_border,
				PSCoefficient border_value,
				int border_interaction_size = 5,
				Key key = Key::MouseLeft,
				sf::Vector2f min_size = {}
			);
			
			BoxMovableBorder* make(InitInfo init_info) override;
		};
		
		BoxMovableBorder(Make&& make, InitInfo init_info);
		
		BoxMovableBorder(
			BoxPtr<IScalable>&& first_object,
			BoxPtr<IScalable>&& second_object,
			bool is_horizontal_border,
			PSCoefficient border_value,
			int border_interaction_size = 5,
			sf::Vector2f min_size = {}
		);
		
		void init(InitInfo init_info) override;
		
		float get_border_value();
		
		void set_border_value(float border_value);
		
		float get_border_value_now();
		
		int get_border_interaction_size();
		
		void set_border_interaction_size(int size);
		
		bool get_is_horizontal_border();
		
		bool is_in_border(sf::Vector2f point_position);
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IScalable& get_first_object() override;
		
		const IScalable& get_first_object() const override;
		
		IScalable& get_second_object() override;
		
		const IScalable& get_second_object() const override;
		
		BoxMovableBorder* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		BasicInteractiveData<BoxMovableBorder&> interactive;
		BoxPtr<IScalable> first_object;
		BoxPtr<IScalable> second_object;
		PSCoefficient border_value;
		float border_value_now;
		int border_interaction_size;
		bool is_horizontal_border;
	};
	
	template<>
	struct DecodePointer<BoxMovableBorder> {
		static bool decode_pointer(const YAML::Node& node, BoxMovableBorder*& box_with_movable_border);
	};
}