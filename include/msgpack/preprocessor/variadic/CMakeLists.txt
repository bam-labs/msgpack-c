add_subdirectory(detail)
target_sources(msgpackc
	INTERFACE
		to_tuple.hpp;
		size.hpp;
		to_array.hpp;
		to_seq.hpp;
		to_list.hpp;
		elem.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
