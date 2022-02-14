#ifndef __BIT_BITS_H__
#define __BIT_BITS_H__

#pragma warning(disable : 26451)

#include "byte_bytes.h"

/********************************************************************
 * Functions for working with nibbles and bits
 */

/********************************************************************
 * bitfield functions - for extracting bitfields from a buffer
 /

/* find the byte-address for the bitfield */
#define ADDR(bit) ((bit) >> 3)

/* find the offset (from the MSB) to the start of the bitfield */
#define OFFSET(bit) ((bit) & 0x07)

/* find the number of bytes involved in a bitfield */
#define INVOLVED_BYTES(bit,len) (1 + ADDR(OFFSET(bit) + (len) - 1))

/* find the number of bits involved in first byte.
 * 0 1 2 3 4 5 6 7 8 9 <- (bit)
 * 8 7 6 5 4 3 2 1 8 7 <- BIT_IN_FIRST(bit)
 */
#define BIT_IN_FIRST(bit) (8 - OFFSET(bit))

/* find the number of bits involved in last byte.
 * it is equivalent to '(1 + OFFSET((bit) + (len) - 1))'
 * 1 2 3 4 5 6 7 8 9 <- ((bit) + (len))
 * 1 2 3 4 5 6 7 8 1 <- SHIFT(bit, len)
 */
#define BIT_IN_LAST(bit,len) (1 + OFFSET((bit) + (len) + 7))

/* find the number of bits to shift right
 * it is equivalent to '(7 - OFFSET((bit) + (len) - 1))'
 * 1 2 3 4 5 6 7 8 9 <- ((bit) + (len))
 * 7 6 5 4 3 2 1 0 7 <- SHIFT(bit, len)
 */
#define SHIFT(bit,len) (7 - OFFSET((bit) + (len) + 7))

/* create a mask to mask off the bitfield */
#define MASK8(len)  ((uint32_t)0xFF >> (8 - (len)))
#define MASK16(len) ((uint32_t)0xFFFF >> (16 - (len)))
#define MASK32(len) ((uint32_t)0xFFFFFFFF >> (32 - (len)))
#define MASK64(len) ((uint64_t)0xFFFFFFFFFFFFFFFF >> (64 - (len)))

/* increment buffer pointer 'buf' and bit address 'bit' of custom bitfield length 'len' */
#define BIT_INCREMENT(buf,bit,len) \
    do { \
        BYTE_INCREMENT(buf, ADDR((bit) + (len))); \
        (bit) = OFFSET((bit) + (len)); \
    } while (0)

/* extract a single bit
 * buf ... buffer
 * bit ... bit address
 */
#define BIT_FLAG(buf,bit) \
    ((BYTE_8(buf, ADDR(bit)) >> SHIFT(bit, 1)) & MASK8(1))

/* extract bitfield which is in one byte
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 */
#define BIT_8(buf,bit,len) \
    ((BYTE_8(buf, ADDR(bit)) >> SHIFT(bit, len)) & MASK8(len))

/* extract bitfield which is in two consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 */
#define BIT_16(buf,bit,len) \
    ((BYTE_16(buf, ADDR(bit)) >> SHIFT(bit, len)) & MASK16(len))

/* extract bitfield which is in three consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 */
#define BIT_24(buf,bit,len) \
    ((BYTE_24(buf, ADDR(bit)) >> SHIFT(bit, len)) & MASK32(len))

/* extract bitfield which is in four consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 */
#define BIT_32(buf,bit,len) \
    ((BYTE_32(buf, ADDR(bit)) >> SHIFT(bit, len)) & MASK32(len))

/* extract bitfield which is in five consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 */
#define BIT_40(buf,bit,len) \
    ((BYTE_40(buf, ADDR(bit)) >> SHIFT(bit, len)) & MASK64(len))

/* extract bitfield which is in six consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 */
#define BIT_48(buf,bit,len) \
    ((BYTE_48(buf, ADDR(bit)) >> SHIFT(bit, len)) & MASK64(len))

/* extract bitfield which is in seven consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 */
#define BIT_56(buf,bit,len) \
    ((BYTE_56(buf, ADDR(bit)) >> SHIFT(bit, len)) & MASK64(len))

/* extract bitfield which is in eight consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 */
#define BIT_64(buf,bit,len) \
    ((BYTE_64(buf, ADDR(bit)) >> SHIFT(bit, len)) & MASK64(len))

/* extract bitfield with custom length up to 64 bits
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * ret ... result variable
 */
