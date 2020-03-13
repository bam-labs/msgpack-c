target_sources(msgpackc
	INTERFACE
		shared.hpp;
		counter.hpp;
		def.hpp;
		slot5.hpp;
		slot4.hpp;
		slot1.hpp;
		slot3.hpp;
		slot2.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
