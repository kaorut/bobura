/*! \file
    \brief The definition of bobura::model::serializer::select_oudia_diagram.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_SELECTOUDIADIAGRAM_H)
#define BOBURA_MODEL_SERIALIZER_SELECTOUDIADIAGRAM_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>


namespace bobura::model::serializer {
    /*!
        \brief The class template for an OuDia diagram selecting.

        \tparam OuDiaDiagramDialog An OuDia diagram dialog type.
    */
    template <typename OuDiaDiagramDialog>
    class select_oudia_diagram : private boost::noncopyable
    {
    public:
        // types

        //! The OuDia diagram dialog type.
        using oudia_diagram_dialog_type = OuDiaDiagramDialog;

        //! The abstract window type.
        using abstract_window_type = typename oudia_diagram_dialog_type::abstract_window_type;

        //! The string type.
        using string_type = typename oudia_diagram_dialog_type::string_type;

        //! The iterator type.
        using iterator = typename std::vector<string_type>::const_iterator;

        //! The message catalog type.
        using message_catalog_type = typename oudia_diagram_dialog_type::message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates an OuDia diagram selecting.

            \param parent          A parent window.
            \param file_name       A file name.
            \param message_catalog A message catalog.
        */
        select_oudia_diagram(
            abstract_window_type&       parent,
            string_type                 file_name,
            const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the OuDia diagram selecting.
        */
        ~select_oudia_diagram() noexcept;


        // functions

        /*!
            \brief Selects an OuDia diagram.

            \param first The first position of the diagrams.
            \param last  The last position of the diagrams.

            \return The selected position.
        */
        iterator operator()(iterator first, iterator last) const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };


    /*!
        \brief The class template for an OuDia diagram selecting for testing.

        \tparam String A string type.
    */
    template <typename String>
    class select_oudia_diagram_for_test : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The iterator type.
        using iterator = typename std::vector<string_type>::const_iterator;


        // constructors and destructor

        /*!
            \brief Creates an OuDia diagram selecting for testing.

            \param name A diagram name.
        */
        explicit select_oudia_diagram_for_test(string_type name);

        /*!
            \brief Destroys the OuDia diagram selecting for testing.
        */
        ~select_oudia_diagram_for_test() noexcept;


        // functions

        /*!
            \brief Selects an OuDia diagram.

            \param first The first position of the diagrams.
            \param last  The last position of the diagrams.

            \return Always first.
        */
        iterator operator()(iterator first, iterator last) const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
