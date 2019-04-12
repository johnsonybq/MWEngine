/// @ref gtx_normalize_dot

namespace Core
{
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T normalizeDot(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		return Core::dot(x, y) * Core::inversesqrt(Core::dot(x, x) * Core::dot(y, y));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T fastNormalizeDot(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		return Core::dot(x, y) * Core::fastInverseSqrt(Core::dot(x, x) * Core::dot(y, y));
	}
}//namespace Core
