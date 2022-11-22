#pragma once
#include "../general/sValue.hpp"

namespace ui {
	template <typename T>
	class SRangeValue : public SValue<T> {
	protected:
		T upper;
		T bottom;
	
	public:
		explicit SRangeValue(T value = {});
		
		void setBounds(T upper, T bottom);
		
		void setValue(const float &value) override;
	};
	
	template <typename T>
	bool convertPointer(const YAML::Node &node, SRangeValue<T> *&sRangeValue);
	
	template <typename T>
	using SRange = SRangeValue<T>;
	
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
