#pragma once

#include "modules/appendix/yaml-cpp/buffer/buffer.hpp"
#include "../iSConvertValue.hpp"
#include "../../general/sValue.hpp"

namespace ui {
	template<typename FromType, typename ToType>
	class SConvertValue : public ISConvertValue<FromType, ToType>, public SValue<ToType> {
	protected:
		PISValue<FromType> fromValue;
		
		virtual ToType convert(FromType fromValue);
	
	public:
		SConvertValue(PISValue<FromType> fromValue, ToType defaultValue = ToType{});
		
		void setFromValue(PISValue<FromType> fromValue);
		
		const ToType& getValue() const override;
		
		void setValue(const ToType& value) override;
	};
	
	
	template<typename FromType, typename ToType>
	struct DecodePointer<SConvertValue<FromType, ToType>> {
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