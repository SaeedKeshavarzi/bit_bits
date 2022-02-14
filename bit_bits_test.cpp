#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#include "bit_bits.h"

static void fill_byte_and_bits(uint8_t& byte, uint8_t* bits)
{
	bits[0] = (std::rand() & 0x01);
	bits[1] = (std::rand() & 0x01);
	bits[2] = (std::rand() & 0x01);
	bits[3] = (std::rand() & 0x01);
	bits[4] = (std::rand() & 0x01);
	bits[5] = (std::rand() & 0x01);
	bits[6] = (std::rand() & 0x01);
	bits[7] = (std::rand() & 0x01);

	byte = (bits[0] << 7) | (bits[1] << 6) | (bits[2] << 5) | (bits[3] << 4) |
		(bits[4] << 3) | (bits[5] << 2) | (bits[6] << 1) | bits[7];
}

static bool bit_bits_test(const uint8_t* bit_array, const int bit_count, const uint8_t* byte_array, const int byte_count)
{
	// BIT_FLAG(buf,bit)
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
		if (BIT_FLAG(byte_array, bit_index) != bit_array[bit_index])
			return false;

	// BIT_8(buf,bit,len)
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
	{
		for (int bit_field_len = 1; bit_field_len <= 8; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				continue;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 1)
				continue;

			uint64_t result = BIT_8(byte_array, bit_index, bit_field_len);

			uint64_t desired = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				desired = (desired << 1) | (bit_array[cnt] & 0x01);

			if (result != desired)
				return false;
		}
	}

	// BIT_16(buf,bit,len)
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
	{
		for (int bit_field_len = 2; bit_field_len <= 16; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				continue;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 2)
				continue;

			uint64_t result = BIT_16(byte_array, bit_index, bit_field_len);

			uint64_t desired = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				desired = (desired << 1) | (bit_array[cnt] & 0x01);

			if (result != desired)
				return false;
		}
	}

	// BIT_24(buf,bit,len)
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
	{
		for (int bit_field_len = 10; bit_field_len <= 24; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				continue;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 3)
				continue;

			uint64_t result = BIT_24(byte_array, bit_index, bit_field_len);

			uint64_t desired = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				desired = (desired << 1) | (bit_array[cnt] & 0x01);

			if (result != desired)
				return false;
		}
	}

	// BIT_32(buf,bit,len)
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
	{
		for (int bit_field_len = 18; bit_field_len <= 32; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				continue;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 4)
				continue;

			uint64_t result = BIT_32(byte_array, bit_index, bit_field_len);

			uint64_t desired = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				desired = (desired << 1) | (bit_array[cnt] & 0x01);

			if (result != desired)
				return false;
		}
	}

	// BIT_40(buf,bit,len)
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
	{
		for (int bit_field_len = 26; bit_field_len <= 40; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				continue;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 5)
				continue;

			uint64_t result = BIT_40(byte_array, bit_index, bit_field_len);

			uint64_t desired = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				desired = (desired << 1) | (bit_array[cnt] & 0x01);

			if (result != desired)
				return false;
		}
	}

	// BIT_48(buf,bit,len)
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
	{
		for (int bit_field_len = 34; bit_field_len <= 48; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				continue;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 6)
				continue;

			uint64_t result = BIT_48(byte_array, bit_index, bit_field_len);

			uint64_t desired = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				desired = (desired << 1) | (bit_array[cnt] & 0x01);

			if (result != desired)
				return false;
		}
	}

	// BIT_56(buf,bit,len)
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
	{
		for (int bit_field_len = 42; bit_field_len <= 56; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				continue;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 7)
				continue;

			uint64_t result = BIT_56(byte_array, bit_index, bit_field_len);

			uint64_t desired = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				desired = (desired << 1) | (bit_array[cnt] & 0x01);

			if (result != desired)
				return false;
		}
	}

	// BIT_64(buf,bit,len)
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
	{
		for (int bit_field_len = 50; bit_field_len <= 64; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				continue;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 8)
				continue;

			uint64_t result = BIT_64(byte_array, bit_index, bit_field_len);

			uint64_t desired = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				desired = (desired << 1) | (bit_array[cnt] & 0x01);

			if (result != desired)
				return false;
		}
	}

	// BIT_BITS(buf,bit,len,ret)
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
	{
		for (int bit_field_len = 1; bit_field_len <= 64; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				continue;

			uint64_t result;
			BIT_BITS(byte_array, bit_index, bit_field_len, result);

			uint64_t desired = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				desired = (desired << 1) | (bit_array[cnt] & 0x01);

			if (result != desired)
				return false;
		}
	}

	// BIT_BITS_INC(buf,bit,len,ret)
	{
		uint8_t* byte_array_local = (uint8_t*)byte_array;
		for (int bit_index = 0, bit_index_local = 0; bit_index < bit_count; /*_*/)
		{
			int bit_field_len;
			if (bit_count - bit_index >= 64)
				bit_field_len = 1 + (std::rand() & 0x3f); /* 1 - 64 */
			else
				bit_field_len = 1 + (std::rand() % (bit_count - bit_index)); /* 1 - (bit_count - bit_index) */

			uint64_t result{};
			BIT_BITS_INC(byte_array_local, bit_index_local, bit_field_len, result);

			uint64_t desired = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				desired = (desired << 1) | (bit_array[cnt] & 0x01);

			if (result != desired)
				return false;

			bit_index += bit_field_len;
		}
	}

	// BIT_BITS_BUFFER(buf,bit,len,dst)
	{
		uint8_t* result_array = new uint8_t[25];
		uint8_t* desired_array = new uint8_t[25];

		for (int bit_index = 0; bit_index < 64; ++bit_index)
		{
			for (int bit_field_len = 1; bit_field_len <= 192; ++bit_field_len)
			{
				if (bit_index + bit_field_len > bit_count)
					continue;

				int dest_bit_index = (std::rand() & 0x07);

				memset(result_array, 0x55, 25);
				BIT_BITS_BUFFER(byte_array, bit_index, bit_field_len, result_array, dest_bit_index);

				memset(desired_array, 0x55, 25);
				for (int cnt = 0; cnt < bit_field_len; ++cnt)
					BIT_WFLAG(desired_array, dest_bit_index + cnt, bit_array[bit_index + cnt]);

				if (memcmp(result_array, desired_array, 25) != 0)
					return false;
			}
		}

		delete[] result_array;
		delete[] desired_array;
	}

	// BIT_BITS_BUFFER_INC(buf,bit,len,dst)
	{
		uint8_t* byte_array_iterator = (uint8_t*)byte_array;

		uint8_t* result_array = new uint8_t[byte_count];
		memset(result_array, 0x55, byte_count);
		uint8_t* result_array_iterator = result_array;

		for (int bit_index = 0, remained_bits = bit_count; remained_bits > 0; /*_*/)
		{
			int bit_field_len;
			if (remained_bits >= 191)
				bit_field_len = 65 + (std::rand() % (191 - 65 + 1)); /* 65 - 191 */
			else if (remained_bits >= 65)
				bit_field_len = 65 + (std::rand() % (remained_bits - 65 + 1)) /* 65 - remained_bits */;
			else
				bit_field_len = 1 + (std::rand() % remained_bits); /* 1 - remained_bits */

			BIT_BITS_BUFFER_INC(byte_array_iterator, bit_index, bit_field_len, result_array_iterator, bit_index);
			result_array_iterator = result_array + (byte_array_iterator - byte_array);
			remained_bits -= bit_field_len;
		}

		if (memcmp(result_array, byte_array, byte_count) != 0)
			return false;

		delete[] result_array;
	}

	return true;
}

