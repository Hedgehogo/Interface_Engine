#include "Positioning2.hpp"
#include "IE/sizing-positioning/IPositioning/Functions/make_position/make_position.hpp"

namespace ie {
	Positioning2::Make::Make(BoxPtr<IPositioning>&& horizontal, BoxPtr<IPositioning>&& vertical) :
		horizontal(std::move(horizontal)), vertical(std::move(vertical)) {
	}
	
	Positioning2::Make::Make(sf::Vector2f coefficient, sf::Vector2f offset, bool relative_target) :
		horizontal(make_position(coefficient.x, offset.x, relative_target)),
		vertical(make_position(coefficient.y, offset.y, relative_target)) {
	}
	
	Positioning2::Make::Make(Location2 parent_location, Location2 object_location, sf::Vector2f offset) :
		horizontal(new MatchSidesPositioning{
			get_horizontal_location(parent_location),
			get_horizontal_location(object_location),
			offset.x
		}),
		vertical(new MatchSidesPositioning{
			get_vertical_location(parent_location),
			get_vertical_location(object_location),
			offset.y
		}) {
	}
	
	Positioning2::Make::Make(sf::Vector2f coefficient, sf::Vector2f object_coefficient, sf::Vector2f offset, bool relative_target) :
		horizontal(make_position(coefficient.x, object_coefficient.x, offset.x, relative_target)),
		vertical(make_position(coefficient.y, object_coefficient.y, offset.y, relative_target)) {
	}
	
	Positioning2* Positioning2::Make::make(Positioning2InitInfo init_info) {
		return new Positioning2{std::move(*this), init_info};
	}
	
	Positioning2::Positioning2(Make&& make, Positioning2InitInfo init_info) :
		horizontal_(std::move(make.horizontal)), vertical_(std::move(make.vertical)), render_target_(&init_info.render_target) {
	}
	
	Positioning2::Positioning2(BoxPtr<IPositioning>&& horizontal, BoxPtr<IPositioning>&& vertical) :
		horizontal_(std::move(horizontal)), vertical_(std::move(vertical)), render_target_(nullptr) {
	}
	
	Positioning2::Positioning2(sf::Vector2f coefficient, sf::Vector2f offset, bool relative_target) :
		horizontal_(make_position(coefficient.x, offset.x, relative_target)),
		vertical_(make_position(coefficient.y, offset.y, relative_target)),
		render_target_(nullptr) {
	}
	
	Positioning2::Positioning2(Location2 parent_location, Location2 object_location, sf::Vector2f offset) :
		horizontal_(new MatchSidesPositioning{get_horizontal_location(parent_location), get_horizontal_location(object_location), offset.x}),
		vertical_(new MatchSidesPositioning{get_vertical_location(parent_location), get_vertical_location(object_location), offset.y}),
		render_target_(nullptr) {
	}
	
	Positioning2::Positioning2(sf::Vector2f coefficient, sf::Vector2f object_coefficient, sf::Vector2f offset, bool relative_target) :
		horizontal_(make_position(coefficient.x, object_coefficient.x, offset.x, relative_target)),
		vertical_(make_position(coefficient.y, object_coefficient.y, offset.y, relative_target)),
		render_target_(nullptr) {
	}
	
	void Positioning2::init(sf::RenderTarget& render_target) {
		this->render_target_ = &render_target;
	}
	
	sf::Vector2f Positioning2::find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size) {
		sf::Vector2f target_size{static_cast<sf::Vector2f>(render_target_->getSize())};
		return {horizontal_->find_position(parent_position.x, object_size.x, parent_size.x, target_size.x),
				vertical_->find_position(parent_position.y, object_size.y, parent_size.y, target_size.y)};
	}
	
	Positioning2* Positioning2::copy() {
		return new Positioning2{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<Positioning2>::decode_pointer(const YAML::Node& node, Positioning2*& positioning2) {
		if(node.IsScalar()) {
			positioning2 = new Positioning2{node.as<sf::Vector2f>()};
		} else {
			if(node["horizontal"] && node["vertical"]) {
				positioning2 = new Positioning2{
					node["horizontal"].as < BoxPtr < IPositioning > > (),
					node["vertical"].as < BoxPtr < IPositioning > > ()
				};
			} else {
				auto offset{conv_def(node["offset"], sf::Vector2f{})};
				
				if(node["coefficient"]) {
					positioning2 = new Positioning2{
						node["coefficient"].as<sf::Vector2f>(),
						offset,
						conv_bool_def(node["relative"], "target", "parent")
					};
				} else if(node["object-coefficient"]) {
					auto object_coefficient{node["object-coefficient"].as<sf::Vector2f>()};
					
					if(node["parent-coefficient"]) {
						positioning2 = new Positioning2{
							node["parent-coefficient"].as<sf::Vector2f>(),
							object_coefficient, offset, false
						};
					} else if(node["target-coefficient"]) {
						positioning2 = new Positioning2{
							node["target-coefficient"].as<sf::Vector2f>(),
							object_coefficient, offset, true
						};
					} else {
						throw YAML::BadConversion{node.Mark()};
					}
				} else if(node["parent-location"] && node["object-location"]) {
					positioning2 = new Positioning2{
						node["parent-location"].as<Location2>(),
						node["object-location"].as<Location2>(),
						offset
					};
				} else {
					throw YAML::BadConversion{node.Mark()};
				}
			}
		}
		return true;

	}
	*/
}