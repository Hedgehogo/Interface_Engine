#pragma once

#include "../../../../buffer/buffer.hpp"
#include "../iSConvertValue.hpp"
#include "../../general/sValue.hpp"

namespace ie {
	template<typename FromType, typename ToType>
	class SConvertValue : public SValue<ToType>, public virtual ISConvertValue<FromType, ToType> {
	protected:
		virtual ToType convert(FromType fromValue);
	
	public:
		SConvertValue(PISValue<FromType> fromValue, ToType defaultValue = ToType{});
		
		void setFromValue(PISValue<FromType> fromValue);
		
		const ToType& getValue() const override;
		
		void setValue(const ToType& value) override;
	
	protected:
		PISValue<FromType> fromValue;
	};
	
	template<typename FromType, typename ToType>
	struct DecodePointer<SConvertValue<FromType, ToType> > {
		static bool decodePointer(const YAML::Node& node, SConvertValue<FromType, ToType>*& sConvertValue);
	};
	
	template<typename T>
	using SConvertToBool = SConvertValue<T, bool>;
	
	template<typename T>
	using SConvertToInt = SConvertValue<T, int>;
	
	template<typename T>
	using SConvertToFloat = SConvertValue<T, float>;
}

#include "sConvertValue.inl"