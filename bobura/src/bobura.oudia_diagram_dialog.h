/*! \file
    \brief The definition of bobura::oudia_diagram_dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_OUDIADIAGRAMDIALOG_H)
#define BOBURA_OUDIADIAGRAMDIALOG_H

#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/optional.hpp>

#include <tetengo2.stdalt.h>


namespace bobura
{
    /*!
        \brief The class template for the OuDia diagram dialog.

        \tparam Dialog         A dialog type.
        \tparam MessageCatalog A message catalog type.
        \tparam IntSize        An integer size type.
    */
    template <typename Dialog, typename MessageCatalog, typename IntSize>
    class oudia_diagram_dialog : public Dialog
    {
    public:
        // types

        //! The base type.
        using base_type = Dialog;

        //! The abstract window type.
        using abstract_window_type = typename base_type::base_type;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The integer size type.
        using int_size_type = IntSize;


        // constructors and destructor

        /*!
            \brief Creates a OuDia diagram dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        oudia_diagram_dialog(abstract_window_type& parent, const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the OuDia diagram dialog.
        */
        virtual ~oudia_diagram_dialog()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Returns the file name.

            \return The file name.
        */
        const string_type& file_name()
        const;

        /*!
            \brief Sets a file name.

            \param file_name A file name.
        */
        void set_file_name(string_type file_name);

        /*!
            \brief Returns the names.

            \return The names.
        */
        const std::vector<string_type>& names()
        const;

        /*!
            \brief Sets names.

            \param names Names.
        */
        void set_names(std::vector<string_type> names);

        /*!
            \brief Returns the selected index.

            \return The selected index.
        */
        const boost::optional<int_size_type>& selected_index()
        const;

        /*!
            \brief Sets a selected index.

            \param index An index.

            \throw std::out_of_range When index is greater than the diagram count.
        */
        void set_selected_index(const int_size_type index);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void set_result_impl()
        override;


    };


}

#endif
