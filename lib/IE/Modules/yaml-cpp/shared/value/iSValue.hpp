#pragma once

#include "../iShared.hpp"

namespace ui {
	template<typename T>
	class ISValue : public IShared {
	public:
		using SetterFunc = std::function<void(const T&)>;
		
		virtual void addSetter(const SetterFunc& setter) = 0;
		
		virtual const T& getValue() const = 0;
		
		virtual void setValue(const T& value) = 0;
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
