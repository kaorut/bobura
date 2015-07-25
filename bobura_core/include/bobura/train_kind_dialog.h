/*! \file
    \brief The definition of bobura::train_kind_dialog.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_TRAINKINDDIALOG_H)
#define BOBURA_TRAINKINDDIALOG_H

#include <memory>
#include <vector>

#include <boost/optional.hpp>

#include <tetengo2.h>

#include <bobura/model/train_kind.h>


namespace bobura
{
    /*!
        \brief The class template for the train kind dialog.

        \tparam Traits      A traits type.
        \tparam Size        A size type.
        \tparam String      A string type.
        \tparam Font        A font type.
        \tparam Color       A color type.
        \tparam Canvas      A canvas type.
        \tparam ColorDialog A color dialog type.
    */
    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename Color,
        typename Canvas,
        typename ColorDialog
    >
    class train_kind_dialog : public Traits::dialog_type
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The base type.
        using base_type = typename traits_type::dialog_type;

        //! The abstract window type.
        using abstract_window_type = typename traits_type::abstract_window_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The size type.
        using size_type = Size;

        //! THe string type.
        using string_type = String;

        //! The font type.
        using font_type = Font;

        //! The color type.
        using color_type = Color;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The color dialog type.
        using color_dialog_type = ColorDialog;

        //! The information set type.
        class info_set_type
        {
        public:
            //! The train kind type.
            using train_kind_type = bobura::model::train_kind<string_type>;

            /*!
                \brief Creates an information set.

                \param original_index An original index.
                \param referred       A referred status.
                \param train_kind     A train kind.
            */
            info_set_type(boost::optional<size_type> original_index, bool referred, train_kind_type train_kind);


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
        noexcept;


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
