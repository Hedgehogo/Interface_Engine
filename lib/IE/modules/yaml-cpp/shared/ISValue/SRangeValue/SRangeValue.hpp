#pragma once

#include "../SValue/SValue.hpp"

namespace ie {
	template<typename T>
	class SRangeValue : public SValue<T> {
	public:
		explicit SRangeValue(T value = {});
		
		T get_upper();
		
		T get_lower();
		
		void set_upper(const T& upper);
		
		void set_lower(const T& lower);
		
		void set_bounds(T lower, T upper);
		
		void set_value(const T& value) override;
	
	protected:
		T upper_;
		T lower_;
	};
	
	/*old_yaml_decode_pointer
	template<typename T>
	struct DecodePointer<SRangeValue<T>> {
		static bool decode_pointer(const YAML::Node& node, SRangeValue<T>*& sRange_value);
	};
	*/
	
	template<typename T>
	using SRange = SRangeValue<T>;
	
	template<typename T>
	using PSRange = std::shared_ptr<SRange<T> >;
	
	using SRbool = SRange<bool>;
	using SRfloat = SRange<float>;
	using SRint = SRange<int>;
	using SRsize = SRange<size_t>;
	
	using PSRbool = std::shared_ptr<SRbool>;
	using PSRfloat = std::shared_ptr<SRfloat>;
	using PSRint = std::shared_ptr<SRint>;
	using PSRsize = std::shared_ptr<SRsize>;
}

#include "SRangeValue.inl"
