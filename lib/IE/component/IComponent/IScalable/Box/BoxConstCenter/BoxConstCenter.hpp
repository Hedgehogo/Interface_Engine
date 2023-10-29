#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxConstCenter : public Box, public virtual IScalableTwoObjects {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> const_object;
			BoxPtr<IScalable::Make> background;
			sf::Vector2f const_size;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& const_object, BoxPtr<IScalable::Make>&& background, sf::Vector2f const_size, sf::Vector2f min_size = {});
			
			BoxConstCenter* make(InitInfo init_info) override;
		};
		
		BoxConstCenter(Make&& make, InitInfo init_info);
		
		BoxConstCenter(BoxPtr<IScalable>&& const_object, BoxPtr<IScalable>&& background, const sf::Vector2f& const_size, const sf::Vector2f& min_size = {});
		
		void init(InitInfo init_info) override;
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		IScalable& get_first_object() override;
		
		const IScalable& get_first_object() const override;
		
		IScalable& get_second_object() override;
		
		const IScalable& get_second_object() const override;
		
		bool update_interactions(sf::Vector2f) override;
		
		BoxConstCenter* copy() override;
	
	protected:
		BoxPtr<IScalable> const_object_;
		BoxPtr<IScalable> background_;
		sf::Vector2f const_size_;
		bool resized_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<BoxConstCenter> {
		static bool decode_pointer(const YAML::Node& node, BoxConstCenter*& box_with_const_center);
	};
	*/
}
