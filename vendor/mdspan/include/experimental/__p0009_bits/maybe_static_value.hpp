/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#include "macros.hpp"
// This is only needed for the non-standard-layout version of partially
// static array.
#if !_MDSPAN_PRESERVE_STANDARD_LAYOUT

#include "dynamic_extent.hpp"
#include "no_unique_address.hpp"

namespace std {
namespace experimental {

//==============================================================================

namespace detail {

// static case
template <class _T, _T __v,
          _T __is_dynamic_sentinal = dynamic_extent,
          size_t __array_entry_index = 0>
struct __maybe_static_value {
  static constexpr _T __static_value = __v;
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __value() const noexcept {
    return __v;
  }
  template <class _U>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __mdspan_enable_fold_comma
  __set_value(_U&& __rhs) noexcept {
    // Should we assert that the value matches the static value here?
    return {};
  }

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __maybe_static_value() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __maybe_static_value(__maybe_static_value const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __maybe_static_value(__maybe_static_value&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __maybe_static_value& operator=(__maybe_static_value const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __maybe_static_value& operator=(__maybe_static_value&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__maybe_static_value() noexcept = default;

  MDSPAN_INLINE_FUNCTION
  constexpr explicit __maybe_static_value(_T const&) noexcept {
    // Should we assert that the value matches the static value here?
  }

  //--------------------------------------------------------------------------

};

// dynamic case
template <class _T, _T __is_dynamic_sentinal, size_t __array_entry_index>
struct __maybe_static_value<_T, __is_dynamic_sentinal, __is_dynamic_sentinal,
                            __array_entry_index>
    : __no_unique_address_emulation<_T> {
  static constexpr _T __static_value = __is_dynamic_sentinal;
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __value() const noexcept {
    return this->__no_unique_address_emulation<_T>::__ref();
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _T &__ref() noexcept {
    return this->__no_unique_address_emulation<_T>::__ref();
  }
  template <class _U>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __mdspan_enable_fold_comma
  __set_value(_U&& __rhs) noexcept {
    this->__no_unique_address_emulation<_T>::__ref() = __rhs;
    return {};
  }
  _MDSPAN_NO_UNIQUE_ADDRESS _T __v = {};
};

} // namespace detail

//==============================================================================

} // end namespace experimental
} // end namespace std

#endif // !_MDSPAN_PRESERVE_STANDARD_LAYOUT