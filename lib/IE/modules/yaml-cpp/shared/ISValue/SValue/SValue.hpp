#pragma once

#include "../ISValue.hpp"

namespace ie {
	template<typename T>
	class SValue : public virtual ISValue<T> {
	public:
		explicit SValue(T value = T{});
		
		void add_setter(const typename ISValue<T>::SetterFunc& setter) override;
		
		const T& get_value() const override;
		
		void set_value(const T& value) override;
	
	protected:
		T value_;
		std::vector<typename ISValue<T>::SetterFunc> setters_;
	};
	
	/*old_yaml_decode_pointer
	template<typename T>
	struct DecodePointer<SValue<T> > {
		static bool decode_pointer(const YAML::Node& node, SValue<T>*& sValue);
	};
	*/
	
	using Sbool = SValue<bool>;
	using Sfloat = SValue<float>;
	using Sint = SValue<int>;
	using Ssize = SValue<size_t>;
	
	template<typename T>
	using PSValue = std::shared_ptr<SValue<T>>;
	
	using PSbool = std::shared_ptr<Sbool>;
	using PSfloat = std::shared_ptr<Sfloat>;
	using PSint = std::shared_ptr<Sint>;
	using PSsize = std::shared_ptr<Ssize>;
}

#include "SValue.inl"