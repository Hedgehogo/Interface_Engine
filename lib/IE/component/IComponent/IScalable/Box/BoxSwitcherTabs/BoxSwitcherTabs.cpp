#include "BoxSwitcherTabs.hpp"

#include "../BoxSwitch/BoxSwitch.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include "IE/interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "IE/modules/yaml-cpp/shared/ISValue/ISConvertValue/BaseSConvertToBoolComparison/SConvertToBoolEquals/SConvertToBoolEquals.hpp"
#include "IE/component/IComponent/IScalable/Box/BoxSwitcherTabs/SwitcherTabsAction/SwitcherTabsAction.hpp"

namespace ie {
	BoxSwitcherTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSint value, Key key, bool is_horizontal, sf::Vector2f min_size) :
		objects(std::move(objects)), value(std::move(value)), key(key), is_horizontal(is_horizontal), min_size(min_size) {
	}
	
	BoxSwitcherTabs* BoxSwitcherTabs::Make::make(InitInfo init_info) {
		return new BoxSwitcherTabs{std::move(*this), init_info};
	}
	
	BoxSwitcherTabs::BoxSwitcherTabs(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		interactive(make_box_ptr<BasicOneKeyInteraction<BoxSwitcherTabs&>::Make>(
			make_box_ptr<SwitcherTabsAction::Make>(make.value), make.key
		), init_info, *this),
		objects(map_make(std::move(make.objects), init_info)),
		is_horizontal(make.is_horizontal),
		value(make.value) {
		init_info.update_manager.add(*this);
	}
	
	BoxSwitcherTabs::BoxSwitcherTabs(std::vector<BoxPtr<IScalable> >&& objects, PSint value, Key key, bool is_horizontal, sf::Vector2f min_size) :
		Box(min_size), interactive(make_box_ptr<BasicOneKeyInteraction<BoxSwitcherTabs&> >(make_box_ptr<SwitcherTabsAction>(value), key)),
		objects(std::move(objects)), is_horizontal(is_horizontal), value(value) {
	}
	
	void BoxSwitcherTabs::init(InitInfo init_info) {
		interactive.init(init_info, *this);
		for(auto& object: objects) {
			object->init(init_info);
		}
		init_info.update_manager.add(*this);
	}
	
	void BoxSwitcherTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		
		if(is_horizontal) {
			sf::Vector2f object_size{size.x / objects.size(), size.y};
			float position_x = position.x;
			for(const auto& object: objects) {
				object->resize(object_size, {position_x, position.y});
				position_x += object_size.x;
			}
		} else {
			sf::Vector2f object_size{size.x, size.y / objects.size()};
			float position_y = position.y;
			for(const auto& object: objects) {
				object->resize(object_size, {position.x, position_y});
				position_y += object_size.y;
			}
		}
	}
	
	void BoxSwitcherTabs::update() {
		interactive.update();
	}
	
	bool BoxSwitcherTabs::update_interactions(sf::Vector2f) {
		interactive.update_interactions();
		return true;
	}
	
	size_t BoxSwitcherTabs::get_array_size() const {
		return objects.size();
	}
	
	IScalable& BoxSwitcherTabs::get_object_at(size_t index) {
		return *objects.at(index);
	}
	
	const IScalable& BoxSwitcherTabs::get_object_at(size_t index) const {
		return *objects.at(index);
	}
	
	int BoxSwitcherTabs::get_tab(sf::Vector2f position) {
		if(is_horizontal) {
			return static_cast<int>((position.x - layout_.position.x) / (layout_.size.x / objects.size()));
		}
		return static_cast<int>((position.y - layout_.position.y) / (layout_.size.y / objects.size()));
	}
	
	BoxSwitcherTabs* BoxSwitcherTabs::copy() {
		return new BoxSwitcherTabs{*this};
	}
	
	bool DecodePointer<BoxSwitcherTabs>::decode_pointer(const YAML::Node& node, BoxSwitcherTabs*& switcher_tabs) {
		switcher_tabs = new BoxSwitcherTabs{
			node["objects"].as<std::vector<BoxPtr<IScalable> > >(),
			Buffer::get<Sint>(node["value"]),
			conv_def(node["key"], Key::MouseLeft),
			conv_bool_def(node["direction"], "horizontal", "vertical"),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}