#pragma once

#include "../IShared.hpp"

namespace ie {
	template<typename T>
	class ISValue : public virtual IShared {
	public:
		using SetterFunc = std::function<void(const T&)>;
		
		virtual void add_setter(const SetterFunc& setter) = 0;
		
		virtual const T& get_value() const = 0;
		
		virtual void set_value(const T& value) = 0;
	};
	
	using ISbool = ISValue<bool>;
	using ISfloat = ISValue<float>;
	using ISint = ISValue<int>;
	using ISsize = ISValue<size_t>;
	
	template<typename T>
	using PISValue = std::shared_ptr<ISValue<T>>;
	
	using PISbool = std::shared_ptr<ISbool>;
	using PISfloat = std::shared_ptr<ISfloat>;
	using PISint = std::shared_ptr<ISint>;
	using PISsize = std::shared_ptr<size_t>;
}
