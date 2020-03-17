/*
 * MessagePack for C dynamic typing routine
 *
 * Copyright (C) 2008-2009 FURUHASHI Sadayuki
 *
 *    Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *    http://www.boost.org/LICENSE_1_0.txt)
 */
#if defined(_KERNEL_MODE)
#  undef  _NO_CRT_STDIO_INLINE
#  define _NO_CRT_STDIO_INLINE
#endif

#include "msgpack/object.h"
#include "msgpack/pack.h"
#include <ctype.h>

#include <stdio.h>
#include <string.h>

//#if defined(_MSC_VER)
//#if _MSC_VER >= 1800
#include <inttypes.h>
//#else
//#define PRIu64 "I64u"
//#define PRIi64 "I64i"
//#define PRIi8 "i"
//#endif
//#else
//#include <inttypes.h>
//#endif
#  undef  PRIu64

#if defined(_KERNEL_MODE)
#  undef  snclog_info
#  define snclog_info _snclog_info
#endif

#include "fsl_debug_console.h"
#include "clog.h"

#define LOG_ZONE 'E'

int msgpack_pack_object(msgpack_packer* pk, msgpack_object d)
{
    switch(d.type) {
    case MSGPACK_OBJECT_NIL:
        return msgpack_pack_nil(pk);

    case MSGPACK_OBJECT_BOOLEAN:
        if(d.via.boolean) {
            return msgpack_pack_true(pk);
        } else {
            return msgpack_pack_false(pk);
        }

    case MSGPACK_OBJECT_POSITIVE_INTEGER:
        return msgpack_pack_uint64(pk, d.via.u64);

    case MSGPACK_OBJECT_NEGATIVE_INTEGER:
        return msgpack_pack_int64(pk, d.via.i64);

    case MSGPACK_OBJECT_FLOAT32:
        return msgpack_pack_float(pk, (float)d.via.f64);

    case MSGPACK_OBJECT_FLOAT64:
        return msgpack_pack_double(pk, d.via.f64);

    case MSGPACK_OBJECT_STR:
        {
            int ret = msgpack_pack_str(pk, d.via.str.size);
            if(ret < 0) { return ret; }
            return msgpack_pack_str_body(pk, d.via.str.ptr, d.via.str.size);
        }

    case MSGPACK_OBJECT_BIN:
        {
            int ret = msgpack_pack_bin(pk, d.via.bin.size);
            if(ret < 0) { return ret; }
            return msgpack_pack_bin_body(pk, d.via.bin.ptr, d.via.bin.size);
        }

    case MSGPACK_OBJECT_EXT:
        {
            int ret = msgpack_pack_ext(pk, d.via.ext.size, d.via.ext.type);
            if(ret < 0) { return ret; }
            return msgpack_pack_ext_body(pk, d.via.ext.ptr, d.via.ext.size);
        }

    case MSGPACK_OBJECT_ARRAY:
        {
            int ret = msgpack_pack_array(pk, d.via.array.size);
            if(ret < 0) {
                return ret;
            }
            else {
                msgpack_object* o = d.via.array.ptr;
                msgpack_object* const oend = d.via.array.ptr + d.via.array.size;
                for(; o != oend; ++o) {
                    ret = msgpack_pack_object(pk, *o);
                    if(ret < 0) { return ret; }
                }

                return 0;
            }
        }

    case MSGPACK_OBJECT_MAP:
        {
            int ret = msgpack_pack_map(pk, d.via.map.size);
            if(ret < 0) {
                return ret;
            }
            else {
                msgpack_object_kv* kv = d.via.map.ptr;
                msgpack_object_kv* const kvend = d.via.map.ptr + d.via.map.size;
                for(; kv != kvend; ++kv) {
                    ret = msgpack_pack_object(pk, kv->key);
                    if(ret < 0) { return ret; }
                    ret = msgpack_pack_object(pk, kv->val);
                    if(ret < 0) { return ret; }
                }

                return 0;
            }
        }

    default:
        return -1;
    }
}

#if !defined(_KERNEL_MODE)

