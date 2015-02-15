/*! \file
    \brief The definition of bobura::model::serializer::exec_json_reading_task.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_EXECJSONREADINGTASK_H)
#define BOBURA_MODEL_SERIALIZER_EXECJSONREADINGTASK_H

#include <tetengo2.h>
#include <tetengo2.gui.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON reading task execution.

        \tparam String         A string type.
        \tparam Dialog         A progress dialog type.
        \tparam Timer          A timer type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename String, typename Dialog, typename Timer, typename MessageCatalog>
    class exec_json_reading_task
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The dialog type.
        using dialog_type = Dialog;

        //! The abstract window type.
        using abstract_window_type = typename dialog_type::base_type;

        //! The timer type.
        using timer_type = Timer;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The progress dialog type.
        using progress_dialog_type =
            tetengo2::gui::widget::progress_dialog<
                typename dialog_type::traits_type,
                int,
                typename dialog_type::details_traits_type,
                typename dialog_type::menu_details_type,
                typename dialog_type::message_loop_details_type,
                typename timer_type::timer_details_type
            >;

        //! The promise type.
        using promise_type = typename progress_dialog_type::promise_type;


        // constructors and destructor

        /*!
            \brief Creates an OuDia diagram selecting.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        exec_json_reading_task(abstract_window_type& parent, const message_catalog_type& message_catalog)
        :
        m_parent(parent),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Execute a JSON reading task.
        */
        void operator()()
        const
        {
            auto task =
                [](promise_type& p)
                {
                    p.set_value(42);
                };
            progress_dialog_type dialog{ m_parent, task };
            dialog.do_modal();

        }


    private:
        // variables

        abstract_window_type& m_parent;

        const message_catalog_type& m_message_catalog;


    };


}}}


#endif
