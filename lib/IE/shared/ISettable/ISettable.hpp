#pragma once

namespace ie {
	template<typename T_>
	class ISettable {
	public:
		virtual auto set(T_ value) -> void = 0;
		
		virtual ~ISettable() = default;
	};
}