static void msgpack_object_bin_print(FILE* out, const char *ptr, size_t size)
{
    size_t i;
    for (i = 0; i < size; ++i) {
        if (ptr[i] == '"') {
            clog_info("\\\"");
        } else if (isprint((unsigned char)ptr[i])) {
            clog_info(ptr[i]);
        } else {
            clog_info( "\\x%02x", (unsigned char)ptr[i]);
        }
    }
}

void msgpack_object_print(FILE* out, msgpack_object o)
{
    int i = 0;
    switch(o.type) {
    case MSGPACK_OBJECT_NIL:
        clog_info( "nil");
        break;

    case MSGPACK_OBJECT_BOOLEAN:
        clog_info( (o.via.boolean ? "true" : "false"));
        break;

    case MSGPACK_OBJECT_POSITIVE_INTEGER:
#if defined(PRIu64)
        clog_info( "%" PRIu64, o.via.u64);
#else
        if (o.via.u64 > ULONG_MAX)
            clog_info( "over 4294967295");
        else
            clog_info( "%d", (unsigned long)o.via.u64);
#endif
        break;

    case MSGPACK_OBJECT_NEGATIVE_INTEGER:
#if defined(PRIi64)
        clog_info( "%" PRIi64, o.via.i64);
#else
        if (o.via.i64 > LONG_MAX)
            clog_info( "over +2147483647");
        else if (o.via.i64 < LONG_MIN)
            clog_info( "under -2147483648");
        else
            clog_info( "%ld", (signed long)o.via.i64);
#endif
        break;

    case MSGPACK_OBJECT_FLOAT32:
    case MSGPACK_OBJECT_FLOAT64:
        clog_info( "%f", o.via.f64);
        break;

    case MSGPACK_OBJECT_STR:
        clog_info( "\"");
        //fwrite(o.via.str.ptr, o.via.str.size, 1, out);
        char *cptr = o.via.str.ptr;
        for (i=0; i<o.via.str.size; i++)
        {
            clog_info("%c", *cptr++);
        }
        clog_info( "\"");
        break;

    case MSGPACK_OBJECT_BIN:
        clog_info( "\"");
        msgpack_object_bin_print(out, o.via.bin.ptr, o.via.bin.size);
        clog_info( "\"");
        break;

    case MSGPACK_OBJECT_EXT:
#if defined(PRIi8)
        clog_info( "(ext: %" PRIi8 ")", o.via.ext.type);
#else
        clog_info( "(ext: %d)", (int)o.via.ext.type);
#endif
        clog_info( "\"");
        msgpack_object_bin_print(out, o.via.ext.ptr, o.via.ext.size);
        clog_info( "\"");
        break;

    case MSGPACK_OBJECT_ARRAY:
        clog_info( "[");
        if(o.via.array.size != 0) {
            msgpack_object* p = o.via.array.ptr;
            msgpack_object* const pend = o.via.array.ptr + o.via.array.size;
            msgpack_object_print(out, *p);
            ++p;
            for(; p < pend; ++p) {
                clog_info( ", ");
                msgpack_object_print(out, *p);
            }
        }
        clog_info( "]");
        break;

    case MSGPACK_OBJECT_MAP:
        clog_info( "{");
        if(o.via.map.size != 0) {
            msgpack_object_kv* p = o.via.map.ptr;
            msgpack_object_kv* const pend = o.via.map.ptr + o.via.map.size;
            msgpack_object_print(out, p->key);
            clog_info( "=>");
            msgpack_object_print(out, p->val);
            ++p;
            for(; p < pend; ++p) {
                clog_info( ", ");
                msgpack_object_print(out, p->key);
                clog_info( "=>");
                msgpack_object_print(out, p->val);
            }
        }
        clog_info( "}");
        break;

    default:
        // FIXME
#if defined(PRIu64)
        clog_info( "#<UNKNOWN %i %" PRIu64 ">", o.type, o.via.u64);
#else
        if (o.via.u64 > ULONG_MAX)
            clog_info( "#<UNKNOWN %i over 4294967295>", o.type);
        else
            clog_info( "#<UNKNOWN %i %lu>", o.type, (unsigned long)o.via.u64);
#endif

    }
}

#endif

