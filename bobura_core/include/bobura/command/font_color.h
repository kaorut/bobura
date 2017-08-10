/*! \file
    \brief The definition of bobura::command::font_color.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FONTCOLOR_H)
#define BOBURA_COMMAND_FONTCOLOR_H

#include <memory>

#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a font and color command.

        \tparam Traits             A traits type.
        \tparam Dialog             A dialog type.
        \tparam PointDimensionUnit A point dimension unit type.
        \tparam Color              A color type.
        \tparam Canvas             A canvas type.
        \tparam FontDialog         A font dialog type.
        \tparam ColorDialog        A color dialog type.
        \tparam MessageCatalog     A message catalog type.
        \tparam DialogTraits       A dialog traits type.
    */
    template <
        typename Traits,
        typename Dialog,
        typename PointDimensionUnit,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog,
        typename MessageCatalog,
        typename DialogTraits
    >
    class font_color : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The dialog type.
        using dialog_type = Dialog;

        //! The point dimension unit type.
        using point_dimension_unit_type = PointDimensionUnit;

        //! The color type.
        using color_type = Color;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The font dialog type.
        using font_dialog_type = FontDialog;

        //! The color dialog type.
        using color_dialog_type = ColorDialog;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The dialog traits type.
        using dialog_traits_type = DialogTraits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The abstract window type.
        using abstract_window_type = typename base_type::abstract_window_type;

        //! The model type.
        using model_type = typename base_type::model_type;


        // constructors and destructor

        /*!
            \brief Create a font and color command.

            \param message_catalog A message catalog.
        */
        explicit font_color(const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the font and color command.
        */
        virtual ~font_color()
        noexcept;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const override;


    };


}}


#endif
