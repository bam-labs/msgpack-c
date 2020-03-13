target_sources(msgpackc
	INTERFACE
		forward1.hpp;
		forward2.hpp;
		forward3.hpp;
		forward4.hpp;
		forward5.hpp;
		reverse4.hpp;
		reverse5.hpp;
		reverse2.hpp;
		reverse3.hpp;
		reverse1.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
