#include "msgpack.h"
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

const uint32_t ITERATIONS = 1000;
const uint32_t CONVERSION_VALUE = 1024;

void print(char const* buf, unsigned int len)
{
    size_t i = 0;
    printf("\nSerialized object: ");
    for(; i < len ; ++i)
    	printf("%02x ", 0xff & buf[i]);
    printf("\n");
    printf("\n");
    printf("Serialized data size in bytes: %d\n\n",len);
}

int main(void)
{
    msgpack_sbuffer sbuf;
    msgpack_packer pk;
    msgpack_zone mempool;
    msgpack_object deserialized;

    /* msgpack::sbuffer is a simple buffer implementation. */
    msgpack_sbuffer_init(&sbuf);

     /* serialize values into the buffer using msgpack_sbuffer_write callback function. */
    msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

    /* serialize values into the buffer using msgpack_sbuffer_write callback function. */
    msgpack_pack_array(&pk, 6);
    msgpack_pack_str(&pk, 7);
    msgpack_pack_str_body(&pk, "version", 7);
    msgpack_pack_int(&pk, 2);

    msgpack_pack_str(&pk, 6);
    msgpack_pack_str_body(&pk, "cmdkey", 6);
    msgpack_pack_str(&pk, 15);
    msgpack_pack_str_body(&pk, "articulate head", 15);

    msgpack_pack_str(&pk, 10);
    msgpack_pack_str_body(&pk, "attributes", 10);

    msgpack_pack_array(&pk, 4);

    msgpack_pack_str(&pk, 2);
    msgpack_pack_str_body(&pk, "a1", 2);
    msgpack_pack_true(&pk);

    msgpack_pack_str(&pk, 2);
    msgpack_pack_str_body(&pk, "a2", 2);
    msgpack_pack_float(&pk, 3.14);

    print(sbuf.data, sbuf.size);
    printf("\n");

    /* deserialize the buffer into msgpack_object instance. */
    /* deserialized object is valid during the msgpack_zone instance alive. */
    msgpack_zone_init(&mempool, 100);
    msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

    /* print the deserialized object. */
    printf("Deserialized object: ");
    msgpack_object_print(stdout, deserialized);
    printf("\n");

    msgpack_zone_destroy(&mempool);
    msgpack_sbuffer_destroy(&sbuf);

    /* run 1000 iterations, track time */
    struct timespec start_spec, end_spec, start_time, end_time;
    int retval = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_spec);
    retval = clock_gettime(CLOCK_REALTIME, &start_time);
    for (size_t i = 0; i < ITERATIONS; i++) 
    {
    	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 6);
    	msgpack_pack_str(&pk, 7);
    	msgpack_pack_str_body(&pk, "version", 7);
    	msgpack_pack_int(&pk, 2);

    	msgpack_pack_str(&pk, 6);
    	msgpack_pack_str_body(&pk, "cmdkey", 6);
    	msgpack_pack_str(&pk, 15);
    	msgpack_pack_str_body(&pk, "articulate head", 15);


	msgpack_pack_str(&pk, 10);
    	msgpack_pack_str_body(&pk, "attributes", 10);
    	
	msgpack_pack_array(&pk, 4);

    	msgpack_pack_str(&pk, 2);
   	msgpack_pack_str_body(&pk, "a1", 2);
    	msgpack_pack_true(&pk);

    	msgpack_pack_str(&pk, 2);
    	msgpack_pack_str_body(&pk, "a2", 2);
    	msgpack_pack_float(&pk, 3.14);

	msgpack_zone_init(&mempool, 50);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);
    	
	msgpack_zone_destroy(&mempool);
    	msgpack_sbuffer_destroy(&sbuf);
    }
    retval = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_spec);
    retval = clock_gettime(CLOCK_REALTIME, &end_time);
    long cpu_duration = (long)(1e9) * (end_spec.tv_sec - start_spec.tv_sec) + end_spec.tv_nsec - start_spec.tv_nsec;
    long duration = (long)(1e9) * (end_spec.tv_sec - start_spec.tv_sec) + end_spec.tv_nsec - start_spec.tv_nsec;
    /* print metrics */
    printf("\nTotal wall clock time: %ld nanoseconds\n", duration);
    printf("Average wall clock time per iteration: %ld nanoseconds\n",
           duration/ITERATIONS);
    printf("\nTotal CPU time : %ld nanoseconds\n", cpu_duration);
    printf("Average CPU time per iteration: %ld nanoseconds\n",
           (cpu_duration)/ITERATIONS);

    /* print mem usage stats */
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("\nMemory usage in kbytes : %ld\n",(usage.ru_maxrss/CONVERSION_VALUE));
    printf("\n");

    return 0;
}

