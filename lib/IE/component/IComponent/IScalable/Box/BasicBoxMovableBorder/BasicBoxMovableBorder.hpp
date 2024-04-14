#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "IE/interaction/IInteraction/BasicPressedInteraction/BasicPressedInteraction.hpp"
#include "../../BasicInteractiveData/BasicInteractiveData.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"
#include "../Box.hpp"

namespace ie {
	template<bool mutable_>
	class BasicBoxMovableBorder;
	
	namespace make_system {
		template<bool mutable_>
		struct BasicBoxMovableBorder : public virtual IScalableTwoObjects::Make, public virtual Box::Make {
			using Value_ = std::conditional_t<mutable_, ISMRFloat, ISRFloat>;
			
			BoxPtr<IScalable::Make> first_object;
			BoxPtr<IScalable::Make> second_object;
			bool is_horizontal_border;
			MakeDyn<Value_> border_value;
			sf::Vector2f min_size = {};
			
			BasicBoxMovableBorder(
				BoxPtr<IScalable::Make>&& first_object,
				BoxPtr<IScalable::Make>&& second_object,
				bool is_horizontal_border,
				MakeDyn<Value_> border_value,
				sf::Vector2f min_size = {}
			);
			
			auto make(InitInfo init_info) -> ie::BasicBoxMovableBorder<mutable_>* override;
		};
	}
	
	template<bool mutable_>
	class BasicBoxMovableBorder : public virtual IScalableTwoObjects, public Box {
	public:
		using Make = make_system::BasicBoxMovableBorder<mutable_>;
		using Value_ = typename Make::Value_;
		
		BasicBoxMovableBorder(Make&& make, InitInfo init_info);
		
		auto get_first_object() -> IScalable& override;
		
		auto get_first_object() const -> IScalable const& override;
		
		auto get_second_object() -> IScalable& override;
		
		auto get_second_object() const -> IScalable const& override;
		
		auto set_border_position(float value) -> void;
		
		auto get_is_horizontal_border() -> bool;
		
		auto handle_event(Event event) -> bool override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		BoxPtr<IScalable> first_object_;
		BoxPtr<IScalable> second_object_;
		bool is_horizontal_border_;
		SReader<Value_> border_value_;
	};
	
	using BoxMovableBorder = BasicBoxMovableBorder<false>;
}

template<>
struct ieml::Decode<char, ie::BoxMovableBorder::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxMovableBorder::Make>;
};

#include "BasicBoxMovableBorder.inl"