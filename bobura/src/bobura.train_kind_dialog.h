/*! \file
    \brief The definition of bobura::train_kind_dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_TRAINKINDDIALOG_H)
#define BOBURA_TRAINKINDDIALOG_H

#include <memory>
#include <vector>

#include <boost/optional.hpp>

#include <tetengo2.h>


namespace bobura
{
    /*!
        \brief The class template for the train kind dialog.

        \tparam Dialog         A dialog type.
        \tparam MessageCatalog A message catalog type.
        \tparam IntSize        An integer size type.
        \tparam TrainKind      A train kind type.
        \tparam Font           A font type.
        \tparam Color          A color type.
    */
    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename TrainKind,
        typename Font,
        typename Color
    >
    class train_kind_dialog : public Dialog
    {
    public:
        // types

        //! The base type.
        using base_type = Dialog;

        //! The abstract window type.
        using abstract_window_type = typename base_type::base_type;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The integer size type.
        using int_size_type = IntSize;

        //! The train kind type.
        using train_kind_type = TrainKind;

        //! The font type.
        using font_type = Font;

        //! The color type.
        using color_type = Color;

        //! The information set type.
        class info_set_type
        {
        public:
            //! The train kind type.
            using train_kind_type = TrainKind;

            /*!
                \brief Creates an information set.

                \param original_index An original index.
                \param referred       A referred status.
                \param train_kind     A train kind.
            */
            info_set_type(
                boost::optional<int_size_type> original_index,
                const bool                     referred,
                train_kind_type                train_kind
            );


            /*!
                \brief Returns the original index.

                \return The original index.
            */
            const boost::optional<int_size_type>& original_index()
            const;

            /*!
                \brief Returns the referred status.

                \return The referred status.
            */
            bool referred()
            const;

            /*!
                \brief Returns the train kind.

                \return The train kind.
            */
            const train_kind_type& train_kind()
            const;

            /*!
                \brief Returns the train kind.

                \return The train kind.
            */
            train_kind_type& train_kind();

        private:
            boost::optional<int_size_type> m_original_index;

            bool m_referred;

            train_kind_type m_train_kind;

        };


        // constructors and destructor

        /*!
            \brief Creates a train kind dialog.

            \param parent           A parent window.
            \param message_catalog  A message catalog.
            \param font             A font for the sample.
            \param background_color A background color for the sample.
        */
        train_kind_dialog(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog,
            const font_type&            font,
            const color_type&           background_color
        );

        /*!
            \brief Destroys the train kind dialog.
        */
        virtual ~train_kind_dialog()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Returns the information sets.

            \return The information sets.
        */
        const std::vector<info_set_type> info_sets()
        const;

        /*!
            \brief Sets information sets.

            \param info_sets Information sets.
        */
        void set_info_sets(std::vector<info_set_type> info_sets);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void do_modal_impl()
        override;


    };


}

#endif
