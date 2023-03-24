#pragma once

namespace ui {
	class IEvent {
	public:
		virtual void start() {}
		
		virtual void finish() {}
		
		virtual ~IEvent() = default;
	};
}
