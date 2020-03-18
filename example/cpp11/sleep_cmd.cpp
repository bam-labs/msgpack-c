#include <iostream>
#include <msgpack.hpp>
#include <chrono>
#include <time.h>

//Print serialized object
void print(std::string const& buf) {
    for (std::string::const_iterator it = buf.begin(), end = buf.end();
         it != end;
         ++it) {
        std::cout
            << std::setw(2)
            << std::hex
            << std::setfill('0')
            << (static_cast<int>(*it) & 0xff)
            << ' ';
    }
    std::cout << std::dec << std::endl;
}

int main() {
	// using msgpack variant to store the nested struct
	using Map = std::multimap<msgpack::type::variant, msgpack::type::variant>;
	Map sleep_cmd = Map({
                        {"version",2},
                        {"bamkey","articulate head"},
                        {"attributes",Map({
                                {"a1",true},
                                {"a2",3.14f}
                        })}
                });

	// First iteration to print serialized and deserialized object	
	std::stringstream ss;
	msgpack::pack(ss, sleep_cmd);
	print(ss.str());

    	msgpack::object_handle oh =
        	msgpack::unpack(ss.str().data(), ss.str().size());
	msgpack::object obj = oh.get();
        std::cout << obj << std::endl;

	// Collect and print CPU and wall clock time for 1000 iterations
	auto start = std::chrono::high_resolution_clock::now();
        struct timespec start_spec, end_spec;
        int retval = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_spec);
	const unsigned int iterations = 1000;
	std::cout << "Serialized size in bytes : " << ss.str().size() << std::endl;
        for (size_t i = 0; i < iterations; i++) {
            ss.clear();
            msgpack::pack(ss, sleep_cmd);
            msgpack::object_handle oh =
                msgpack::unpack(ss.str().data(), ss.str().size());
            msgpack::object obj = oh.get();
	    Map retcmd;
            obj.convert(retcmd);
        }
        retval = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_spec);
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
        auto cpu_duration = static_cast<long>(1e9) * (end_spec.tv_sec - start_spec.tv_sec) + end_spec.tv_nsec - start_spec.tv_nsec;
        std::cout << "Wall clock time: " << duration << " nanoseconds" << std::endl;
        std::cout << "CPU time : " << cpu_duration << " nanoseconds" << std::endl;

}

