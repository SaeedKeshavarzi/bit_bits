/* byte_bytes.h
 * definitions for extracting and translating integers safely and portably
 * via pointers.
 */

#ifndef __BYTE_BYTES_H__
#define __BYTE_BYTES_H__

#pragma warning(disable : 26451)

#include <string.h>

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

/********************************************************************
 * utility functions for extracting and translating bytes
 */

/* increment buffer pointer 'buf' of custom byte-count length 'len' */
#define BYTE_INCREMENT(buf,len) \
    do { \
        (const uint8_t*&)(buf) += (len); \
    } while (0)

/********************************************************************
 * functions for extracting a single byte
 */

/* extract a const reference to single byte (8 bit)
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_8(buf,off) (*((const uint8_t*)(buf)+(off)))

/* extract a modifiable reference to single byte (8 bit)
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_8_REF(buf,off) (*((uint8_t*)(buf)+(off)))

/********************************************************************
 * functions for extracting bytes with big-endian representation
 */

/* extract a short (16 bit, 2 byte) with big-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_16(buf,off) ((uint32_t)*((const uint8_t*)(buf)+(off)+0)<<8|   \
                          (uint32_t)*((const uint8_t*)(buf)+(off)+1)<<0)

/* extract 3 byte (24 bit) with big-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_24(buf,off) ((uint32_t)*((const uint8_t*)(buf)+(off)+0)<<16|  \
                          (uint32_t)*((const uint8_t*)(buf)+(off)+1)<<8|   \
                          (uint32_t)*((const uint8_t*)(buf)+(off)+2)<<0)

/* extract a long (32 bit, 4 byte) with big-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_32(buf,off) ((uint32_t)*((const uint8_t*)(buf)+(off)+0)<<24|  \
                          (uint32_t)*((const uint8_t*)(buf)+(off)+1)<<16|  \
                          (uint32_t)*((const uint8_t*)(buf)+(off)+2)<<8|   \
                          (uint32_t)*((const uint8_t*)(buf)+(off)+3)<<0)

/* extract 5 byte (40 bit) with big-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_40(buf,off) ((uint64_t)*((const uint8_t*)(buf)+(off)+0)<<32|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+1)<<24|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+2)<<16|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+3)<<8|   \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+4)<<0)

/* extract 6 byte (48 bit) with big-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_48(buf,off) ((uint64_t)*((const uint8_t*)(buf)+(off)+0)<<40|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+1)<<32|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+2)<<24|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+3)<<16|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+4)<<8|   \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+5)<<0)

/* extract 7 byte (56 bit) with big-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_56(buf,off) ((uint64_t)*((const uint8_t*)(buf)+(off)+0)<<48|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+1)<<40|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+2)<<32|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+3)<<24|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+4)<<16|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+5)<<8|   \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+6)<<0)

/* extract a long long (64 bit, 8 byte) with big-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_64(buf,off) ((uint64_t)*((const uint8_t*)(buf)+(off)+0)<<56|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+1)<<48|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+2)<<40|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+3)<<32|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+4)<<24|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+5)<<16|  \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+6)<<8|   \
                          (uint64_t)*((const uint8_t*)(buf)+(off)+7)<<0)

/* extract bytes with custom length up to 8 byte with big-endian representation
 * buf ... buffer
 * len ... number of bytes
 * ret ... result variable
 */
#define BYTE_BYTES(buf,len,ret) \
    do { \
        if ((len) == 1) (ret) = BYTE_8(buf, 0); \
        else if ((len) == 2) (ret) = BYTE_16(buf, 0); \
        else if ((len) == 3) (ret) = BYTE_24(buf, 0); \
        else if ((len) == 4) (ret) = BYTE_32(buf, 0); \
        else if ((len) == 5) (ret) = BYTE_40(buf, 0); \
        else if ((len) == 6) (ret) = BYTE_48(buf, 0); \
        else if ((len) == 7) (ret) = BYTE_56(buf, 0); \
        else if ((len) == 8) (ret) = BYTE_64(buf, 0); \
    } while (0)

/* extract bytes with custom length up to 8 byte with big-endian representation and
 *     increment buffer pointer 'buf'
 * buf ... buffer
 * len ... number of bytes
 * ret ... result variable
 */
#define BYTE_BYTES_INC(buf,len,ret) \
    do { \
        BYTE_BYTES(buf, len, ret); \
        BYTE_INCREMENT(buf, len); \
    } while (0)

/* extract bytes with custom length up to 8 byte with big-endian representation
 * buf ... buffer
 * len ... number of bytes
 */
template<typename _RetTy, typename _BufTy, typename _LenTy>
static inline _RetTy byte_bytes(_BufTy buf, _LenTy len)
{
    _RetTy ret{};
    BYTE_BYTES(buf, len, ret);
    return ret;
}

/* extract bytes with custom length up to 8 byte with big-endian representation and
 *     increment buffer pointer 'buf'
 * buf ... buffer
 * len ... number of bytes
 */
