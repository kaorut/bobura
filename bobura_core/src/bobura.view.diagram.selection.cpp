/*! \file
    \brief The definition of bobura::view::diagram::selection.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <cassert>
#include <limits>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/type_list.h>
#include <bobura/view/diagram/selection.h>


namespace bobura { namespace view { namespace diagram
{
    template <typename Traits>
    class selection<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using size_type = typename traits_type::size_type;

        using station_location_type = typename selection::station_location_type;

        using train_type = typename selection::train_type;

        using selection_observer_set_type = typename selection::selection_observer_set_type;


        // constructors and destructor

        impl()
        :
        m_p_selected_station_location(nullptr),
        m_p_selected_train(nullptr),
        m_p_selection_observer_set(tetengo2::stdalt::make_unique<selection_observer_set_type>())
        {}

        impl(impl&& another)
        :
        m_p_selected_station_location(another.m_p_selected_station_location),
        m_p_selected_train(another.m_p_selected_train),
        m_p_selection_observer_set(std::move(another.m_p_selection_observer_set))
        {}


        // functions

        bool selected(const station_location_type& station_location)
        const
        {
            if (!m_p_selected_station_location)
                return false;

            return &station_location == m_p_selected_station_location;
        }

        bool selected(const train_type& train, const boost::optional<size_type>& departure_stop_index)
        const
        {
            if (!m_p_selected_train)
                return false;
            if (!departure_stop_index != !m_departure_stop_index)
                return false;
            if (!departure_stop_index)
            {
                assert(!m_departure_stop_index);
                return &train == m_p_selected_train;
            }
            return
                &train == m_p_selected_train &&
                (
                    *departure_stop_index == std::numeric_limits<size_type>::max() ||
                    *departure_stop_index == *m_departure_stop_index
                );
        }

        void select(const station_location_type& station_location)
        {
            unselect_all();

            m_p_selected_station_location = &station_location;

            m_p_selection_observer_set->station_selected()(station_location);
        }

        void select(
            const train_type&                 train,
            const boost::optional<size_type>& departure_stop_index
        )
        {
            unselect_all();

            m_p_selected_train = &train;
            m_departure_stop_index = departure_stop_index;

            m_p_selection_observer_set->train_selected()(train, departure_stop_index);
        }

        void unselect_all()
        {
            m_p_selected_station_location = nullptr;
            m_p_selected_train = nullptr;
            m_departure_stop_index = boost::none;

            m_p_selection_observer_set->all_unselected()();
        }

        const selection_observer_set_type& selection_observer_set()
        const
        {
            return *m_p_selection_observer_set;
        }

        selection_observer_set_type& selection_observer_set()
        {
            return *m_p_selection_observer_set;
        }


    private:
        // variables

        const station_location_type* m_p_selected_station_location;

        const train_type* m_p_selected_train;

        boost::optional<size_type> m_departure_stop_index;

        std::unique_ptr<selection_observer_set_type> m_p_selection_observer_set;


    };


    template <typename Traits>
    selection<Traits>::selection()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <typename Traits>
    selection<Traits>::selection(selection&& another)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    selection<Traits>::~selection()
    noexcept
    {}

    template <typename Traits>
    bool selection<Traits>::selected(const station_location_type& station_location)
    const
    {
        return m_p_impl->selected(station_location);
    }

    template <typename Traits>
    bool selection<Traits>::selected(const train_type& train, const boost::optional<size_type>& departure_stop_index)
    const
    {
        return m_p_impl->selected(train, departure_stop_index);
    }

    template <typename Traits>
    void selection<Traits>::select(const station_location_type& station_location)
    {
        m_p_impl->select(station_location);
    }

    template <typename Traits>
    void selection<Traits>::select(const train_type& train, const boost::optional<size_type>& departure_stop_index)
    {
        m_p_impl->select(train, departure_stop_index);
    }

    template <typename Traits>
    void selection<Traits>::unselect_all()
    {
        m_p_impl->unselect_all();
    }

    template <typename Traits>
    const typename selection<Traits>::selection_observer_set_type& selection<Traits>::selection_observer_set()
    const
    {
        return m_p_impl->selection_observer_set();
    }

    template <typename Traits>
    typename selection<Traits>::selection_observer_set_type& selection<Traits>::selection_observer_set()
    {
        return m_p_impl->selection_observer_set();
    }

        
    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class selection<typename application::traits_type_list_type::diagram_view_type>;
#endif

    template class selection<typename test::traits_type_list_type::diagram_view_type>;


}}}