#define BIT_BITS(buf,bit,len,ret) \
    do { \
        int __involved_bytes__ = INVOLVED_BYTES(bit, len); \
             if (__involved_bytes__ == 1) (ret) =  BIT_8(buf, bit, len); \
        else if (__involved_bytes__ == 2) (ret) = BIT_16(buf, bit, len); \
        else if (__involved_bytes__ == 3) (ret) = BIT_24(buf, bit, len); \
        else if (__involved_bytes__ == 4) (ret) = BIT_32(buf, bit, len); \
        else if (__involved_bytes__ == 5) (ret) = BIT_40(buf, bit, len); \
        else if (__involved_bytes__ == 6) (ret) = BIT_48(buf, bit, len); \
        else if (__involved_bytes__ == 7) (ret) = BIT_56(buf, bit, len); \
        else if (__involved_bytes__ == 8) (ret) = BIT_64(buf, bit, len); \
        else if (__involved_bytes__ == 9) { \
            int __last_len__ = BIT_IN_LAST(bit, len); \
            (ret) = ((BIT_64(buf, bit, (len) - __last_len__) << __last_len__) | \
                ((uint64_t)BIT_8(buf, (bit) + ((len) - __last_len__), __last_len__))); \
        } \
    } while (0)

/* extract bitfield with custom length up to 64 bits and
 *     increment buffer pointer 'buf' and bit address 'bit'
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * ret ... result variable
 */
#define BIT_BITS_INC(buf,bit,len,ret) \
    do { \
        BIT_BITS(buf, bit, len, ret); \
        BIT_INCREMENT(buf, bit, len); \
    } while (0)

/* extract bitfield with custom length up to 64 bits
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 */
template<typename _RetTy, typename _BufTy, typename _LenTy, typename _BitTy>
static inline _RetTy bit_bits(_BufTy buf, _BitTy bit, _LenTy len)
{
    _RetTy ret{};
    BIT_BITS(buf, bit, len, ret);
    return ret;
}

/* extract bitfield with custom length up to 64 bits and
 *     increment buffer pointer 'buf' and bit address 'bit'
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 */
template<typename _RetTy, typename _BufTy, typename _LenTy, typename _BitTy>
static inline _RetTy bit_bits_inc(_BufTy & buf, _BitTy & bit, _LenTy len)
{
    _RetTy ret{};
    BIT_BITS_INC(buf, bit, len, ret);
    return ret;
}

/********************************************************************
 * bitfield functions - for writing bitfields to a buffer
 */

/* write a single bit
 * buf ... buffer
 * bit ... bit address
 * val ... value to write
 */
#define BIT_WFLAG(buf,bit,val) \
    ((BYTE_8_REF(buf, ADDR(bit)) &= ~(MASK8(1) << SHIFT(bit, 1))) |= (((val)&MASK8(1)) << SHIFT(bit, 1)))

/* write value in a bitfield which is in one byte
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * val ... value to write
 */
#define BIT_W8(buf,bit,len,val) \
    ((BYTE_8_REF(buf, ADDR(bit)) &= ~(MASK8(len) << SHIFT(bit, len))) |= (((val)&MASK8(len)) << SHIFT(bit, len)))

/* write value in a bitfield which is in two consecutive bytes
* buf ... buffer
* bit ... bit address
* len ... length of bitfield
* val ... value to write
*/
#define BIT_W16(buf,bit,len,val) \
    do { \
        int __first_len__ = BIT_IN_FIRST(bit); \
        int __last_len__ = (len) - __first_len__; \
        BIT_W8(buf, bit, __first_len__, (val) >> __last_len__); \
        BIT_W8(buf, (bit) + __first_len__, __last_len__, (val) & MASK8(__last_len__)); \
    } while (0)

/* write value in a bitfield which is in three consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * val ... value to write
 */
#define BIT_W24(buf,bit,len,val) \
    do { \
        int __first_len__ = BIT_IN_FIRST(bit); \
        int __last_len__ = (len) - (8 + __first_len__); \
        BIT_W8(buf, bit, __first_len__, (val) >> (8 + __last_len__)); \
        BYTE_8_REF(buf, ADDR(bit) + 1) = ((val) >> __last_len__) & 0xFF; \
        BIT_W8(buf, (bit) + (__first_len__ + 8), __last_len__, (val) & MASK8(__last_len__)); \
    } while (0)

/* write value in a bitfield which is in four consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * val ... value to write
 */
