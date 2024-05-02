//included into Event.hpp

namespace ie::event_system {
	template<Event::Type Type_>
	auto Event::alternative() const -> orl::Option<Alternative<Type_> > {
		if(data_.index() == static_cast<size_t>(Type_)) {
			return {std::get<static_cast<size_t>(Type_)>(data_)};
		}
		return {};
	}
}
