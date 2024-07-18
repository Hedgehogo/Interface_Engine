#pragma once

#include <variant>
#include <SFML/Window/Event.hpp>
#include <option_result/option_result.hpp>
#include "IE/event/EventHandler/KeyHandler/KeyHandler.hpp"

namespace ie {
	namespace event_system {
		using Empty = std::monostate;
		
		struct TextEntered {
			char32_t symbol;
		};
		
		struct Scroll {
			size_t wheel_id;
			float delta;
		};
		
		struct Pointer {
			size_t id;
			sf::Vector2i position;
			
			Pointer(size_t id, sf::Vector2i position = {});
			
			Pointer(sf::Vector2i position = {});;
			
			auto is_mouse() -> bool;
		};
		
		struct JoystickConnect {
			size_t id;
		};
		
		struct JoystickMove {
			size_t id;
			size_t axis_id;
			float position;
		};
		
		struct JoystickButton {
			size_t id;
			size_t button_id;
		};
		
		class Event {
		public:
			enum class Type {
				Closed,
				LostFocus,
				GainedFocus,
				TextEntered,
				Scroll,
				Pointer,
				JoystickConnect,
				JoystickDisconnect,
				JoystickMove,
				JoystickButton,
			};
			
			using Data = std::variant<
				event_system::Empty,           //!< The window requested to be closed
				event_system::Empty,           //!< The window lost the focus
				event_system::Empty,           //!< The window gained the focus
				event_system::TextEntered,     //!< A character was entered
				event_system::Scroll,          //!< The mouse wheel was scrolled
				event_system::Pointer,         //!< A pointer exists
				event_system::JoystickConnect, //!< A joystick was connected
				event_system::JoystickConnect, //!< A joystick was disconnected
				event_system::JoystickMove,    //!< The joystick moved along an axis
				event_system::JoystickButton   //!< A joystick button was pressed
			>;
			
			template<Type Type_>
			using Alternative = std::variant_alternative_t<static_cast<size_t>(Type_), Data>;
			
			static auto Closed(event_system::Empty) -> Event;
			
			static auto LostFocus(event_system::Empty) -> Event;
			
			static auto GainedFocus(event_system::Empty) -> Event;
			
			static auto TextEntered(event_system::TextEntered value) -> Event;
			
			static auto Scroll(event_system::Scroll value) -> Event;
			
			static auto Pointer(event_system::Pointer value) -> Event;
			
			static auto JoystickConnect(event_system::JoystickConnect value) -> Event;
			
			static auto JoystickDisconnect(event_system::JoystickConnect value) -> Event;
			
			static auto JoystickMove(event_system::JoystickMove value) -> Event;
			
			static auto JoystickButton(event_system::JoystickButton value) -> Event;
			
			auto closed() const -> orl::Option<event_system::Empty>;
			
			auto lost_focus() const -> orl::Option<event_system::Empty>;
			
			auto gained_focus() const -> orl::Option<event_system::Empty>;
			
			auto text_entered() const -> orl::Option<event_system::TextEntered>;
			
			auto scroll() const -> orl::Option<event_system::Scroll>;
			
			auto pointer() const -> orl::Option<event_system::Pointer>;
			
			auto joystick_connect() const -> orl::Option<event_system::JoystickConnect>;
			
			auto joystick_disconnect() const -> orl::Option<event_system::JoystickConnect>;
			
			auto joystick_move() const -> orl::Option<event_system::JoystickMove>;
			
			auto joystick_button() const -> orl::Option<event_system::JoystickButton>;
			
			template<Type Type_>
			auto alternative() const -> orl::Option<Alternative<Type_> >;
			
			auto touch(bool pressed) const -> orl::Option<event_system::Pointer>;
			
			auto type() const -> Type;
			
			auto operator<(Event const& event) -> bool;
		
		private:
			Event(Data data);
			
			Data data_;
		};
	}
	
	using event_system::Event;
}

#include "Event.inl"
