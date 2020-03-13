target_sources(msgpackc
	INTERFACE
		carray_byte.hpp;
		byte.hpp;
		optional.hpp;
		string_view.hpp;
		vector_byte.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
