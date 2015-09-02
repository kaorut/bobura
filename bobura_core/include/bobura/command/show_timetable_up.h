/*! \file
    \brief The definition of bobura::command::show_timetable_up.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SHOWTIMETABLEUP_H)
#define BOBURA_COMMAND_SHOWTIMETABLEUP_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a show-timetable-up command.

        \tparam Traits A traits type.
    */
    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits>
    class show_timetable_up : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The command set traits type.
        using command_set_traits_type = CommandSetTraits;

        //! The main window traits type.
        using main_window_traits_type = MainWindowTraits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The abstract window type.
        using abstract_window_type = typename base_type::abstract_window_type;

        //! The model type.
        using model_type = typename base_type::model_type;


        // constructors and destructor

        /*!
            \brief Create a show-timetable-up command.
        */
        show_timetable_up();

        /*!
            \brief Destroys the show-timetable-up command.
        */
        virtual ~show_timetable_up()
        noexcept;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const override;


    };


}}


#endif