static bool bit_bits_test_launcher()
{
	const int byte_count = 100;
	const int bit_count = (byte_count << 3);

	uint8_t* byte_array = new uint8_t[byte_count];
	uint8_t* bit_array = new uint8_t[bit_count];

	bool ret = true;

	{
		using namespace std::chrono;

		printf("#\nbit_bits_test: \n#\n");
		auto t0 = steady_clock::now();
		auto t1 = t0;
		for (int rep = 0; rep < 10'000; ++rep)
		{
			for (int i = 0; i < byte_count; ++i)
				fill_byte_and_bits(byte_array[i], bit_array + 8 * i);

			if (bit_bits_test(bit_array, bit_count, byte_array, byte_count) == false)
			{
				printf("test failed! \n");
				ret = false;
				break;
			}

			auto t2 = steady_clock::now();
			if (duration_cast<milliseconds>(t2 - t1).count() > 600)
			{
				printf("%5.2f %% \n", ((double)rep * 100) / 10'000);
				t1 = t2;
			}
		}

		printf("Ellapsed Time: %.2f sec \n", duration_cast<duration<double>>(steady_clock::now() - t0).count());
	}

	delete[] byte_array;
	delete[] bit_array;

	return ret;
}

static bool bit_wbits_test(const uint8_t* bit_array, const int bit_count, const uint8_t* byte_array, const int byte_count, uint8_t* test_array)
{
	// BIT_WFLAG(buf,bit,val)
	memset(test_array, 0x55, byte_count);
	for (int bit_index = 0; bit_index < bit_count; ++bit_index)
		BIT_WFLAG(test_array, bit_index, bit_array[bit_index] & 0x01);

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_W8(buf,bit,len,val)
	memset(test_array, 0x55, byte_count);
	for (int bit_index = 0; bit_index < bit_count; /*_*/)
	{
		for (int bit_field_len = 1; bit_field_len <= 8; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				break;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 1)
				continue;

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_W8(test_array, bit_index, bit_field_len, value);

			bit_index += bit_field_len;
		}
	}

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_W16(buf,bit,len,val)
	memset(test_array, 0x55, byte_count);
	memcpy(test_array + byte_count - 1, byte_array + byte_count - 1, 1);
	for (int bit_index = 0; bit_index < bit_count - 8; /*_*/)
	{
		for (int bit_field_len = 2; bit_field_len <= 16; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				break;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 2)
				continue;

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_W16(test_array, bit_index, bit_field_len, value);

			bit_index += bit_field_len;
		}
	}

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_W24(buf,bit,len,val)
	memset(test_array, 0x55, byte_count);
	memcpy(test_array + byte_count - 2, byte_array + byte_count - 2, 2);
	for (int bit_index = 0; bit_index < bit_count - 16; /*_*/)
	{
		for (int bit_field_len = 10; bit_field_len <= 24; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				break;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 3)
				continue;

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_W24(test_array, bit_index, bit_field_len, value);

			bit_index += bit_field_len;
		}
	}

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_W32(buf,bit,len,val)
	memset(test_array, 0x55, byte_count);
	memcpy(test_array + byte_count - 3, byte_array + byte_count - 3, 3);
	for (int bit_index = 0; bit_index < bit_count - 24; /*_*/)
	{
		for (int bit_field_len = 18; bit_field_len <= 32; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				break;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 4)
				continue;

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_W32(test_array, bit_index, bit_field_len, value);

			bit_index += bit_field_len;
		}
	}

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_W40(buf,bit,len,val)
	memset(test_array, 0x55, byte_count);
	memcpy(test_array + byte_count - 4, byte_array + byte_count - 4, 4);
	for (int bit_index = 0; bit_index < bit_count - 32; /*_*/)
	{
		for (int bit_field_len = 26; bit_field_len <= 40; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				break;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 5)
				continue;

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_W40(test_array, bit_index, bit_field_len, value);

			bit_index += bit_field_len;
		}
	}

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_W48(buf,bit,len,val)
	memset(test_array, 0x55, byte_count);
	memcpy(test_array + byte_count - 5, byte_array + byte_count - 5, 5);
	for (int bit_index = 0; bit_index < bit_count - 40; /*_*/)
	{
		for (int bit_field_len = 34; bit_field_len <= 48; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				break;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 6)
				continue;

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_W48(test_array, bit_index, bit_field_len, value);

			bit_index += bit_field_len;
		}
	}

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_W56(buf,bit,len,val)
	memset(test_array, 0x55, byte_count);
	memcpy(test_array + byte_count - 6, byte_array + byte_count - 6, 6);
	for (int bit_index = 0; bit_index < bit_count - 48; /*_*/)
	{
		for (int bit_field_len = 42; bit_field_len <= 56; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				break;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 7)
				continue;

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_W56(test_array, bit_index, bit_field_len, value);

			bit_index += bit_field_len;
		}
	}

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_W64(buf,bit,len,val)
	memset(test_array, 0x55, byte_count);
	memcpy(test_array + byte_count - 7, byte_array + byte_count - 7, 7);
	for (int bit_index = 0; bit_index < bit_count - 56; /*_*/)
	{
		for (int bit_field_len = 50; bit_field_len <= 64; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				break;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 8)
				continue;

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_W64(test_array, bit_index, bit_field_len, value);

			bit_index += bit_field_len;
		}
	}

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_W72(buf,bit,len,val)
	memset(test_array, 0x55, byte_count);
	memcpy(test_array + byte_count - 8, byte_array + byte_count - 8, 8);
	for (int bit_index = 0; bit_index < bit_count - 64; /*_*/)
	{
		if (OFFSET(bit_index) == 0)
		{
			BIT_WFLAG(test_array, bit_index, bit_array[bit_index] & 0x01);
			bit_index += 1;
		}

		for (int bit_field_len = 58; bit_field_len <= 64; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				break;

			if (INVOLVED_BYTES(bit_index, bit_field_len) != 9)
				continue;

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_W72(test_array, bit_index, bit_field_len, value);

			bit_index += bit_field_len;
		}
	}

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_WBITS(buf,bit,len,val)
	memset(test_array, 0x55, byte_count);
	for (int bit_index = 0; bit_index < bit_count; /*_*/)
	{
		for (int bit_field_len = 1; bit_field_len <= 64; ++bit_field_len)
		{
			if (bit_index + bit_field_len > bit_count)
				break;

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_WBITS(test_array, bit_index, bit_field_len, value);

			bit_index += bit_field_len;
		}
	}

	if (memcmp(byte_array, test_array, byte_count) != 0)
		return false;

	// BIT_WBITS_INC(buf,bit,len,val)
	{
		memset(test_array, 0x55, byte_count);
		uint8_t* test_array_local = (uint8_t*)test_array;
		for (int bit_index = 0, bit_index_local = 0; bit_index < bit_count; /*_*/)
		{
			int bit_field_len;
			if (bit_count - bit_index >= 64)
				bit_field_len = 1 + (std::rand() & 0x3f); /* 1 - 64 */
			else
				bit_field_len = 1 + (std::rand() % (bit_count - bit_index)); /* 1 - (bit_count - bit_index) */

			uint64_t value = bit_array[bit_index] & 0x01;
			for (int cnt = bit_index + 1; cnt < bit_index + bit_field_len; ++cnt)
				value = (value << 1) | (bit_array[cnt] & 0x01);

			BIT_WBITS_INC(test_array_local, bit_index_local, bit_field_len, value);

			bit_index += bit_field_len;
		}

		if (memcmp(byte_array, test_array, byte_count) != 0)
			return false;
	}

	// BIT_WBITS_BUFFER(buf,bit,len,dst)
	{
		uint8_t* result_array = new uint8_t[25];
		uint8_t* desired_array = new uint8_t[25];

		for (int bit_index = 0; bit_index < 64; ++bit_index)
		{
			for (int bit_field_len = 1; bit_field_len <= 192; ++bit_field_len)
			{
				if (bit_index + bit_field_len > bit_count)
					continue;

				int dest_bit_index = (std::rand() & 0x07);

				memset(result_array, 0x55, 25);
				BIT_WBITS_BUFFER(result_array, dest_bit_index, bit_field_len, byte_array, bit_index);

				memset(desired_array, 0x55, 25);
				for (int cnt = 0; cnt < bit_field_len; ++cnt)
					BIT_WFLAG(desired_array, dest_bit_index + cnt, bit_array[bit_index + cnt]);

				if (memcmp(result_array, desired_array, 25) != 0)
					return false;
			}
		}

		delete[] result_array;
		delete[] desired_array;
	}

	// BIT_WBITS_BUFFER_INC(buf,bit,len,dst)
	{
		memset(test_array, 0x55, byte_count);
		uint8_t* write_array_iterator = (uint8_t*)test_array;
		uint8_t* byte_array_iterator = (uint8_t*)byte_array;
		for (int bit_index = 0, remained_bits = bit_count; remained_bits > 0; /*_*/)
		{
			int bit_field_len;
			if (remained_bits >= 191)
				bit_field_len = 65 + (std::rand() % (191 - 65 + 1)); /* 65 - 191 */
			else if (remained_bits >= 65)
				bit_field_len = 65 + (std::rand() % (remained_bits - 65 + 1)) /* 65 - remained_bits */;
			else
				bit_field_len = 1 + (std::rand() % remained_bits); /* 1 - remained_bits */

			BIT_WBITS_BUFFER_INC(write_array_iterator, bit_index, bit_field_len, byte_array_iterator, bit_index);
			byte_array_iterator = (uint8_t*)byte_array + (write_array_iterator - test_array);
			remained_bits -= bit_field_len;
		}

		if (memcmp(test_array, byte_array, byte_count) != 0)
			return false;
	}

	return true;
}

