/*! \file
    \brief The definition of bobura::command::font_color.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FONTCOLOR_H)
#define BOBURA_COMMAND_FONTCOLOR_H

#include <memory>

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a font and color command.
    */
    class font_color : public command_base
    {
    public:
        // types

        //! The base type.
        using base_type = command_base;

        //! The font and color dialog type.
        using font_color_dialog_type = boost::mpl::at<dialog_type_list, type::dialog::font_color_dialog>::type;

        //! The dialog base type.
        using dialog_base_type = font_color_dialog_type::base_type;

        //! The message catalog type.
        using message_catalog_type = font_color_dialog_type::message_catalog_type;


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