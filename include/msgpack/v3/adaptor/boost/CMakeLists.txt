target_sources(msgpackc
	INTERFACE
		msgpack_variant_decl.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
