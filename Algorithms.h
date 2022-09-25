#pragma once

// add exceptions  
// add constrints


template<typename Iterator>
concept IteratorConcept = requires(Iterator i, Iterator j)
{
	{ i++ } -> std::same_as<Iterator>;
	{ i-- } -> std::same_as<Iterator>;
	{ ++i } -> std::same_as<Iterator&>;
	{ --i } -> std::same_as<Iterator&>;
	{ i == j } -> std::convertible_to<bool>;
	{ i != j } -> std::convertible_to<bool>;
	{ *i } -> std::same_as<std::iter_reference_t<Iterator>>;
};



template<typename InputIt, typename UnaryPredicate>
requires IteratorConcept<InputIt>
int count_if(InputIt begin, InputIt end, UnaryPredicate pred)
{
	int count = 0;
	
	while (begin != end)
	{
		if (pred(*begin))
		{
			count++;
		}
		++begin;
	}
	return count;
}

template<typename InputIt, typename UnaryFunction>
requires IteratorConcept<InputIt>
void for_each(InputIt begin, InputIt end, UnaryFunction fun)
{
	while (begin != end)
	{
		fun(*begin);
		++begin;
	}
}

template<typename InputIt, typename UnaryPredicate>
requires IteratorConcept<InputIt>
InputIt find_if(InputIt begin, InputIt end, UnaryPredicate pred)
{
	while (begin != end)
	{
		if (pred(*begin))
			return begin;
		++begin;
	}
	// FIXME: exception
}

template<typename InputIt, typename UnaryFunction>
requires IteratorConcept<InputIt>
InputIt min_element(InputIt begin, InputIt end, UnaryFunction func)
{
	auto result = begin;
	while (begin != end)
	{
		if (func(*result) > func(*begin))
			result = begin;

		++begin;
	}
	return result;
}

template<typename InputIt, typename UnaryFunction>
requires IteratorConcept<InputIt>
InputIt max_element(InputIt begin, InputIt end, UnaryFunction func)
{
	auto result = begin;
	while (begin != end)
	{
		if (func(*result) < func(*begin))
			result = begin;

		++begin;
	}
	return result;
}

template<typename InputIt, typename UnaryFunction>
requires IteratorConcept<InputIt>
void Sort(InputIt begin, InputIt end, UnaryFunction func)
{
		std::iter_swap(begin, min_element(begin, end, func));
}

template<typename InputIt, typename OutputIt, typename UnaryPredicate>
requires IteratorConcept<InputIt>
int copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate pred)
{
	int copied = 0; 
	
	while (first != last)
	{
		if (pred(*first))
		{
			*d_first = first;
			++d_first;
			++copied; 
		}
		++first;
	}
	return copied;
}