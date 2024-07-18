#include "Event.hpp"

namespace ie::event_system {
	Pointer::Pointer(size_t id, sf::Vector2i position) : id(id), position(position) {}
	
	Pointer::Pointer(sf::Vector2i position) : id(std::numeric_limits<size_t>::max()), position(position) {}
	
	auto Pointer::is_mouse() -> bool {
		return id == std::numeric_limits<size_t>::max();
	}
	
	Event::Event(Event::Data data) : data_(std::move(data)) {
	}
	
	auto Event::Closed(event_system::Empty) -> Event {
		return Event{Data{std::in_place_index_t<0>(), event_system::Empty{}}};
	}
	
	auto Event::LostFocus(event_system::Empty) -> Event {
		return Event{Data{std::in_place_index_t<1>(), event_system::Empty{}}};
	}
	
	auto Event::GainedFocus(event_system::Empty) -> Event {
		return Event{Data{std::in_place_index_t<2>(), event_system::Empty{}}};
	}
	
	auto Event::TextEntered(event_system::TextEntered value) -> Event {
		return Event{Data{std::in_place_index_t<3>(), std::move(value)}};
	}
	
	auto Event::Scroll(event_system::Scroll value) -> Event {
		return Event{Data{std::in_place_index_t<4>(), std::move(value)}};
	}
	
	auto Event::Pointer(event_system::Pointer value) -> Event {
		return Event{Data{std::in_place_index_t<5>(), std::move(value)}};
	}
	
	auto Event::JoystickConnect(event_system::JoystickConnect value) -> Event {
		return Event{Data{std::in_place_index_t<6>(), std::move(value)}};
	}
	
	auto Event::JoystickDisconnect(event_system::JoystickConnect value) -> Event {
		return Event{Data{std::in_place_index_t<7>(), std::move(value)}};
	}
	
	auto Event::JoystickMove(event_system::JoystickMove value) -> Event {
		return Event{Data{std::in_place_index_t<8>(), std::move(value)}};
	}
	
	auto Event::JoystickButton(event_system::JoystickButton value) -> Event {
		return Event{Data{std::in_place_index_t<9>(), std::move(value)}};
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
	
	auto Event::pointer() const -> orl::Option<event_system::Pointer> {
		return alternative<Type::Pointer>();
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
	
	auto Event::touch(bool pressed) const -> orl::Option<event_system::Pointer> {
		return pointer().and_then([&](auto pointer) -> orl::Option<event_system::Pointer> {
			if(pointer.id == std::numeric_limits<size_t>::max()) {
				if(pressed) {
					return {pointer};
				} else {
					return {};
				}
			}
			return {pointer};
		});
	}
	
	auto Event::type() const -> Event::Type {
		return static_cast<Type>(data_.index());
	}
	
	auto Event::operator<(Event const& event) -> bool {
		return data_.index() < event.data_.index();
	}
}