static bool bit_wbits_test_launcher()
{
	const int byte_count = 1010;
	const int bit_count = (byte_count << 3);

	uint8_t* bit_array = new uint8_t[bit_count];
	uint8_t* byte_array = new uint8_t[byte_count];
	uint8_t* test_array = new uint8_t[byte_count];

	bool ret = true;

	{
		using namespace std::chrono;
		printf("#\nbit_wbits_test: \n#\n");

		auto t0 = steady_clock::now();
		auto t1 = t0;
		for (int rep = 0; rep < 20'000; ++rep)
		{
			for (int i = 0; i < byte_count; ++i)
				fill_byte_and_bits(byte_array[i], bit_array + i * 8);

			if (bit_wbits_test(bit_array, bit_count, byte_array, byte_count, test_array) == false)
			{
				printf("test failed! \n");
				ret = false;
				break;
			}

			auto t2 = steady_clock::now();
			if (duration_cast<milliseconds>(t2 - t1).count() > 600)
			{
				printf("%5.2f %% \n", ((double)rep * 100) / 20'000);
				t1 = t2;
			}
		}

		printf("Ellapsed Time: %.2f sec \n", duration_cast<duration<double>>(steady_clock::now() - t0).count());
	}

	delete[] bit_array;
	delete[] byte_array;
	delete[] test_array;

	return ret;
}

int main()
{
	bit_bits_test_launcher();
	bit_wbits_test_launcher();

	printf("\npress any key to continue ");
	(void)getchar();
	return 0;
}