template<typename _RetTy, typename _BufTy, typename _LenTy>
static inline _RetTy byte_bytes_inc(_BufTy & buf, _LenTy len)
{
    _RetTy ret{};
    BYTE_BYTES_INC(buf, len, ret);
    return ret;
}

/********************************************************************
 * Functions for extracting bytes with custom length from a source to a
 *     destination buffer
 */

/* extract bytes with custom length to a destination buffer 'dst'
 * buf ... source buffer
 * len ... number of bytes
 * dst ... destination buffer
 */
#define BYTE_BYTES_BUFFER(buf,len,dst) \
    do { \
        (void)memcpy((void*)(dst), (const void*)(buf), (std::size_t)(len)); \
    } while (0)

/* extract bytes with custom length to a destination buffer 'dst' and
 *     increment source buffer pointer 'buf'
 * buf ... source buffer
 * len ... number of bytes
 * dst ... destination buffer
 */
#define BYTE_BYTES_BUFFER_INC(buf,len,dst) \
    do { \
        BYTE_BYTES_BUFFER(buf, len, dst); \
        BYTE_INCREMENT(buf, len); \
    } while (0)

/********************************************************************
 * functions for extracting bytes with little-endian representation
 */

/* extract a short (16 bit, 2 byte) with little-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_16LE(buf,off) ((uint32_t)*((const uint8_t*)(buf)+(off)+1)<<8|   \
                            (uint32_t)*((const uint8_t*)(buf)+(off)+0)<<0)

/* extract 3 byte (24 bit) with little-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_24LE(buf,off) ((uint32_t)*((const uint8_t*)(buf)+(off)+2)<<16|  \
                            (uint32_t)*((const uint8_t*)(buf)+(off)+1)<<8|   \
                            (uint32_t)*((const uint8_t*)(buf)+(off)+0)<<0)

/* extract a long (32 bit, 4 byte) with little-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_32LE(buf,off) ((uint32_t)*((const uint8_t*)(buf)+(off)+3)<<24|  \
                            (uint32_t)*((const uint8_t*)(buf)+(off)+2)<<16|  \
                            (uint32_t)*((const uint8_t*)(buf)+(off)+1)<<8|   \
                            (uint32_t)*((const uint8_t*)(buf)+(off)+0)<<0)

/* extract 5 byte (40 bit) with little-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_40LE(buf,off) ((uint64_t)*((const uint8_t*)(buf)+(off)+4)<<32|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+3)<<24|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+2)<<16|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+1)<<8|   \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+0)<<0)

/* extract 6 byte (48 bit) with little-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_48LE(buf,off) ((uint64_t)*((const uint8_t*)(buf)+(off)+5)<<40|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+4)<<32|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+3)<<24|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+2)<<16|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+1)<<8|   \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+0)<<0)

/* extract 7 byte (56 bit) with little-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_56LE(buf,off) ((uint64_t)*((const uint8_t*)(buf)+(off)+6)<<48|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+5)<<40|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+4)<<32|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+3)<<24|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+2)<<16|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+1)<<8|   \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+0)<<0)

/* extract a long long (64 bit, 8 byte) with little-endian representation
 * buf ... buffer
 * off ... byte offset
 */
#define BYTE_64LE(buf,off) ((uint64_t)*((const uint8_t*)(buf)+(off)+7)<<56|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+6)<<48|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+5)<<40|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+4)<<32|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+3)<<24|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+2)<<16|  \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+1)<<8|   \
                            (uint64_t)*((const uint8_t*)(buf)+(off)+0)<<0)

/* extract bytes with custom length up to 8 byte with little-endian representation
 * buf ... buffer
 * len ... number of bytes
 * ret ... result variable
 */
#define BYTE_BYTES_LE(buf,len,ret) \
    do { \
        if ((len) == 1) (ret) = BYTE_8(buf, 0); \
        else if ((len) == 2) (ret) = BYTE_16LE(buf, 0); \
        else if ((len) == 3) (ret) = BYTE_24LE(buf, 0); \
        else if ((len) == 4) (ret) = BYTE_32LE(buf, 0); \
        else if ((len) == 5) (ret) = BYTE_40LE(buf, 0); \
        else if ((len) == 6) (ret) = BYTE_48LE(buf, 0); \
        else if ((len) == 7) (ret) = BYTE_56LE(buf, 0); \
        else if ((len) == 8) (ret) = BYTE_64LE(buf, 0); \
    } while (0)

/* extract bytes with custom length up to 8 byte with little-endian representation and
 *     increment buffer pointer 'buf'
 * buf ... buffer
 * len ... number of bytes
 * ret ... result variable
 */
#define BYTE_BYTES_LE_INC(buf,len,ret) \
    do { \
        BYTE_BYTES_LE(buf, len, ret); \
        BYTE_INCREMENT(buf, len); \
    } while (0)

/* extract bytes with custom length up to 8 byte with little-endian representation
 * buf ... buffer
 * len ... number of bytes
 */
template<typename _RetTy, typename _BufTy, typename _LenTy>
static inline _RetTy byte_bytes_le(_BufTy buf, _LenTy len)
{
    _RetTy ret{};
    BYTE_BYTES_LE(buf, len, ret);
    return ret;
}

