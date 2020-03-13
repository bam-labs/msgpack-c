target_sources(msgpackc
	INTERFACE
		unordered_map.hpp;
		timespec.hpp;
		array.hpp;
		tuple.hpp;
		forward_list.hpp;
		array_char.hpp;
		reference_wrapper.hpp;
		chrono.hpp;
		shared_ptr.hpp;
		unordered_set.hpp;
		array_unsigned_char.hpp;
		unique_ptr.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
