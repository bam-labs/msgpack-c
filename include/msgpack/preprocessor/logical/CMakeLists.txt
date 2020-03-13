target_sources(msgpackc
	INTERFACE
		bool.hpp;
		and.hpp;
		compl.hpp;
		xor.hpp;
		bitnor.hpp;
		bitor.hpp;
		or.hpp;
		bitxor.hpp;
		nor.hpp;
		bitand.hpp;
		not.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
