#include "Event.hpp"

namespace ie::event_system {
	auto Touch::is_mouse() -> bool {
		return id == std::numeric_limits<size_t>::max();
	}
	
	Event::Event(Event::Data data) : data_(std::move(data)) {
	}
	
	auto Event::Closed(std::monostate) -> Event {
		return Event{Data{std::in_place_index_t<0>(), event_system::Empty{}}};
	}
	
	auto Event::LostFocus(std::monostate) -> Event {
		return Event{Data{std::in_place_index_t<1>(), event_system::Empty{}}};
	}
	
	auto Event::GainedFocus(std::monostate) -> Event {
		return Event{Data{std::in_place_index_t<2>(), event_system::Empty{}}};
	}
	
	auto Event::TextEntered(char32_t unicode) -> Event {
		return Event{Data{std::in_place_index_t<3>(), event_system::TextEntered{unicode}}};
	}
	
	auto Event::Scroll(size_t wheel_id, float delta) -> Event {
		return Event{Data{std::in_place_index_t<4>(), event_system::Scroll{wheel_id, delta}}};
	}
	
	auto Event::Touch(size_t id, sf::Vector2i position) -> Event {
		return Event{Data{std::in_place_index_t<5>(), event_system::Touch{id, position}}};
	}
	
	auto Event::JoystickConnect(size_t id) -> Event {
		return Event{Data{std::in_place_index_t<6>(), event_system::JoystickConnect{id}}};
	}
	
	auto Event::JoystickDisconnect(size_t id) -> Event {
		return Event{Data{std::in_place_index_t<7>(), event_system::JoystickConnect{id}}};
	}
	
	auto Event::JoystickMove(size_t id, size_t axis_id, float position) -> Event {
		return Event{Data{std::in_place_index_t<8>(), event_system::JoystickMove{id, axis_id, position}}};
	}
	
	auto Event::JoystickButton(size_t id, size_t button_id) -> Event {
		return Event{Data{std::in_place_index_t<9>(), event_system::JoystickButton{id, button_id}}};
	}
	
	auto Event::closed() const -> orl::Option<event_system::Empty> {
		return alternative<Type::Closed>();
	}
	
	auto Event::lost_focus() const -> orl::Option<event_system::Empty> {
		return alternative<Type::LostFocus>();
	}
	
	auto Event::gained_focus() const -> orl::Option<event_system::Empty> {
		return alternative<Type::GainedFocus>();
	}
	
	auto Event::text_entered() const -> orl::Option<event_system::TextEntered> {
		return alternative<Type::TextEntered>();
	}
	
	auto Event::scroll() const -> orl::Option<event_system::Scroll> {
		return alternative<Type::Scroll>();
	}
	
	auto Event::touch() const -> orl::Option<event_system::Touch> {
		return alternative<Type::Touch>();
	}
	
	auto Event::joystick_connect() const -> orl::Option<event_system::JoystickConnect> {
		return alternative<Type::JoystickConnect>();
	}
	
	auto Event::joystick_disconnect() const -> orl::Option<event_system::JoystickConnect> {
		return alternative<Type::JoystickDisconnect>();
	}
	
	auto Event::joystick_move() const -> orl::Option<event_system::JoystickMove> {
		return alternative<Type::JoystickMove>();
	}
	
	auto Event::joystick_button() const -> orl::Option<event_system::JoystickButton> {
		return alternative<Type::JoystickButton>();
	}
	
	auto Event::touch_pressed(bool pressed) const -> orl::Option<event_system::Touch> {
		return touch().and_then([&](auto touch) -> orl::Option<event_system::Touch> {
			if(touch.id == std::numeric_limits<size_t>::max()) {
				if(pressed) {
					return {touch};
				} else {
					return {};
				}
			}
			return {touch};
		});
	}
	
	auto Event::type() const -> Event::Type {
		return static_cast<Type>(data_.index());
	}
	
	auto Event::operator<(Event const& event) -> bool {
		return data_.index() < event.data_.index();
	}
}
