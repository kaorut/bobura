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

#include <tetengo2.h>


namespace bobura
{
    /*!
        \brief The class template for the OuDia diagram dialog.

        \tparam Traits A traits type.
        \tparam Size   A size type.
    */
    template <typename Traits, typename Size>
    class oudia_diagram_dialog : public Traits::dialog_type
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The base type.
        using base_type = typename traits_type::dialog_type;

        //! The abstract window type.
        using abstract_window_type = typename traits_type::abstract_window_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The size type.
        using size_type = Size;


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
        const boost::optional<size_type>& selected_index()
        const;

        /*!
            \brief Sets a selected index.

            \param index An index.

            \throw std::out_of_range When index is greater than the diagram count.
        */
        void set_selected_index(const size_type index);


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
