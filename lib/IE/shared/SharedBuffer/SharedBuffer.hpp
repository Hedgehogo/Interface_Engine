#pragma once

#include <IE/ieml/ieml-rttb/ieml-rttb.hpp>
#include <box-ptr/BoxPtr.hpp>

namespace ie {
	namespace fs = std::filesystem;
	
	class SharedBuffer {
	public:
		SharedBuffer() = default;
		
		template<typename T>
		bool add(MakeDyn<T> make_shared);
		
		template<typename T>
		T& get(MakeDyn<T> make_shared);
	
	private:
		absl::flat_hash_map<size_t, rttb::Dyn> shared_;
	};
}
