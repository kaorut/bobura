/*! \file
    \brief The definition of bobura::command::show_diagram.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SHOWDIAGRAM_H)
#define BOBURA_COMMAND_SHOWDIAGRAM_H

#include <memory>

#include <bobura/command/command_base.h>


namespace bobura::command {
    /*!
        \brief The class template for a show-diagram command.

        \tparam Traits A traits type.
    */
    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits>
    class show_diagram : public command_base<Traits>
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
            \brief Create a show-diagram command.
        */
        show_diagram();

        /*!
            \brief Destroys the show-diagram command.
        */
        virtual ~show_diagram() noexcept;


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
