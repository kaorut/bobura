/*! \file
    \brief The definition of bobura::message::oudia_diagram_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_OUDIADIAGRAMDIALOG_H)
#define BOBURA_MESSAGE_OUDIADIAGRAMDIALOG_H


namespace bobura { namespace message { namespace oudia_diagram_dialog
{
     /*!
        \brief The class template for a mouse click observer of the OK button.

        \tparam Dialog A dialog type.
    */
    template <typename Dialog>
    class ok_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the OK button.

            \param dialog A dialog.
        */
        explicit ok_button_mouse_clicked(dialog_type& dialog)
        :
        m_dialog(dialog)
        {}


        // functions

        /*!
            \brief Called when the OK button is clicked.
        */
        void operator()()
        const
        {
            m_dialog.set_result(dialog_type::result_type::accepted);
            m_dialog.close();
        }


    private:
        // variables

        dialog_type& m_dialog;


    };

     /*!
        \brief The class template for a mouse click observer of the cancel button.

        \tparam Dialog A dialog type.
    */
    template <typename Dialog>
    class cancel_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the cancel button.

            \param dialog A dialog.
        */
        explicit cancel_button_mouse_clicked(dialog_type& dialog)
        :
        m_dialog(dialog)
        {}


        // functions

        /*!
            \brief Called when the cancel button is clicked.
        */
        void operator()()
        const
        {
            m_dialog.set_result(dialog_type::result_type::canceled);
            m_dialog.close();
        }


    private:
        // variables

        dialog_type& m_dialog;


    };


}}}


#endif