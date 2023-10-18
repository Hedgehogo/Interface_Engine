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
	
	typedef ISValue<bool> ISbool;
	typedef ISValue<float> ISfloat;
	typedef ISValue<int> ISint;
	typedef ISValue<unsigned> ISuint;
	
	template<typename T>
	using PISValue = std::shared_ptr<ISValue<T>>;
	
	typedef std::shared_ptr<ISbool> PISbool;
	typedef std::shared_ptr<ISfloat> PISfloat;
	typedef std::shared_ptr<ISint> PISint;
	typedef std::shared_ptr<unsigned> PISuint;
}