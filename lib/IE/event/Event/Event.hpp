#pragma once

#include <variant>
#include <SFML/Window/Event.hpp>
#include <option_result/option_result.hpp>
#include "IE/event/KeyHandler/KeyHandler.hpp"

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
		
		struct Touch {
			size_t id;
			sf::Vector2i position;
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
				Touch,
				JoystickConnect,
				JoystickDisconnect,
				JoystickMove,
				JoystickButton,
			};
			
			static auto Closed(std::monostate) -> Event;
			
			static auto LostFocus(std::monostate) -> Event;
			
			static auto GainedFocus(std::monostate) -> Event;
			
			static auto TextEntered(char32_t unicode) -> Event;
			
			static auto Scroll(size_t wheel_id, float delta) -> Event;
			
			static auto Touch(size_t id, sf::Vector2i position) -> Event;
			
			static auto JoystickConnect(size_t id) -> Event;
			
			static auto JoystickDisconnect(size_t id) -> Event;
			
			static auto JoystickMove(size_t id, size_t axis_id, float position) -> Event;
			
			static auto JoystickButton(size_t id, size_t button_id) -> Event;
			
			auto closed() const -> orl::Option<event_system::Empty>;
			
			auto lost_focus() const -> orl::Option<event_system::Empty>;
			
			auto gained_focus() const -> orl::Option<event_system::Empty>;
			
			auto text_entered() const -> orl::Option<event_system::TextEntered>;
			
			auto scroll() const -> orl::Option<event_system::Scroll>;
			
			auto touch() const -> orl::Option<event_system::Touch>;
			
			auto joystick_connect() const -> orl::Option<event_system::JoystickConnect>;
			
			auto joystick_disconnect() const -> orl::Option<event_system::JoystickConnect>;
			
			auto joystick_move() const -> orl::Option<event_system::JoystickMove>;
			
			auto joystick_button() const -> orl::Option<event_system::JoystickButton>;
			
			auto type() const -> Type;
			
			auto operator<(Event const& event) -> bool;
		
		private:
			using Data = std::variant<
				event_system::Empty,           //!< The window requested to be closed
				event_system::Empty,           //!< The window lost the focus
				event_system::Empty,           //!< The window gained the focus
				event_system::TextEntered,     //!< A character was entered
				event_system::Scroll,          //!< The mouse wheel was scrolled
				event_system::Touch,           //!< A touch moved
				event_system::JoystickConnect, //!< A joystick was connected
				event_system::JoystickConnect, //!< A joystick was disconnected
				event_system::JoystickMove,    //!< The joystick moved along an axis
				event_system::JoystickButton   //!< A joystick button was pressed
			>;
			
			Event(Data data);
			
			Data data_;
		};
	}
	
	using event_system::Event;
}
