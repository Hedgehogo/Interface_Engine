namespace ie {
	template<typename T>
	SInitInfo::SInitInfo(BasicActionInitInfo<T> init_info) : SInitInfo(init_info.dyn_buffer, init_info.update_manager){
	}
}