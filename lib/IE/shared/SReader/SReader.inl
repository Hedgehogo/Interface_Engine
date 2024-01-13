//included into ISReader.hpp

namespace ie {
	template<typename Value_, typename _>
	SReader<Value_, _>::SReader(Value_& readable, ReadFn&& read_fn) :
		readable_(&readable), read_fn_(&static_cast<ISValue<T>&>(readable).add_read_fn(std::move(read_fn))) {
	}
	
	template<typename Value_, typename _>
	SReader<Value_, _>::SReader(const SReader& other) :
		readable_(other.readable_), read_fn_(&static_cast<ISValue<T>&>(*other.readable_).add_read_fn(ReadFn{*other.read_fn_})) {
	}
	
	template<typename Value_, typename _>
	SReader<Value_, _>::SReader(SReader&& other) : readable_(other.readable_), read_fn_(other.read_fn_) {
		other.readable_ = nullptr;
	}
	
	template<typename Value_, typename _>
	Value_& SReader<Value_, _>::get() const {
		return *readable_;
	}
	
	template<typename Value_, typename _>
	SReader<Value_, _>::~SReader() {
		if(readable_) {
			static_cast<ISValue<T>&>(*readable_).delete_read_fn(*read_fn_);
		}
	}
}