#define MSGPACK_CHECKED_CALL(ret, func, aux_buffer, aux_buffer_size, ...) \
    ret = func(aux_buffer, aux_buffer_size, __VA_ARGS__);                 \
    if (ret <= 0 || ret >= (int)aux_buffer_size) return 0;                \
    aux_buffer = aux_buffer + ret;                                        \
    aux_buffer_size = aux_buffer_size - ret                               \

static int msgpack_object_bin_print_buffer(char *buffer, size_t buffer_size, const char *ptr, size_t size)
{
    size_t i;
    char *aux_buffer = buffer;
    size_t aux_buffer_size = buffer_size;
    int ret;

    for (i = 0; i < size; ++i) {
        if (ptr[i] == '"') {
            MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "\\\"");
        } else if (isprint((unsigned char)ptr[i])) {
            if (aux_buffer_size > 0) {
                memcpy(aux_buffer, ptr + i, 1);
                aux_buffer = aux_buffer + 1;
                aux_buffer_size = aux_buffer_size - 1;
            }
        } else {
            MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "\\x%02x", (unsigned char)ptr[i]);
        }
    }

    return (int)(buffer_size - aux_buffer_size);
}

int msgpack_object_print_buffer(char *buffer, size_t buffer_size, msgpack_object o)
{
    char *aux_buffer = buffer;
    size_t aux_buffer_size = buffer_size;
    int ret;
    switch(o.type) {
    case MSGPACK_OBJECT_NIL:
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "nil");
        break;

    case MSGPACK_OBJECT_BOOLEAN:
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, (o.via.boolean ? "true" : "false"));
        break;

    case MSGPACK_OBJECT_POSITIVE_INTEGER:
#if defined(PRIu64)
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "%" PRIu64, o.via.u64);
#else
        if (o.via.u64 > ULONG_MAX) {
            MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "over 4294967295");
        } else {
            MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "%lu", (unsigned long)o.via.u64);
        }
#endif
        break;

    case MSGPACK_OBJECT_NEGATIVE_INTEGER:
#if defined(PRIi64)
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "%" PRIi64, o.via.i64);
#else
        if (o.via.i64 > LONG_MAX) {
            MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "over +2147483647");
        } else if (o.via.i64 < LONG_MIN) {
            MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "under -2147483648");
        } else {
            MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "%ld", (signed long)o.via.i64);
        }
#endif
        break;

    case MSGPACK_OBJECT_FLOAT32:
    case MSGPACK_OBJECT_FLOAT64:
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "%f", o.via.f64);
        break;

    case MSGPACK_OBJECT_STR:
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "\"");
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "%.*s", (int)o.via.str.size, o.via.str.ptr);
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "\"");
        break;

    case MSGPACK_OBJECT_BIN:
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "\"");
        MSGPACK_CHECKED_CALL(ret, msgpack_object_bin_print_buffer, aux_buffer, aux_buffer_size, o.via.bin.ptr, o.via.bin.size);
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "\"");
        break;

    case MSGPACK_OBJECT_EXT:
#if defined(PRIi8)
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "(ext: %" PRIi8 ")", o.via.ext.type);
#else
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "(ext: %d)", (int)o.via.ext.type);
#endif
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "\"");
        MSGPACK_CHECKED_CALL(ret, msgpack_object_bin_print_buffer, aux_buffer, aux_buffer_size, o.via.ext.ptr, o.via.ext.size);
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "\"");
        break;

    case MSGPACK_OBJECT_ARRAY:
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "[");
        if(o.via.array.size != 0) {
            msgpack_object* p = o.via.array.ptr;
            msgpack_object* const pend = o.via.array.ptr + o.via.array.size;
            MSGPACK_CHECKED_CALL(ret, msgpack_object_print_buffer, aux_buffer, aux_buffer_size, *p);
            ++p;
            for(; p < pend; ++p) {
                MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, ", ");
                MSGPACK_CHECKED_CALL(ret, msgpack_object_print_buffer, aux_buffer, aux_buffer_size, *p);
            }
        }
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "]");
        break;

    case MSGPACK_OBJECT_MAP:
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "{");
        if(o.via.map.size != 0) {
            msgpack_object_kv* p = o.via.map.ptr;
            msgpack_object_kv* const pend = o.via.map.ptr + o.via.map.size;
            MSGPACK_CHECKED_CALL(ret, msgpack_object_print_buffer, aux_buffer, aux_buffer_size, p->key);
            MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "=>");
            MSGPACK_CHECKED_CALL(ret, msgpack_object_print_buffer, aux_buffer, aux_buffer_size, p->val);
            ++p;
            for(; p < pend; ++p) {
                MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, ", ");
                MSGPACK_CHECKED_CALL(ret, msgpack_object_print_buffer, aux_buffer, aux_buffer_size, p->key);
                MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "=>");
                MSGPACK_CHECKED_CALL(ret, msgpack_object_print_buffer, aux_buffer, aux_buffer_size, p->val);
            }
        }
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "}");
        break;

    default:
    // FIXME
