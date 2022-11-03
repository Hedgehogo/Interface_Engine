#pragma once

namespace ui {
	class IEvent {
	public:
		void start() {}
		
		void finish() {}
		
		virtual ~IEvent() = default;
	};
}
