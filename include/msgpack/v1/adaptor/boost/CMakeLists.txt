target_sources(msgpackc
	INTERFACE
		optional.hpp;
		msgpack_variant.hpp;
		string_view.hpp;
		msgpack_variant_decl.hpp;
		fusion.hpp;
		string_ref.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
