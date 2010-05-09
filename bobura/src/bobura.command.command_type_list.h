/*! \file
    \brief The definition of bobura::command::command_type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_COMMANDTYPELIST_H)
#define BOBURA_COMMAND_COMMANDTYPELIST_H //!< !! Include Guard !!

//#include <boost/concept_check.hpp>
#include <boost/function.hpp>

#include "bobura.command.about.h"
#include "bobura.command.exit.h"
#include "bobura.command.nop.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a command type list.

        \tparam Window      A window type. It must conform to
                            concept_tetengo2::gui::Window<Window>.
        \tparam AboutDialog An about dialog type. It must conform to
                            concept_bobura::AboutDialog<AboutDialog>.
    */
    template <typename Window, typename AboutDialog>
    class command_type_list
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));
        BOOST_CONCEPT_ASSERT((concept_bobura::AboutDialog<AboutDialog>));


    public:
        // types

        //! The command type;
        typedef boost::function<void ()> command_type;

        //! The about command type.
        typedef about<AboutDialog> about_type;

        //! The exit command type.
        typedef exit<Window> exit_type;

        //! The nop command type.
        typedef nop nop_type;


    private:
        // forbidden operations

        command_type_list();


    };


}}

#endif
