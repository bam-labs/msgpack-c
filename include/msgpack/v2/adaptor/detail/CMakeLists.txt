target_sources(msgpackc
	INTERFACE
		cpp11_define_map_decl.hpp;
		cpp03_define_array_decl.hpp;
		cpp11_msgpack_tuple_decl.hpp;
		cpp03_define_map_decl.hpp;
		cpp11_define_array_decl.hpp;
		cpp03_msgpack_tuple_decl.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
