#pragma once

namespace ui {
	class IValve {
	public:
		virtual bool operator()() = 0;
		
		virtual IValve* copy() = 0;
	};
}