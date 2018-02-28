/*! \file
    \brief The definition of bobura::message::diagram_selection_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#include <tetengo2/stdalt.h>

#include <bobura/message/diagram_selection_observer_set.h>
#include <bobura/type_list.h>


namespace bobura { namespace message {
    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    class diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::impl : private boost::noncopyable
    {
    public:
        // types

        using station_selected_type = typename diagram_selection_observer_set::station_selected_type;

        using station_selected_signal_type = typename diagram_selection_observer_set::station_selected_signal_type;

        using train_selected_type = typename diagram_selection_observer_set::train_selected_type;

        using train_selected_signal_type = typename diagram_selection_observer_set::train_selected_signal_type;

        using all_unselected_type = typename diagram_selection_observer_set::all_unselected_type;

        using all_unselected_signal_type = typename diagram_selection_observer_set::all_unselected_signal_type;


        // functions

        const station_selected_signal_type& station_selected() const
        {
            return m_station_selected;
        }

        station_selected_signal_type& station_selected()
        {
            return m_station_selected;
        }

        const train_selected_signal_type& train_selected() const
        {
            return m_train_selected;
        }

        train_selected_signal_type& train_selected()
        {
            return m_train_selected;
        }

        const all_unselected_signal_type& all_unselected() const
        {
            return m_all_unselected;
        }

        all_unselected_signal_type& all_unselected()
        {
            return m_all_unselected;
        }


    private:
        // variables

        station_selected_signal_type m_station_selected;

        train_selected_signal_type m_train_selected;

        all_unselected_signal_type m_all_unselected;
    };


    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::diagram_selection_observer_set()
    : m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::
        ~diagram_selection_observer_set() noexcept
    {}

    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    const typename diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::
        station_selected_signal_type&
        diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::station_selected() const
    {
        return m_p_impl->station_selected();
    }

    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    typename diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::station_selected_signal_type&
    diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::station_selected()
    {
        return m_p_impl->station_selected();
    }

    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    const typename diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::
        train_selected_signal_type&
        diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::train_selected() const
    {
        return m_p_impl->train_selected();
    }

    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    typename diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::train_selected_signal_type&
    diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::train_selected()
    {
        return m_p_impl->train_selected();
    }

    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    const typename diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::
        all_unselected_signal_type&
        diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::all_unselected() const
    {
        return m_p_impl->all_unselected();
    }

    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    typename diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::all_unselected_signal_type&
    diagram_selection_observer_set<Size, Difference, String, OperatingDistance>::all_unselected()
    {
        return m_p_impl->all_unselected();
    }


    namespace {
        using common_type_list_type = type_list::common;
    }

    template class diagram_selection_observer_set<
        typename common_type_list_type::size_type,
        typename common_type_list_type::difference_type,
        typename common_type_list_type::string_type,
        typename common_type_list_type::operating_distance_type>;


}}
