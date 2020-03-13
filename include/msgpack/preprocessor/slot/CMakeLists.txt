add_subdirectory(detail)
target_sources(msgpackc
	INTERFACE
		counter.hpp;
		slot.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
