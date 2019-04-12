/// @ref gtx_hash
///
/// @see core (dependence)
///
/// @defgroup gtx_hash GLM_GTX_hash
/// @ingroup gtx
///
/// @brief Add std::hash support for glm types
///
/// <glm/gtx/hash.inl> need to be included to use the features of this extension.

namespace Core {
namespace detail
{
	GLM_INLINE void hash_combine(size_t &seed, size_t hash)
	{
		hash += 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= hash;
	}
}}

namespace std
{
	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::vec<1, T, Q>>::operator()(Core::vec<1, T, Q> const& v) const
	{
		hash<T> hasher;
		return hasher(v.x);
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::vec<2, T, Q>>::operator()(Core::vec<2, T, Q> const& v) const
	{
		size_t seed = 0;
		hash<T> hasher;
		Core::detail::hash_combine(seed, hasher(v.x));
		Core::detail::hash_combine(seed, hasher(v.y));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::vec<3, T, Q>>::operator()(Core::vec<3, T, Q> const& v) const
	{
		size_t seed = 0;
		hash<T> hasher;
		Core::detail::hash_combine(seed, hasher(v.x));
		Core::detail::hash_combine(seed, hasher(v.y));
		Core::detail::hash_combine(seed, hasher(v.z));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::vec<4, T, Q>>::operator()(Core::vec<4, T, Q> const& v) const
	{
		size_t seed = 0;
		hash<T> hasher;
		Core::detail::hash_combine(seed, hasher(v.x));
		Core::detail::hash_combine(seed, hasher(v.y));
		Core::detail::hash_combine(seed, hasher(v.z));
		Core::detail::hash_combine(seed, hasher(v.w));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::tquat<T, Q>>::operator()(Core::tquat<T,Q> const& q) const
	{
		size_t seed = 0;
		hash<T> hasher;
		Core::detail::hash_combine(seed, hasher(q.x));
		Core::detail::hash_combine(seed, hasher(q.y));
		Core::detail::hash_combine(seed, hasher(q.z));
		Core::detail::hash_combine(seed, hasher(q.w));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::tdualquat<T, Q>>::operator()(Core::tdualquat<T, Q> const& q) const
	{
		size_t seed = 0;
		hash<Core::tquat<T, Q>> hasher;
		Core::detail::hash_combine(seed, hasher(q.real));
		Core::detail::hash_combine(seed, hasher(q.dual));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::mat<2, 2, T, Q>>::operator()(Core::mat<2, 2, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<Core::vec<2, T, Q>> hasher;
		Core::detail::hash_combine(seed, hasher(m[0]));
		Core::detail::hash_combine(seed, hasher(m[1]));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::mat<2, 3, T, Q>>::operator()(Core::mat<2, 3, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<Core::vec<3, T, Q>> hasher;
		Core::detail::hash_combine(seed, hasher(m[0]));
		Core::detail::hash_combine(seed, hasher(m[1]));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::mat<2, 4, T, Q>>::operator()(Core::mat<2, 4, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<Core::vec<4, T, Q>> hasher;
		Core::detail::hash_combine(seed, hasher(m[0]));
		Core::detail::hash_combine(seed, hasher(m[1]));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::mat<3, 2, T, Q>>::operator()(Core::mat<3, 2, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<Core::vec<2, T, Q>> hasher;
		Core::detail::hash_combine(seed, hasher(m[0]));
		Core::detail::hash_combine(seed, hasher(m[1]));
		Core::detail::hash_combine(seed, hasher(m[2]));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::mat<3, 3, T, Q>>::operator()(Core::mat<3, 3, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<Core::vec<3, T, Q>> hasher;
		Core::detail::hash_combine(seed, hasher(m[0]));
		Core::detail::hash_combine(seed, hasher(m[1]));
		Core::detail::hash_combine(seed, hasher(m[2]));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::mat<3, 4, T, Q>>::operator()(Core::mat<3, 4, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<Core::vec<4, T, Q>> hasher;
		Core::detail::hash_combine(seed, hasher(m[0]));
		Core::detail::hash_combine(seed, hasher(m[1]));
		Core::detail::hash_combine(seed, hasher(m[2]));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::mat<4, 2, T,Q>>::operator()(Core::mat<4, 2, T,Q> const& m) const
	{
		size_t seed = 0;
		hash<Core::vec<2, T, Q>> hasher;
		Core::detail::hash_combine(seed, hasher(m[0]));
		Core::detail::hash_combine(seed, hasher(m[1]));
		Core::detail::hash_combine(seed, hasher(m[2]));
		Core::detail::hash_combine(seed, hasher(m[3]));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::mat<4, 3, T,Q>>::operator()(Core::mat<4, 3, T,Q> const& m) const
	{
		size_t seed = 0;
		hash<Core::vec<3, T, Q>> hasher;
		Core::detail::hash_combine(seed, hasher(m[0]));
		Core::detail::hash_combine(seed, hasher(m[1]));
		Core::detail::hash_combine(seed, hasher(m[2]));
		Core::detail::hash_combine(seed, hasher(m[3]));
		return seed;
	}

	template<typename T, Core::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<Core::mat<4, 4, T,Q>>::operator()(Core::mat<4, 4, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<Core::vec<4, T, Q>> hasher;
		Core::detail::hash_combine(seed, hasher(m[0]));
		Core::detail::hash_combine(seed, hasher(m[1]));
		Core::detail::hash_combine(seed, hasher(m[2]));
		Core::detail::hash_combine(seed, hasher(m[3]));
		return seed;
	}
}
