#pragma once

#include "../ISList.hpp"

namespace ie {
	template<typename T>
	class SList : public virtual ISList {
	protected:
		void set();
	
	public:
		using V = to_auto<decltype(std::declval<T>().get_value())>;
		using SetterFunc = std::function<void(const std::vector<V>&)>;
		
		SList(const std::vector<V>& list = {});
		
		SList(std::vector<std::shared_ptr<T>> list);
		
		PIShared get_element_ptr(size_t index) const override;
		
		void set_element_ptr(size_t index, PIShared value) override;
		
		V get_element(size_t index) const;
		
		void set_element(size_t index, const V& value);
		
		std::vector<V> get_value() const;
		
		void set_value(const std::vector<V>& list);
		
	protected:
		std::vector<std::shared_ptr<T>> list;
		std::vector<SetterFunc> setters;
	};
	
	template<typename T>
	struct DecodePointer<SList<T> > {
		static bool decode_pointer(const YAML::Node& node, SList<T>*& with_list);
	};
	
	template<typename T>
	using PSList = std::shared_ptr<SList<T>>;
}

#include "SList.inl"