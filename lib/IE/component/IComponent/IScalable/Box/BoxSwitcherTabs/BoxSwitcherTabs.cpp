#include "BoxSwitcherTabs.hpp"

#include "../BoxSwitch/BoxSwitch.hpp"
#include "IE/event/EventHandler/KeyHandler/KeyHandler.hpp"
#include "IE/interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "IE/component/IComponent/IScalable/Box/BoxSwitcherTabs/SwitcherTabsAction/SwitcherTabsAction.hpp"

namespace ie {
	BoxSwitcherTabs::Make::Make(
		std::vector<BoxPtr<IScalable::Make> >&& objects,
		MakeDyn<ISMRSize> value,
		Key key,
		bool is_horizontal,
		sf::Vector2f min_size
	) :
		objects(std::move(objects)), value(std::move(value)), key(key), is_horizontal(is_horizontal), min_size(min_size) {
	}
	
	auto BoxSwitcherTabs::Make::make(InitInfo init_info) -> BoxSwitcherTabs* {
		return new BoxSwitcherTabs{std::move(*this), init_info};
	}
	
	BoxSwitcherTabs::BoxSwitcherTabs(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		interactive_(make_box_ptr<BasicOneKeyInteraction<BoxSwitcherTabs&>::Make>(
			make_box_ptr<SwitcherTabsAction::Make>(make.value.make(SInitInfo{init_info})), make.key
		), init_info, *this),
		objects_(map_make(std::move(make.objects), init_info)),
		is_horizontal_(make.is_horizontal),
		value_(make.value.make(SInitInfo{init_info})) {
		init_info.update_manager.add(*this);
	}
	
	auto BoxSwitcherTabs::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		
		if(is_horizontal_) {
			sf::Vector2f object_size{size.x / objects_.size(), size.y};
			float position_x = position.x;
			for(const auto& object: objects_) {
				object->resize(object_size, {position_x, position.y});
				position_x += object_size.x;
			}
		} else {
			sf::Vector2f object_size{size.x, size.y / objects_.size()};
			float position_y = position.y;
			for(const auto& object: objects_) {
				object->resize(object_size, {position.x, position_y});
				position_y += object_size.y;
			}
		}
	}
	
	auto BoxSwitcherTabs::update() -> void {
		interactive_.update();
	}
	
	auto BoxSwitcherTabs::handle_event(Event event) -> bool {
		return event.pointer().map([=](event_system::Pointer pointer) {
			interactive_.handle_event();
			return true;
		}).some_or_else([=] {
			auto updated{false};
			for(auto& object: objects_) {
				if(object->handle_event(event)) {
					updated = true;
				}
			}
			return updated;
		});
	}
	
	auto BoxSwitcherTabs::get_array_size() const -> size_t {
		return objects_.size();
	}
	
	auto BoxSwitcherTabs::get_object_at(size_t index) -> IScalable& {
		return *objects_.at(index);
	}
	
	auto BoxSwitcherTabs::get_object_at(size_t index) const -> IScalable const& {
		return *objects_.at(index);
	}
	
	auto BoxSwitcherTabs::get_tab(sf::Vector2f position) -> int {
		if(is_horizontal_) {
			return static_cast<int>((position.x - layout_.position.x) / (layout_.size.x / objects_.size()));
		}
		return static_cast<int>((position.y - layout_.position.y) / (layout_.size.y / objects_.size()));
	}
}

auto ieml::Decode<char, ie::BoxSwitcherTabs::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxSwitcherTabs::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxSwitcherTabs::Make{
		map.at("objects").except().as<std::vector<ie::BoxPtr<ie::IScalable::Make> > >().except(),
		map.at("value").except().as<ie::MakeDyn<ie::ISMRSize> >().except(),
		map.get_as<ie::Key>("key").except().ok_or(ie::Key::MouseLeft),
		map.get_as<bool>("horizontal").except().ok_or(true),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({}),
	};
}
