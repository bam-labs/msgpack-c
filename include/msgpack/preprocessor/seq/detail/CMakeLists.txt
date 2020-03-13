target_sources(msgpackc
	INTERFACE
		to_list_msvc.hpp;
		binary_transform.hpp;
		is_empty.hpp;
		split.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
