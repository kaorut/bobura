/*! \file
    \brief The definition of bobura::view::diagram::item.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/type_list.h>
#include <bobura/view/scale_list.h>


namespace bobura::view {
    template <typename Size, typename String, typename Scale>
    class scale_list<Size, String, Scale>::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = Size;

        using string_type = String;

        using scale_type = Scale;


        // functions

        size_type size() const
        {
            assert(scales().size() == labels().size());
            return scales().size();
        }

        const scale_type& at(const size_type index) const
        {
            if (index >= scales().size())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            return scales()[index];
        }

        const string_type& label_at(const size_type index) const
        {
            if (index >= labels().size())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            return labels()[index];
        }

        tetengo2::stdalt::optional<size_type> index_of(const scale_type& scale) const
        {
            for (size_type i = 0; i < scales().size(); ++i)
            {
                if (scales()[i] == scale)
                    return tetengo2::stdalt::make_optional(std::move(i));
            }
            return TETENGO2_STDALT_NULLOPT;
        }

        const scale_type& larger(const scale_type& scale) const
        {
            const auto found = std::find_if(
                scales().begin(), scales().end(), [&scale](const scale_type& candidate) { return candidate > scale; });
            return found != scales().end() ? *found : scales().back();
        }

        const scale_type& smaller(const scale_type& scale) const
        {
            const auto found = std::find_if(scales().rbegin(), scales().rend(), [&scale](const scale_type& candidate) {
                return candidate < scale;
            });
            return found != scales().rend() ? *found : scales().front();
        }


    private:
        // static functions

        static const std::vector<scale_type>& scales()
        {
            static const std::vector<scale_type> singleton{ make_scales() };
            return singleton;
        }

        static const std::vector<string_type>& labels()
        {
            static const std::vector<string_type> singleton{ make_labels() };
            return singleton;
        }

        static std::vector<scale_type> make_scales()
        {
            std::vector<scale_type> scales{
                { 1, 10 }, { 1, 4 }, { 1, 2 }, { 3, 4 }, { 1 }, { 3, 2 }, { 2 }, { 4 },
            };

            assert(std::is_sorted(scales.begin(), scales.end(), std::less<scale_type>{}));
            return scales;
        }

        static std::vector<string_type> make_labels()
        {
            std::vector<string_type> labels{
                { string_type{ TETENGO2_TEXT("10%") } },  { string_type{ TETENGO2_TEXT("25%") } },
                { string_type{ TETENGO2_TEXT("50%") } },  { string_type{ TETENGO2_TEXT("75%") } },
                { string_type{ TETENGO2_TEXT("100%") } }, { string_type{ TETENGO2_TEXT("150%") } },
                { string_type{ TETENGO2_TEXT("200%") } }, { string_type{ TETENGO2_TEXT("400%") } },
            };

            assert(labels.size() == scales().size());
            return labels;
        }
    };


    template <typename Size, typename String, typename Scale>
    scale_list<Size, String, Scale>::scale_list() : m_p_impl{ std::make_unique<impl>() }
    {}

    template <typename Size, typename String, typename Scale>
    scale_list<Size, String, Scale>::~scale_list()
    {}

    template <typename Size, typename String, typename Scale>
    typename scale_list<Size, String, Scale>::size_type scale_list<Size, String, Scale>::size() const
    {
        return m_p_impl->size();
    }

    template <typename Size, typename String, typename Scale>
    const typename scale_list<Size, String, Scale>::scale_type&
    scale_list<Size, String, Scale>::at(const size_type index) const
    {
        return m_p_impl->at(index);
    }

    template <typename Size, typename String, typename Scale>
    const typename scale_list<Size, String, Scale>::string_type&
    scale_list<Size, String, Scale>::label_at(const size_type index) const
    {
        return m_p_impl->label_at(index);
    }

    template <typename Size, typename String, typename Scale>
    tetengo2::stdalt::optional<typename scale_list<Size, String, Scale>::size_type>
    scale_list<Size, String, Scale>::index_of(const scale_type& scale) const
    {
        return m_p_impl->index_of(scale);
    }

    template <typename Size, typename String, typename Scale>
    const typename scale_list<Size, String, Scale>::scale_type&
    scale_list<Size, String, Scale>::larger(const scale_type& scale) const
    {
        return m_p_impl->larger(scale);
    }

    template <typename Size, typename String, typename Scale>
    const typename scale_list<Size, String, Scale>::scale_type&
    scale_list<Size, String, Scale>::smaller(const scale_type& scale) const
    {
        return m_p_impl->smaller(scale);
    }


    namespace {
        using common_type_list_type = type_list::common;
    }

    template class scale_list<
        typename common_type_list_type::size_type,
        typename common_type_list_type::string_type,
        typename common_type_list_type::scale_type>;
}