#define BIT_W32(buf,bit,len,val) \
    do { \
        int __first_len__ = BIT_IN_FIRST(bit); \
        int __last_len__ = (len) - (16 + __first_len__); \
        BIT_W8(buf, bit, __first_len__, (val) >> (16 + __last_len__)); \
        BYTE_8_REF(buf, ADDR(bit) + 1) = ((val) >> (8 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 2) = ((val) >> __last_len__) & 0xFF; \
        BIT_W8(buf, (bit) + (__first_len__ + 16), __last_len__, (val) & MASK8(__last_len__)); \
    } while (0)

/* write value in a bitfield which is in five consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * val ... value to write
 */
#define BIT_W40(buf,bit,len,val) \
    do { \
        int __first_len__ = BIT_IN_FIRST(bit); \
        int __last_len__ = (len) - (24 + __first_len__); \
        BIT_W8(buf, bit, __first_len__, (val) >> (24 + __last_len__)); \
        BYTE_8_REF(buf, ADDR(bit) + 1) = ((val) >> (16 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 2) = ((val) >> (8 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 3) = ((val) >> __last_len__) & 0xFF; \
        BIT_W8(buf, (bit) + (__first_len__ + 24), __last_len__, (val) & MASK8(__last_len__)); \
    } while (0)

/* write value in a bitfield which is in six consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * val ... value to write
 */
#define BIT_W48(buf,bit,len,val) \
    do { \
        int __first_len__ = BIT_IN_FIRST(bit); \
        int __last_len__ = (len) - (32 + __first_len__); \
        BIT_W8(buf, bit, __first_len__, (val) >> (32 + __last_len__)); \
        BYTE_8_REF(buf, ADDR(bit) + 1) = ((val) >> (24 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 2) = ((val) >> (16 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 3) = ((val) >> (8 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 4) = ((val) >> __last_len__) & 0xFF; \
        BIT_W8(buf, (bit) + (__first_len__ + 32), __last_len__, (val) & MASK8(__last_len__)); \
    } while (0)

/* write value in a bitfield which is in seven consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * val ... value to write
 */
#define BIT_W56(buf,bit,len,val) \
    do { \
        int __first_len__ = BIT_IN_FIRST(bit); \
        int __last_len__ = (len) - (40 + __first_len__); \
        BIT_W8(buf, bit, __first_len__, (val) >> (40 + __last_len__)); \
        BYTE_8_REF(buf, ADDR(bit) + 1) = ((val) >> (32 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 2) = ((val) >> (24 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 3) = ((val) >> (16 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 4) = ((val) >> (8 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 5) = ((val) >> __last_len__) & 0xFF; \
        BIT_W8(buf, (bit) + (__first_len__ + 40), __last_len__, (val) & MASK8(__last_len__)); \
    } while (0)

/* write value in a bitfield which is in eight consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * val ... value to write
 */
#define BIT_W64(buf,bit,len,val) \
    do { \
        int __first_len__ = BIT_IN_FIRST(bit); \
        int __last_len__ = (len) - (48 + __first_len__); \
        BIT_W8(buf, bit, __first_len__, (val) >> (48 + __last_len__)); \
        BYTE_8_REF(buf, ADDR(bit) + 1) = ((val) >> (40 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 2) = ((val) >> (32 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 3) = ((val) >> (24 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 4) = ((val) >> (16 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 5) = ((val) >> (8 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 6) = ((val) >> __last_len__) & 0xFF; \
        BIT_W8(buf, (bit) + (__first_len__ + 48), __last_len__, (val) & MASK8(__last_len__)); \
    } while (0)

/* write value in a bitfield which is in nine consecutive bytes
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * val ... value to write
 */
#define BIT_W72(buf,bit,len,val) \
    do { \
        int __first_len__ = BIT_IN_FIRST(bit); \
        int __last_len__ = (len) - (56 + __first_len__); \
        BIT_W8(buf, bit, __first_len__, (val) >> (56 + __last_len__)); \
        BYTE_8_REF(buf, ADDR(bit) + 1) = ((val) >> (48 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 2) = ((val) >> (40 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 3) = ((val) >> (32 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 4) = ((val) >> (24 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 5) = ((val) >> (16 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 6) = ((val) >> (8 + __last_len__)) & 0xFF; \
        BYTE_8_REF(buf, ADDR(bit) + 7) = ((val) >> __last_len__) & 0xFF; \
        BIT_W8(buf, (bit) + (__first_len__ + 56), __last_len__, (val) & MASK8(__last_len__)); \
    } while (0)

/* write value in a bitfield with custom length up to 64 bits
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * val ... value to write
 */
#define BIT_WBITS(buf,bit,len,val) \
    do { \
        int __involved_bytes__ = INVOLVED_BYTES(bit, len); \
             if (__involved_bytes__ == 1)  BIT_W8(buf, bit, len, val); \
        else if (__involved_bytes__ == 2) BIT_W16(buf, bit, len, val); \
        else if (__involved_bytes__ == 3) BIT_W24(buf, bit, len, val); \
        else if (__involved_bytes__ == 4) BIT_W32(buf, bit, len, val); \
        else if (__involved_bytes__ == 5) BIT_W40(buf, bit, len, val); \
        else if (__involved_bytes__ == 6) BIT_W48(buf, bit, len, val); \
        else if (__involved_bytes__ == 7) BIT_W56(buf, bit, len, val); \
        else if (__involved_bytes__ == 8) BIT_W64(buf, bit, len, val); \
        else if (__involved_bytes__ == 9) BIT_W72(buf, bit, len, val); \
    } while (0)

/* write value in a bitfield with custom length up to 64 bits and 
 *     increment buffer pointer 'buf' and bit address 'bit'
 * buf ... buffer
 * bit ... bit address
 * len ... length of bitfield
 * val ... value to write
 */
#define BIT_WBITS_INC(buf,bit,len,val) \
    do { \
        BIT_WBITS(buf, bit, len, val); \
        BIT_INCREMENT(buf, bit, len); \
    } while (0)

/********************************************************************
 * Functions for writing bits with custom length from a source to a
 *     destination buffer
 */

/* write bits with custom length from a source buffer 'src'
 * buf ... destination buffer
 * bit ... bit address
 * len ... length of bitfield
 * src ... source buffer
 * src_bit source bit address
 */
#define BIT_WBITS_BUFFER(buf,bit,len,src,src_bit) \
    do { \
        uint64_t __bin__ = 0; \
        int __dst_bit__ = (int)(bit); \
        int __rem_len__ = (int)(len); \
        int __src_bit__ = (int)(src_bit); \
        while (__rem_len__ > 64) { \
            BIT_BITS(src, __src_bit__, 64, __bin__); \
            BIT_WBITS(buf, __dst_bit__, 64, __bin__); \
            __src_bit__ += 64; \
            __dst_bit__ += 64; \
            __rem_len__ -= 64; \
        } \
        if (__rem_len__ > 0) { \
            BIT_BITS(src, __src_bit__, __rem_len__, __bin__); \
            BIT_WBITS(buf, __dst_bit__, __rem_len__, __bin__); \
        } \
    } while (0)

/* write bits with custom length from a source buffer 'src' and
 *     increment destination buffer pointer 'buf' and bit address 'bit'
 * buf ... destination buffer
 * bit ... bit address
 * len ... length of bitfield
 * src ... source buffer
 * src_bit source bit address
 */
#define BIT_WBITS_BUFFER_INC(buf,bit,len,src,src_bit) \
    do { \
        BIT_WBITS_BUFFER(buf, bit, len, src, src_bit); \
        BIT_INCREMENT(buf, bit, len); \
    } while (0)

/********************************************************************
 * Functions for extracting bits with custom length from a source to a
 *     destination buffer
 */

/* extract bits with custom length to a destination buffer 'dst'
 * buf ... source buffer
 * bit ... bit address
 * len ... length of bitfield
 * dst ... destination buffer
 * dst_bit destination bit address
 */
#define BIT_BITS_BUFFER(buf,bit,len,dst,dst_bit) \
    do { \
        uint64_t __bin__ = 0; \
        int __src_bit__ = (int)(bit); \
        int __rem_len__ = (int)(len); \
        int __dst_bit__ = (int)(dst_bit); \
        while (__rem_len__ > 64) { \
            BIT_BITS(buf, __src_bit__, 64, __bin__); \
            BIT_WBITS(dst, __dst_bit__, 64, __bin__); \
            __src_bit__ += 64; \
            __dst_bit__ += 64; \
            __rem_len__ -= 64; \
        } \
        if (__rem_len__ > 0) { \
            BIT_BITS(buf, __src_bit__, __rem_len__, __bin__); \
            BIT_WBITS(dst, __dst_bit__, __rem_len__, __bin__); \
        } \
    } while (0)

/* extract bits with custom length to a destination buffer 'dst' and
 *     increment source buffer pointer 'buf' and bit address 'bit'
 * buf ... source buffer
 * bit ... bit address
 * len ... length of bitfield
 * dst ... destination buffer
 * dst_bit destination bit address
 */
#define BIT_BITS_BUFFER_INC(buf,bit,len,dst,dst_bit) \
    do { \
        BIT_BITS_BUFFER(buf, bit, len, dst, dst_bit); \
        BIT_INCREMENT(buf, bit, len); \
    } while (0)

#endif /* __BIT_BITS_H__ */
