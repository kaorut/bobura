/*! \file
    \brief The precompiled header for Visual C++.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(PRECOMPILED_H)
#define PRECOMPILED_H

// The standard library headers
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <functional>
#include <iomanip>
#include <ios>
#include <iterator>
#include <limits>
#include <locale>
#include <memory>
#include <numeric>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

// The Boost library headers
#include <boost/algorithm/string.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/format.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/program_options.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/rational.hpp>
#include <boost/signals2.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/swap.hpp>
#include <boost/system/system_error.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/variant.hpp>


#if BOOST_COMP_MSVC

// Windows headers

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <d2d1.h>
#include <dwrite.h>
#include <dxgiformat.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max
#include <ShObjIdl.h>
#include <ShTypes.h>
#include <Unknwn.h>
#include <wincodec.h>

#endif


// Tetengo2 headers

#include <tetengo2.h>
#include <tetengo2.gui.h>


#endif
