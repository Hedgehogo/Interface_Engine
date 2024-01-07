//included into SharedBuffer.hpp

namespace ie {
	template<typename T>
	bool SharedBuffer::add(MakeDyn<T> make_shared) {
		return shared_.emplace(make_shared.id_, std::move(make_shared.object_)).second;
	}
	
	template<typename T>
	T& SharedBuffer::get(MakeDyn<T> make_shared) {
		if(auto result{shared_.emplace(make_shared.id_, std::move(make_shared.object_))}; result.second) {
			return rttb::Builder<ieml::Node const&, T>::cast(*result.first);
		}
		return shared_.at(make_shared.get_id());
	}
}