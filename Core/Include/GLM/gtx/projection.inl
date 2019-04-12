/// @ref gtx_projection

namespace Core
{
	template<typename genType>
	GLM_FUNC_QUALIFIER genType proj(genType const& x, genType const& Normal)
	{
		return Core::dot(x, Normal) / Core::dot(Normal, Normal) * Normal;
	}
}//namespace Core
