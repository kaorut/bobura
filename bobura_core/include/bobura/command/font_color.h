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

#include <bobura/basic_type_list.h>
#include <bobura/command/command_base.h>
#include <bobura/font_color_dialog.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a font and color command.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class font_color : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The font and color dialog type.
        using font_color_dialog_type =
            font_color_dialog<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                boost::mpl::at<ui_type_list, type::ui::point_unit_size>::type,
                boost::mpl::at<ui_type_list, type::ui::color>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;

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
