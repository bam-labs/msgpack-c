#include <iostream>
#include <msgpack.hpp>
#include <chrono>
#include <time.h>
#include <sys/resource.h>

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
	Map cmd = Map({
                        {"version",2},
                        {"cmdkey","articulate head"},
                        {"attributes",Map({
                                {"a1",true},
                                {"a2",3.14f}
                        })}
                });

	// First iteration to print serialized and deserialized object	
	std::stringstream ss;
	msgpack::pack(ss, cmd);

	std::cout << std::endl;
        std::cout << "Serialized object: ";
	print(ss.str());
	std::cout << std::endl;

	std::cout << "Serialized data size in bytes : " << ss.str().size() << std::endl;
	std::cout << std::endl;

    	msgpack::object_handle oh =
        	msgpack::unpack(ss.str().data(), ss.str().size());
	msgpack::object obj = oh.get();

	std::cout << "Deserialized object : ";
        std::cout << obj << std::endl;
	std::cout << std::endl;

	// Collect and print CPU and wall clock time for 1000 iterations
	auto start = std::chrono::high_resolution_clock::now();
        struct timespec start_spec, end_spec;
        int retval = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_spec);
	const unsigned int iterations = 1000;
        for (size_t i = 0; i < iterations; i++) {
            ss.clear();
            msgpack::pack(ss, cmd);
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
        std::cout << "Total wall clock time: " << duration << " nanoseconds" << std::endl;
        std::cout << "Average wall clock time per iteration: " << duration/iterations << " nanoseconds" << std::endl;
	std::cout << std::endl;
        std::cout << "Total CPU time: " << cpu_duration << " nanoseconds" << std::endl;
        std::cout << "Average CPU time per iteration: " << cpu_duration/iterations << " nanoseconds" << std::endl;
	std::cout << std::endl;

	// print memory usage stats
	struct rusage usage;
	const int CONVERSION_VALUE = 1024;
	getrusage(RUSAGE_SELF, &usage);
	std::cout << "Memory usage in kbytes : " << (usage.ru_maxrss/CONVERSION_VALUE) << std::endl;
	std::cout << std::endl;
}