/* extract bytes with custom length up to 8 byte with little-endian representation and
 *     increment buffer pointer 'buf'
 * buf ... buffer
 * len ... number of bytes
 */
template<typename _RetTy, typename _BufTy, typename _LenTy>
static inline _RetTy byte_bytes_le_inc(_BufTy & buf, _LenTy len)
{
    _RetTy ret{};
    BYTE_BYTES_LE_INC(buf, len, ret);
    return ret;
}

/********************************************************************
 * Functions for writing value to a destination buffer with big-endian representation
 */

/* write value to a destination buffer with custom length up to 8 byte with
 *     big-endian representation
 * buf ... destination buffer
 * len ... number of bytes
 * val ... value to write
 */
#define BYTE_WBYTES(buf,len,val) \
    do { \
        if ((len) <= 8) { \
            if ((len) >= 1) BYTE_8_REF(buf, 0) = (((val) >> (((len) - 1) << 3)) & 0xFF); \
            if ((len) >= 2) BYTE_8_REF(buf, 1) = (((val) >> (((len) - 2) << 3)) & 0xFF); \
            if ((len) >= 3) BYTE_8_REF(buf, 2) = (((val) >> (((len) - 3) << 3)) & 0xFF); \
            if ((len) >= 4) BYTE_8_REF(buf, 3) = (((val) >> (((len) - 4) << 3)) & 0xFF); \
            if ((len) >= 5) BYTE_8_REF(buf, 4) = (((val) >> (((len) - 5) << 3)) & 0xFF); \
            if ((len) >= 6) BYTE_8_REF(buf, 5) = (((val) >> (((len) - 6) << 3)) & 0xFF); \
            if ((len) >= 7) BYTE_8_REF(buf, 6) = (((val) >> (((len) - 7) << 3)) & 0xFF); \
            if ((len) == 8) BYTE_8_REF(buf, 7) = ((val) & 0xFF); \
        } \
    } while (0)

/* write value to a destination buffer with custom length up to 8 byte with
 *     big-endian representation and increment buffer pointer 'buf'
 * buf ... destination buffer
 * len ... number of bytes
 * val ... value to write
 */
#define BYTE_WBYTES_INC(buf,len,val) \
    do { \
        BYTE_WBYTES(buf, len, val); \
        BYTE_INCREMENT(buf, len); \
    } while (0)

/********************************************************************
 * Functions for writing value to a destination buffer with little-endian representation
 */

/* write value to a destination buffer with custom length up to 8 byte with
 *     little-endian representation
 * buf ... destination buffer
 * len ... number of bytes
 * val ... value to write
 */
#define BYTE_WBYTES_LE(buf,len,val) \
    do { \
        if ((len) <= 8) { \
            if ((len) >= 1) BYTE_8_REF(buf, 0) = ((val) & 0xFF); \
            if ((len) >= 2) BYTE_8_REF(buf, 1) = (((val) >> 8) & 0xFF); \
            if ((len) >= 3) BYTE_8_REF(buf, 2) = (((val) >> 16) & 0xFF); \
            if ((len) >= 4) BYTE_8_REF(buf, 3) = (((val) >> 24) & 0xFF); \
            if ((len) >= 5) BYTE_8_REF(buf, 4) = (((val) >> 32) & 0xFF); \
            if ((len) >= 6) BYTE_8_REF(buf, 5) = (((val) >> 40) & 0xFF); \
            if ((len) >= 7) BYTE_8_REF(buf, 6) = (((val) >> 48) & 0xFF); \
            if ((len) == 8) BYTE_8_REF(buf, 7) = (((val) >> 56) & 0xFF); \
        } \
    } while (0)

/* write value to a destination buffer with custom length up to 8 byte with
 *     little-endian representation and increment buffer pointer 'buf'
 * buf ... destination buffer
 * len ... number of bytes
 * val ... value to write
 */
#define BYTE_WBYTES_LE_INC(buf,len,val) \
    do { \
        BYTE_WBYTES_LE(buf, len, val); \
        BYTE_INCREMENT(buf, len); \
    } while (0)

/********************************************************************
 * Functions for writing bytes with custom length from a source to a
 *     destination buffer
 */

/* write bytes with custom length from a source buffer 'src'
 * buf ... destination buffer
 * len ... number of bytes
 * src ... source buffer
 */
#define BYTE_WBYTES_BUFFER(buf,len,src) \
    do { \
        (void)memcpy((void*)(buf), (const void*)(src), (std::size_t)(len)); \
    } while (0)

/* write bytes with custom length from a source buffer 'src' and
 *     increment destination buffer pointer 'buf'
 * buf ... destination buffer
 * len ... number of bytes
 * src ... source buffer
 */
#define BYTE_WBYTES_BUFFER_INC(buf,len,src) \
    do { \
        BYTE_WBYTES_BUFFER(buf, len, src); \
        BYTE_INCREMENT(buf, len); \
    } while (0)

#endif /* __BYTE_BYTES_H__ */
