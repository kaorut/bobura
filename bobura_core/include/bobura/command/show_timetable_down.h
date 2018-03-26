/*! \file
    \brief The definition of bobura::command::show_timetable_down.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SHOWTIMETABLEDOWN_H)
#define BOBURA_COMMAND_SHOWTIMETABLEDOWN_H

#include <memory>

#include <bobura/command/command_base.h>


namespace bobura::command {
    /*!
        \brief The class template for a show-timetable-down command.

        \tparam Traits A traits type.
    */
    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits>
    class show_timetable_down : public command_base<Traits>
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
            \brief Create a show-timetable-down command.
        */
        show_timetable_down();

        /*!
            \brief Destroys the show-timetable-down command.
        */
        virtual ~show_timetable_down() noexcept;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent) const override;
    };
}


#endif
