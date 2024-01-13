//included into SharedBuffer.hpp

namespace ie {
	template<typename T>
	bool DynBuffer::add(MakeDyn<T> make_dyn) {
		if(auto pair{std::get_if<0>(&make_dyn.data_)}) {
			return indexed_.emplace(pair->id_, pair->make_.make(*this)).second;
		}
	}
	
	template<typename T>
	T& DynBuffer::get(MakeDyn<T> make_dyn) {
		if(auto pair{std::get_if<0>(&make_dyn.data_)}) {
			auto& builder{rttb::Builder<ieml::Node const&, T>::builder()};
			if(pair->id_ != 0) {
				if(auto add_result{indexed_.emplace(pair->id_, pair->make_->make(*this))}; add_result.second) {
					return *builder.cast(add_result.first->second).except();
				}
				return *builder.cast(indexed_.at(pair->id_)).except();
			}
			return *builder.cast(non_indexed_.emplace_back(pair->make_->make(*this))).except();
		}
		return *std::get_if<1>(&make_dyn.data_);
	}
	
	template<typename Type_>
	MakeDyn<Type_>::MakeDyn(Type_& ref) : data_(ref) {
	}
	
	template<typename Type_>
	MakeDyn<Type_>::MakeDyn(bp::BoxPtr<MakeType> make) : data_(Pair{0, std::move(make)}) {
	}
	
	template<typename Type_>
	MakeDyn<Type_>::MakeDyn(size_t id, bp::BoxPtr<MakeType> make) : data_(Pair{id, std::move(make)}) {
	}
	
	template<typename Type_>
	Type_& MakeDyn<Type_>::make(DynBuffer& dyn_buffer) {
		return dyn_buffer.get(std::move(*this));
	}
	
	template<typename Type_>
	orl::Option<MakeDyn<Type_> > MakeDyn<Type_>::decode(ieml::Node const& node) {
		auto decode_make_fn = [&](ieml::Node const& node) -> bp::BoxPtr<MakeType> {
			auto& builder{rttb::Builder<ieml::Node const&, MakeType>::builder()};
			auto& clear_node{node.get_clear_data<ieml::NodeType::Tag>()};
			if(&clear_node != &node) {
				auto type_name{node.get_tag()};
				if(auto make{builder.build(type_name.some(), clear_node)}) {
					return {make.some()};
				}
			}
			if(auto make{builder.implicit_build(node)}) {
				return {make.some()};
			}
		};
		auto& tag_node{node.get_clear_data<ieml::NodeType::GetAnchor, ieml::NodeType::TakeAnchor>()};
		auto result{decode_make_fn(tag_node)};
		if(&tag_node != &node) {
			size_t id{reinterpret_cast<size_t>(&tag_node)};
			return {{id, {result}}};
		}
		return {{0, {result}}};
	}
}