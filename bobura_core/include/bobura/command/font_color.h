/*! \file
    \brief The definition of bobura::command::font_color.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FONTCOLOR_H)
#define BOBURA_COMMAND_FONTCOLOR_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a font and color command.

        \tparam Traits         A traits type.
        \tparam Dialog         A dialog type.
        \tparam PointUnitSize  A point unit size type.
        \tparam Color          A color type.
        \tparam MessageCatalog A message catalog type.
        \tparam DialogTraits   A dialog traits type.
    */
    template <
        typename Traits,
        typename Dialog,
        typename PointUnitSize,
        typename Color,
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

        //! The point unit size type.
        using point_unit_size_type = PointUnitSize;

        //! The color type.
        using color_type = Color;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The dialog traits type.
        using dialog_traits_type = DialogTraits;

        //! The base type.
        using base_type = command_base<traits_type>;


        // constructors and destructor

        /*!
            \brief Create a font and color command.

            \param message_catalog A message catalog.
        */
        explicit font_color(const message_catalog_type& message_catalog);

        /*!
            \brief Destroys a font and color command.
        */
        virtual ~font_color()
        TETENGO2_STDALT_NOEXCEPT;


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
