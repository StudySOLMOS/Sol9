#pragma once

#include <algorithm>
#include <utility>

typedef unsigned __int8 u8;
typedef signed __int8 s8;
typedef char c8;

typedef unsigned __int16 u16;
typedef signed __int16 s16;

typedef unsigned __int32 u32;
typedef signed __int32 s32;

typedef float f32;
typedef double f64;

namespace sol9
{
	#ifdef PI
	#undef PI
	#endif

		const f32 PI				= 3.14159265359f;
		const f32 HALF_PI			= PI / 2.0f;
		const f32 RECIPROCAL_PI		= 1.0f / PI;

		const f32 DEG2RAD			= PI / 180.0f;
		const f32 RAD2DEG			= 180.0f / PI;

		__forceinline f32 deg2rad(const f32 degrees)
		{
			return DEG2RAD * degrees;
		}

		__forceinline f32 rad2deg(const f32 radians)
		{
			return RAD2DEG * radians;
		}

	#ifdef PI64
	#undef PI64
	#endif

		const f64 PI64				= 3.1415926535897932384626433832795028841971693993751;
		const f64 HALF_PI64			= PI64 / 2.0;
		const f64 RECIPROCAL_PI64	= 1.0 / PI64;

		const f64 DEG2RAD64			= PI64 / 180.0;
		const f64 RAD2DEG64			= 180.0 / PI64;

		__forceinline f64 deg2rad(const f64& degrees)
		{
			return DEG2RAD64 * degrees;
		}

		__forceinline f64 rad2deg(const f64& radians)
		{
			return RAD2DEG64 * radians;
		}

	const f32 ROUNDING_ERROR = 0.000001f;

	template <typename T>
	__forceinline bool equals(const T& a, const T& b, const T& tolerance = (T)ROUNDING_ERROR)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	template <typename T>
	__forceinline bool isZero(const T& value, const T& tolerance = (T)ROUNDING_ERROR)
	{
		return equals(value, (T)0, tolerance);
	}

	template <typename T>
	__forceinline T clamp(const T& value, const T& low, const T& high)
	{
		return std::min(std::max(value, low), high);
	}

	template <typename T>
	__forceinline T saturate(const T& value)
	{
		return clamp(value, (T)0, (T)1);
	}

	template <typename T>
	__forceinline T lerp(const T& a, const T& b, const f32 t)
	{
		return (T)(saturate(t) * (b - a) + a);
	}

	__forceinline bool toggle(bool b)
	{
		return b = !b;
	}
} // namespace sol9