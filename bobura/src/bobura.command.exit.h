/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_EXIT_H)
#define BOBURA_COMMAND_EXIT_H //!< !! Include Guard !!

//#include <boost/concept_check.hpp>
#include <boost/swap.hpp>

#include <concept_tetengo2.gui.Window.h>
#include <tetengo2.assignable.h>
#include <tetengo2.swappable.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for an exit command.

        \tparam Window A window type. It must conform to
                       concept_tetengo2::gui::Window<Window>.
    */
    template <typename Window>
    class exit :
        public tetengo2::assignable<exit<Window> >,
        private tetengo2::swappable<exit<Window> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));


    public:
        // types

        //! The window type.
        typedef Window window_type;


        // constructors and destructor

        /*!
            \brief Creates an exit command.

            \param window A window.
        */
        explicit exit(window_type& window)
        :
        m_p_window(&window)
        {}

        /*!
            \brief Copies an exit command.

            \param another Another exit command.
        */
        exit(const exit& another)
        :
        m_p_window(another.m_p_window)
        {}

        /*!
            \brief Destroys the exit command.
        */
        ~exit()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another exit command.

            \param another Another exit command.
        */
        void swap(exit& another)
        throw ()
        {
            boost::swap(m_p_window, another.m_p_window);
        }

        /*!
            \brief Assigns another exit command.

            \param another Another exit command.

            \return this object.
        */
        exit& operator=(const exit& another)
        {
            return assign(another);
        }

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            m_p_window->close();
        }


    private:
        // variables

        window_type* m_p_window;


    };


}}


#endif
