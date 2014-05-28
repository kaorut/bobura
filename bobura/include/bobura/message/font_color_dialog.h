/*! \file
    \brief The definition of bobura::message::font_color_dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_FONTCOLORDIALOG_H)
#define BOBURA_MESSAGE_FONTCOLORDIALOG_H

#include <cassert>
#include <functional>
#include <utility>
#include <vector>

#include <boost/optional.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>


namespace bobura { namespace message { namespace font_color_dialog
{
    /*!
        \brief The class template for a selection change observer of the category list box.

        \tparam Size    A size type.
        \tparam ListBox A list box type.
    */
    template <typename Size, typename ListBox>
    class category_list_box_selection_changed
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The list box type.
        using list_box_type = ListBox;

        //! The update type.
        using update_type = std::function<void ()>;


        // constructors and destructor

        /*!
            \brief Create a selection change observer of the category list box.

            \param current_category_index A current category index.
            \param list_box               A list box.
            \param update                 A update function.
        */
        category_list_box_selection_changed(
            boost::optional<size_type>& current_category_index,
            const list_box_type&        list_box,
            const update_type           update
        )
        :
        m_current_category_index(current_category_index),
        m_list_box(list_box),
        m_update(update)
        {}


        // functions

        /*!
            \brief Called when the selection of the category list box is changed.
        */
        void operator()()
        const
        {
            m_current_category_index = m_list_box.selected_value_index();
            m_update();
        }


    private:
        // variables

        boost::optional<size_type>& m_current_category_index;

        const list_box_type& m_list_box;

        update_type m_update;


    };


    /*!
        \brief The class template for a paint observer of the sample picture box.

        \tparam IntSize        A integer size type.
        \tparam Canvas         A canvas type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename IntSize, typename Canvas, typename MessageCatalog>
    class sample_picture_box_paint
    {
    public:
        // types

        //! The integer size type.
        using int_size_type = IntSize;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The font type.
        using font_type = typename Canvas::font_type;

        //! The color type.
        using color_type = typename Canvas::color_type;

        //! The internal font and color type.
        using internal_font_color_type = std::pair<boost::optional<font_type>, boost::optional<color_type>>;

        //! The dimension type.
        using dimension_type = typename Canvas::dimension_type;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;


        // constructors and destructor

        /*!
            \brief Creates a paint observer of the sample picture box.

            \param font_color_list        A font and color list.
            \param current_category_index A current category index.
            \param canvas_dimension       A canvas dimension.
            \param message_catalog        A message catalog.
        */
        sample_picture_box_paint(
            const std::vector<internal_font_color_type>& font_color_list,
            const boost::optional<int_size_type>&        current_category_index,
            const dimension_type&                        canvas_dimension,
            const message_catalog_type&                  message_catalog
        )
        :
        m_font_color_list(font_color_list),
        m_current_category_index(current_category_index),
        m_canvas_dimension(canvas_dimension),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas)
        const
        {
            assert(m_font_color_list[0].second);
            auto p_background = tetengo2::stdalt::make_unique<solid_background_type>(*m_font_color_list[0].second);
            canvas.set_background(std::move(p_background));
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), m_canvas_dimension);

            if (
                !m_current_category_index ||
                *m_current_category_index == 0 ||
                *m_current_category_index >= m_font_color_list.size()
            )
            {
                return;
            }

            assert(m_font_color_list[*m_current_category_index].first);
            canvas.set_font(*m_font_color_list[*m_current_category_index].first);
            canvas.set_color(
                m_font_color_list[*m_current_category_index].second ?
                *m_font_color_list[*m_current_category_index].second : color_type(0x40, 0x40, 0x40)
            );

            const string_type text{ m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:SAMPLE")) };

            const auto text_and_line_tops = sample_text_and_line_tops(canvas, text);

            canvas.draw_text(text, position_type(left_type(1), text_and_line_tops.first));

            canvas.set_line_width(width_type(size_type(1, 12)));
            canvas.set_line_style(canvas_type::line_style_type::solid);
            canvas.draw_line(
                position_type(left_type(0), text_and_line_tops.second),
                position_type(
                    left_type::from(tetengo2::gui::dimension<dimension_type>::width(m_canvas_dimension)),
                    text_and_line_tops.second
                )
            );
        }


    private:
        // types

        using string_type = typename canvas_type::string_type;

        using position_type = typename canvas_type::position_type;

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using size_type = typename width_type::value_type;

        using background_type = typename canvas_type::background_type;

        using solid_background_type = typename canvas_type::solid_background_type;


        // variables

        const std::vector<internal_font_color_type>& m_font_color_list;

        const boost::optional<int_size_type>& m_current_category_index;

        const dimension_type m_canvas_dimension;

        const message_catalog_type& m_message_catalog;


        // functions

        std::pair<top_type, top_type> sample_text_and_line_tops(const canvas_type& canvas, const string_type& text)
        const
        {
            const auto& canvas_height = tetengo2::gui::dimension<dimension_type>::height(m_canvas_dimension);
            const auto& text_height =
                tetengo2::gui::dimension<dimension_type>::height(canvas.calc_text_dimension(text));

            if (canvas_height > text_height)
            {
                const auto text_top = top_type::from((canvas_height - text_height) / 2);
                const auto line_top = text_top + top_type::from(text_height);
                return std::make_pair(text_top, line_top);
            }
            else
            {
                const auto line_top = top_type::from(canvas_height);
                const auto text_top = line_top - top_type::from(text_height);
                return std::make_pair(text_top, line_top);
            }
        }


    };


    /*!
        \brief The class template for a mouse click observer of the font button.

        \tparam Size           A size type.
        \tparam Dialog         A dialog type.
        \tparam FontDialog     A font dialog type.
        \tparam Canvas         A canvas type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename Size, typename Dialog, typename FontDialog, typename Canvas, typename MessageCatalog>
    class font_button_mouse_clicked
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The dialog type.
        using dialog_type = Dialog;

        //! The font dialog type.
        using font_dialog_type = FontDialog;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The font type.
        using font_type = typename Canvas::font_type;

        //! The color type.
        using color_type = typename Canvas::color_type;

        //! The internal font and color type.
        using internal_font_color_type = std::pair<boost::optional<font_type>, boost::optional<color_type>>;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The update type.
        using update_type = std::function<void ()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the font button.

            \param dialog                 A dialog.
            \param font_color_list        A font and color list.
            \param current_category_index A current category index.
            \param update                 A update function.
            \param message_catalog        A message catalog.
        */
        font_button_mouse_clicked(
            dialog_type&                           dialog,
            std::vector<internal_font_color_type>& font_color_list,
            const boost::optional<size_type>&      current_category_index,
            const update_type                      update,
            const message_catalog_type&            message_catalog
        )
        :
        m_dialog(dialog),
        m_font_color_list(font_color_list),
        m_current_category_index(current_category_index),
        m_update(update),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Called when the font button is clicked.
        */
        void operator()()
        const
        {
            if (!m_current_category_index)
                return;

            font_dialog_type font_dialog(m_font_color_list[*m_current_category_index].first, m_dialog);

            const auto ok = font_dialog.do_modal();
            if (!ok)
                return;

            m_font_color_list[*m_current_category_index].first = boost::make_optional(font_dialog.result());

            m_update();
        }


    private:
        // variables

        dialog_type& m_dialog;

        std::vector<internal_font_color_type>& m_font_color_list;

        const boost::optional<size_type>& m_current_category_index;

        update_type m_update;

        const message_catalog_type& m_message_catalog;


    };


    /*!
        \brief The class template for a mouse click observer of the color button.

        \tparam Size           A size type.
        \tparam Dialog         A dialog type.
        \tparam ColorDialog    A color dialog type.
        \tparam Canvas         A canvas type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename Size, typename Dialog, typename ColorDialog, typename Canvas, typename MessageCatalog>
    class color_button_mouse_clicked
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The dialog type.
        using dialog_type = Dialog;

        //! The color dialog type.
        using color_dialog_type = ColorDialog;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The font type.
        using font_type = typename Canvas::font_type;

        //! The color type.
        using color_type = typename Canvas::color_type;

        //! The internal font and color type.
        using internal_font_color_type = std::pair<boost::optional<font_type>, boost::optional<color_type>>;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The update type.
        using update_type = std::function<void ()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the color button.

            \param dialog                 A dialog.
            \param font_color_list        A font and color list.
            \param current_category_index A current category index.
            \param update                 A update function.
            \param message_catalog        A message catalog.
        */
        explicit color_button_mouse_clicked(
            dialog_type&                           dialog,
            std::vector<internal_font_color_type>& font_color_list,
            const boost::optional<size_type>&      current_category_index,
            const update_type                      update,
            const message_catalog_type&            message_catalog
        )
        :
        m_dialog(dialog),
        m_font_color_list(font_color_list),
        m_current_category_index(current_category_index),
        m_update(update),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Called when the font button is clicked.
        */
        void operator()()
        const
        {
            if (!m_current_category_index)
                return;

            color_dialog_type color_dialog(m_font_color_list[*m_current_category_index].second, m_dialog);

            const auto ok = color_dialog.do_modal();
            if (!ok)
                return;

            m_font_color_list[*m_current_category_index].second = boost::make_optional(color_dialog.result());

            m_update();
        }


    private:
        // variables

        dialog_type& m_dialog;

        std::vector<internal_font_color_type>& m_font_color_list;

        const boost::optional<size_type>& m_current_category_index;

        update_type m_update;

        const message_catalog_type& m_message_catalog;


    };


    /*!
        \brief The class template for a mouse click observer of the OK button.

        \tparam Dialog A dialog type.
    */
    template <typename Dialog>
    class ok_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        using dialog_type = Dialog;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the OK button.

            \param dialog A dialog.
        */
        explicit ok_button_mouse_clicked(dialog_type& dialog)
        :
        m_dialog(dialog)
        {}


        // functions

        /*!
            \brief Called when the OK button is clicked.
        */
        void operator()()
        const
        {
            m_dialog.set_result(dialog_type::result_type::accepted);
            m_dialog.close();
        }


    private:
        // variables

        dialog_type& m_dialog;


    };


    /*!
        \brief The class template for a mouse click observer of the cancel button.

        \tparam Dialog A dialog type.
    */
    template <typename Dialog>
    class cancel_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        using dialog_type = Dialog;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the cancel button.

            \param dialog A dialog.
        */
        explicit cancel_button_mouse_clicked(dialog_type& dialog)
        :
        m_dialog(dialog)
        {}


        // functions

        /*!
            \brief Called when the cancel button is clicked.
        */
        void operator()()
        const
        {
            m_dialog.set_result(dialog_type::result_type::canceled);
            m_dialog.close();
        }


    private:
        // variables

        dialog_type& m_dialog;


    };


}}}


#endif
