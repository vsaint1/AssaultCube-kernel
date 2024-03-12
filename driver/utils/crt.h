#pragma once

#define to_lower_c(Char) ((Char >= (char*)'A' && Char <= (char*)'Z') ? (Char + 32) : Char)

namespace crt
{
	template <typename t>
	__forceinline int strlen(t str) {
		if (!str)
		{
			return 0;
		}

		t buffer = str;

		while (*buffer)
		{
			*buffer++;
		}

		return (int)(buffer - str);
	}

	inline bool strcmp(const char* src, const char* dst)
	{
		if (!src || !dst)
		{
			return true;
		}

		const auto src_sz = crt::strlen(src);
		const auto dst_sz = crt::strlen(dst);

		if (src_sz != dst_sz)
		{
			return true;
		}

		for (int i = 0; i < src_sz; i++)
		{
			if (src[i] != dst[i])
			{
				return true;
			}
		}

		return false;
	}

	inline int strtoi(const char* str)
	{
		int result = 0;
		while (*str)
		{
			result *= 10;
			result += *str++ - '0';
		}
		return result;
	}

	inline const char* to_lower(char* str) {

		char* str_low = "";
		for (char* pointer = str; *pointer != '\0'; ++pointer)
		{
			*str_low = (char)(short)tolower(*pointer);
		}

		return str_low;
	}
}
