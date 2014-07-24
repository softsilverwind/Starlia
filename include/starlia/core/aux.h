#include <algorithm>
#include <numeric>
#include <fstream>

namespace Starlia
{

using namespace std;

// Auxiliary functions for prettier manipulation of the standard library, without
// being too obscure.
template <typename InputIterator, typename Distance>
inline InputIterator operator+(InputIterator it, Distance n)
{
	advance(it, n);
	return it;
}

template <typename InputIterator, typename Distance>
inline InputIterator operator-(InputIterator it, Distance n)
{
	advance(it, -n);
	return it;
}

template <typename IContainerType, typename OContainerType, typename UnaryOperator>
void transform(const IContainerType& container, OContainerType& result, const UnaryOperator& op)
{
	std::transform(container.begin(), container.end(), result.begin(), op);
}

template <typename IContainerType1, typename IContainerType2, typename OContainerType, typename BinaryOperator>
void transform(const IContainerType1& container1, const IContainerType2& container2, OContainerType& result, const BinaryOperator& binop)
{
	std::transform(container1.begin(), container1.end(), container2.begin(), result.begin(), binop);
}

template <typename IContainerType, typename T, typename BinaryOperator>
T accumulate(const IContainerType& container, const T& init, const BinaryOperator& binop )
{
	return std::accumulate(container.begin(), container.end(), init, binop);
}

template <typename IContainerType>
void sort(IContainerType& container)
{
	std::sort(container.begin(), container.end());
}

template <typename IContainerType, typename Compare>
void sort(IContainerType& container, const Compare& comp)
{
	std::sort(container.begin, container.end(), comp);
}

template <typename IContainerType, typename Predicate>
auto partition(IContainerType& container, const Predicate& pred) -> decltype(container.end())
{
	return std::partition(container.begin(), container.end(), pred);
}

}

