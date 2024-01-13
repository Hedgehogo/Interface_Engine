#pragma once

namespace ie {
	template<typename T_>
	class ISettable {
	public:
		virtual void set(T_ value) = 0;
	};
}
