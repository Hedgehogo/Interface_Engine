#pragma once

#include "../ISValue.hpp"

namespace ie {
	template<typename T>
	class SReferenceValue : public virtual ISValue<T> {
	public:
		explicit SReferenceValue(T& value_reference);
		
		void add_setter(const typename ISValue<T>::SetterFunc& setter) override;
		
		const T& get_value() const override;
		
		void set_value(const T& value) override;
		
		virtual void set_reference(T& value_reference);
	
	protected:
		T* value_reference;
		std::vector<typename ISValue<T>::SetterFunc> setters;
	};
}

#include "SReferenceValue.inl"