#if defined(PRIu64)
        MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "#<UNKNOWN %i %" PRIu64 ">", o.type, o.via.u64);
#else
        if (o.via.u64 > ULONG_MAX) {
            MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "#<UNKNOWN %i over 4294967295>", o.type);
        } else {
            MSGPACK_CHECKED_CALL(ret, snclog_info, aux_buffer, aux_buffer_size, "#<UNKNOWN %i %lu>", o.type, (unsigned long)o.via.u64);
        }
#endif
    }

    return (int)(buffer_size - aux_buffer_size);
}

#undef MSGPACK_CHECKED_CALL

bool msgpack_object_equal(const msgpack_object x, const msgpack_object y)
{
    if(x.type != y.type) { return false; }

    switch(x.type) {
    case MSGPACK_OBJECT_NIL:
        return true;

    case MSGPACK_OBJECT_BOOLEAN:
        return x.via.boolean == y.via.boolean;

    case MSGPACK_OBJECT_POSITIVE_INTEGER:
        return x.via.u64 == y.via.u64;

    case MSGPACK_OBJECT_NEGATIVE_INTEGER:
        return x.via.i64 == y.via.i64;

    case MSGPACK_OBJECT_FLOAT32:
    case MSGPACK_OBJECT_FLOAT64:
        return x.via.f64 == y.via.f64;

    case MSGPACK_OBJECT_STR:
        return x.via.str.size == y.via.str.size &&
            memcmp(x.via.str.ptr, y.via.str.ptr, x.via.str.size) == 0;

    case MSGPACK_OBJECT_BIN:
        return x.via.bin.size == y.via.bin.size &&
            memcmp(x.via.bin.ptr, y.via.bin.ptr, x.via.bin.size) == 0;

    case MSGPACK_OBJECT_EXT:
        return x.via.ext.size == y.via.ext.size &&
            x.via.ext.type == y.via.ext.type &&
            memcmp(x.via.ext.ptr, y.via.ext.ptr, x.via.ext.size) == 0;

    case MSGPACK_OBJECT_ARRAY:
        if(x.via.array.size != y.via.array.size) {
            return false;
        } else if(x.via.array.size == 0) {
            return true;
        } else {
            msgpack_object* px = x.via.array.ptr;
            msgpack_object* const pxend = x.via.array.ptr + x.via.array.size;
            msgpack_object* py = y.via.array.ptr;
            do {
                if(!msgpack_object_equal(*px, *py)) {
                    return false;
                }
                ++px;
                ++py;
            } while(px < pxend);
            return true;
        }

    case MSGPACK_OBJECT_MAP:
        if(x.via.map.size != y.via.map.size) {
            return false;
        } else if(x.via.map.size == 0) {
            return true;
        } else {
            msgpack_object_kv* px = x.via.map.ptr;
            msgpack_object_kv* const pxend = x.via.map.ptr + x.via.map.size;
            msgpack_object_kv* py = y.via.map.ptr;
            do {
                if(!msgpack_object_equal(px->key, py->key) || !msgpack_object_equal(px->val, py->val)) {
                    return false;
                }
                ++px;
                ++py;
            } while(px < pxend);
            return true;
        }

    default:
        return false;
    }
}
