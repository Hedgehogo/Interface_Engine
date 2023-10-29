#pragma once

#include "../../../../buffer/Buffer.hpp"
#include "../ISConvertValue.hpp"
#include "../../SValue/SValue.hpp"

namespace ie {
	template<typename FromType, typename ToType>
	class SConvertValue : public SValue<ToType>, public virtual ISConvertValue<FromType, ToType> {
	protected:
		virtual ToType convert(FromType from_value);
	
	public:
		SConvertValue(PISValue<FromType> from_value, ToType default_value = ToType{});
		
		void set_from_value(PISValue<FromType> from_value);
		
		const ToType& get_value() const override;
		
		void set_value(const ToType& value) override;
	
	protected:
		PISValue<FromType> from_value_;
	};
	
	/*old_yaml_decode_pointer
	template<typename FromType, typename ToType>
	struct DecodePointer<SConvertValue<FromType, ToType> > {
		static bool decode_pointer(const YAML::Node& node, SConvertValue<FromType, ToType>*& sConvert_value);
	};
	*/
	
	template<typename T>
	using SConvertToBool = SConvertValue<T, bool>;
	
	template<typename T>
	using SConvertToInt = SConvertValue<T, int>;
	
	template<typename T>
	using SConvertToFloat = SConvertValue<T, float>;
}

#include "SConvertValue.inl"