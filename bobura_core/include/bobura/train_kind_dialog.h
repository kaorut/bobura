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

        \tparam Size           A size type.
        \tparam Dialog         A dialog type.
        \tparam TrainKind      A train kind type.
        \tparam Font           A font type.
        \tparam Color          A color type.
        \tparam MessageCatalog A message catalog type.
    */
    template <
        typename Size,
        typename Dialog,
        typename TrainKind,
        typename Font,
        typename Color,
        typename MessageCatalog
    >
    class train_kind_dialog : public Dialog
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The base type.
        using base_type = Dialog;

        //! The abstract window type.
        using abstract_window_type = typename base_type::base_type;

        //! The train kind type.
        using train_kind_type = TrainKind;

        //! The font type.
        using font_type = Font;

        //! The color type.
        using color_type = Color;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

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
            info_set_type(boost::optional<size_type> original_index, const bool referred, train_kind_type train_kind);


            /*!
                \brief Returns the original index.

                \return The original index.
            */
            const boost::optional<size_type>& original_index()
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
            boost::optional<size_type> m_original_index;

            bool m_referred;

            train_kind_type m_train_kind;

        };


        // constructors and destructor

        /*!
            \brief Creates a train kind dialog.

            \param parent           A parent window.
            \param font             A font for the sample.
            \param background_color A background color for the sample.
            \param message_catalog  A message catalog.
        */
        train_kind_dialog(
            abstract_window_type&       parent,
            const font_type&            font,
            const color_type&           background_color,
            const message_catalog_type& message_catalog
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
