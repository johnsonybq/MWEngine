/// @ref gtx_wrap

namespace Core
{
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> clamp(vec<L, T, Q> const& Texcoord)
	{
		return Core::clamp(Texcoord, vec<L, T, Q>(0), vec<L, T, Q>(1));
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER genType clamp(genType const& Texcoord)
	{
		return clamp(vec<1, genType, defaultp>(Texcoord)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> repeat(vec<L, T, Q> const& Texcoord)
	{
		return Core::fract(Texcoord);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER genType repeat(genType const& Texcoord)
	{
		return repeat(vec<1, genType, defaultp>(Texcoord)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> mirrorClamp(vec<L, T, Q> const& Texcoord)
	{
		return Core::fract(Core::abs(Texcoord));
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER genType mirrorClamp(genType const& Texcoord)
	{
		return mirrorClamp(vec<1, genType, defaultp>(Texcoord)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> mirrorRepeat(vec<L, T, Q> const& Texcoord)
	{
		vec<L, T, Q> const Abs = Core::abs(Texcoord);
		vec<L, T, Q> const Clamp = Core::mod(Core::floor(Abs), vec<L, T, Q>(2));
		vec<L, T, Q> const Floor = Core::floor(Abs);
		vec<L, T, Q> const Rest = Abs - Floor;
		vec<L, T, Q> const Mirror = Clamp + Rest;
		return mix(Rest, vec<L, T, Q>(1) - Rest, Core::greaterThanEqual(Mirror, vec<L, T, Q>(1)));
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER genType mirrorRepeat(genType const& Texcoord)
	{
		return mirrorRepeat(vec<1, genType, defaultp>(Texcoord)).x;
	}
}//namespace Core
