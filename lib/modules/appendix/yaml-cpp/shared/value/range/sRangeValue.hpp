#pragma once

#include "../general/sValue.hpp"

namespace ui {
	template<typename T>
	class SRangeValue : public SValue<T> {
	protected:
		T upper;
		T lower;
	
	public:
		explicit SRangeValue(T value = {});
		
		T getUpper();
		
		T getLower();
		
		void setUpper(const T& upper);
		
		void setLower(const T& lower);
		
		void setBounds(T lower, T upper);
		
		void setValue(const T& value) override;
	};
	
	
	template<typename T>
	struct DecodePointer<SRangeValue<T>> {
		static bool decodePointer(const YAML::Node& node, SRangeValue<T>*& sRangeValue);
	};
	
	template<typename T>
	using SRange = SRangeValue<T>;
	
	template<typename T>
	using PSRange = std::shared_ptr<SRange<T>>;
	
	using SRbool = SRange<bool>;
	using SRfloat = SRange<float>;
	using SRint = SRange<int>;
	using SRuint = SRange<unsigned>;
	
	using PSRbool = std::shared_ptr<SRbool>;
	using PSRfloat = std::shared_ptr<SRfloat>;
	using PSRint = std::shared_ptr<SRint>;
	using PSRuint = std::shared_ptr<SRuint>;
}

#include "sRangeValue.inl"
