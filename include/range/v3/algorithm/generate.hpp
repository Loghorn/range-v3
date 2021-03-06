/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//
#ifndef RANGES_V3_ALGORITHM_GENERATE_HPP
#define RANGES_V3_ALGORITHM_GENERATE_HPP

#include <utility>
#include <range/v3/range_fwd.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/range_concepts.hpp>
#include <range/v3/range_traits.hpp>
#include <range/v3/utility/iterator_concepts.hpp>
#include <range/v3/utility/static_const.hpp>

namespace ranges
{
    inline namespace v3
    {
        /// \addtogroup group-algorithms
        /// @{
        struct generate_fn
        {
            template<typename O, typename S, typename F,
                CONCEPT_REQUIRES_(Function<F>() &&
                    OutputIterator<O, concepts::Function::result_t<F>>() &&
                    IteratorRange<O, S>())>
            std::pair<O, F> operator()(O begin, S end, F fun) const
            {
                for(; begin != end; ++begin)
                    *begin = fun();
                return {begin, fun};
            }

            template<typename Rng, typename F,
                typename O = range_iterator_t<Rng>,
                CONCEPT_REQUIRES_(Function<F>() &&
                    OutputRange<Rng, concepts::Function::result_t<F>>())>
            std::pair<range_safe_iterator_t<Rng>, F> operator()(Rng &&rng, F fun) const
            {
                return (*this)(begin(rng), end(rng), std::move(fun));
            }
        };

        /// \sa `generate_fn`
        /// \ingroup group-algorithms
        namespace
        {
            constexpr auto&& generate = static_const<with_braced_init_args<generate_fn>>::value;
        }

        /// @}
    } // namespace v3
} // namespace ranges

#endif // include guard
