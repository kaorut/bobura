/*! \file
    \brief The definition of bobura::message::font_color_dialog.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_FONTCOLORDIALOG_H)
#define BOBURA_MESSAGE_FONTCOLORDIALOG_H

#include <cassert>
#include <functional>
#include <utility>
#include <vector>

#include <boost/optional.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>


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
            \param update                 An update function.
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
        \tparam FontColor      A font and color type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename IntSize, typename Canvas, typename FontColor, typename MessageCatalog>
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

        //! The font and color type.
        using font_color_type = FontColor;

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
            const std::vector<font_color_type>&   font_color_list,
            const boost::optional<int_size_type>& current_category_index,
            const dimension_type&                 canvas_dimension,
            const message_catalog_type&           message_catalog
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
            const position_type diagram_part_position{};
            const dimension_type diagram_part_dimension{ m_canvas_dimension.width() / 2, m_canvas_dimension.height() };
            draw_diagram_part(canvas, diagram_part_position, diagram_part_dimension);

            const position_type timetable_part_position{
                position_unit_type::from(m_canvas_dimension.width() / 2),
                position_unit_type{}
            };
            const dimension_type timetable_part_dimension{
                m_canvas_dimension.width() / 2, m_canvas_dimension.height()
            };
            draw_timetable_part(canvas, timetable_part_position, timetable_part_dimension);
        }


    private:
        // types

        using string_type = typename canvas_type::string_type;

        using position_type = typename canvas_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using size_type = typename dimension_unit_type::value_type;

        using background_type = typename canvas_type::background_type;

        using solid_background_type = typename canvas_type::solid_background_type;


        // variables

        const std::vector<font_color_type>& m_font_color_list;

        const boost::optional<int_size_type>& m_current_category_index;

        const dimension_type m_canvas_dimension;

        const message_catalog_type& m_message_catalog;


        // functions

        void draw_diagram_part(canvas_type& canvas, const position_type& position, const dimension_type& dimension)
        const
        {
            draw_sample(
                canvas,
                position,
                dimension,
                [](const font_color_type& fc) -> const boost::optional<font_type>& { return fc.diagram_font(); },
                [](const font_color_type& fc) -> const boost::optional<color_type>& { return fc.diagram_color(); },
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Diagram"))
            );
        }

        void draw_timetable_part(canvas_type& canvas, const position_type& position, const dimension_type& dimension)
        const
        {
            draw_sample(
                canvas,
                position,
                dimension,
                [](const font_color_type& fc) -> const boost::optional<font_type>& { return fc.timetable_font(); },
                [](const font_color_type& fc) -> const boost::optional<color_type>& { return fc.timetable_color(); },
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Timetable"))
            );
        }

        void draw_sample(
            canvas_type&                                                                      canvas,
            const position_type&                                                              position,
            const dimension_type&                                                             dimension,
            const std::function<const boost::optional<font_type>& (const font_color_type&)>&  get_font,
            const std::function<const boost::optional<color_type>& (const font_color_type&)>& get_color,
            const string_type&                                                                text
        )
        const
        {
            assert(get_color(m_font_color_list[0]));
            auto p_background =
                tetengo2::stdalt::make_unique<solid_background_type>(*get_color(m_font_color_list[0]));
            canvas.set_background(std::move(p_background));
            canvas.fill_rectangle(position, dimension);

            if (
                !m_current_category_index ||
                *m_current_category_index == 0 ||
                *m_current_category_index >= m_font_color_list.size()
            )
            {
                return;
            }
            const auto font = get_font(m_font_color_list[*m_current_category_index]);
            const auto color = get_color(m_font_color_list[*m_current_category_index]);
            if (!font && !color)
                return;

            canvas.set_color(color ? *color : color_type{ 0x40, 0x40, 0x40 });
            if (font)
            {
                canvas.set_font(*font);

                const position_type text_position{
                    position.left() + position_unit_type{ 1 }, sample_text_top(canvas, position, dimension, text)
                };
                canvas.draw_text(text, text_position);
            }
            else
            {
                canvas.set_line_width(dimension_unit_type{ 1 } / 12);

                const auto line_top = position.top() + position_unit_type::from(dimension.height()) / 2;
                const position_type line_from{ position.left(), line_top };
                const position_type line_to{ position.left() + position_unit_type::from(dimension.width()), line_top };
                canvas.draw_line(line_from, line_to);
            }
        }

        position_unit_type sample_text_top(
            const canvas_type&    canvas,
            const position_type&  base_position,
            const dimension_type& base_dimension,
            const string_type&    text
        )
        const
        {
            const auto& base_top = base_position.top();
            const auto& base_height = base_dimension.height();
            const auto& text_height = canvas.calc_text_dimension(text).height();

            if (base_height > text_height)
                return base_top + position_unit_type::from((base_height - text_height) / 2);
            else
                return position_unit_type{};
        }


    };


    /*!
        \brief The class template for a mouse click observer of the diagram font button.

        \tparam Size           A size type.
        \tparam Dialog         A dialog type.
        \tparam FontDialog     A font dialog type.
        \tparam Canvas         A canvas type.
        \tparam FontColor      A font and color type.
        \tparam MessageCatalog A message catalog type.
    */
    template <
        typename Size,
        typename Dialog,
        typename FontDialog,
        typename Canvas,
        typename FontColor,
        typename MessageCatalog
    >
    class diagram_font_button_mouse_clicked
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

        //! The font and color type.
        using font_color_type = FontColor;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The update type.
        using update_type = std::function<void ()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the diagram font button.

            \param dialog                 A dialog.
            \param font_color_list        A font and color list.
            \param current_category_index A current category index.
            \param update                 An update function.
            \param message_catalog        A message catalog.
        */
        diagram_font_button_mouse_clicked(
            dialog_type&                      dialog,
            std::vector<font_color_type>&     font_color_list,
            const boost::optional<size_type>& current_category_index,
            const update_type                 update,
            const message_catalog_type&       message_catalog
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
        {
            if (!m_current_category_index)
                return;

            font_dialog_type font_dialog{ *m_font_color_list[*m_current_category_index].diagram_font(), m_dialog };

            const auto ok = font_dialog.do_modal();
            if (!ok)
                return;

            m_font_color_list[*m_current_category_index].set_diagram_font(boost::make_optional(font_dialog.result()));

            m_update();
        }


    private:
        // variables

        dialog_type& m_dialog;

        std::vector<font_color_type>& m_font_color_list;

        const boost::optional<size_type>& m_current_category_index;

        update_type m_update;

        const message_catalog_type& m_message_catalog;


    };


    /*!
        \brief The class template for a mouse click observer of the diagram color button.

        \tparam Size           A size type.
        \tparam Dialog         A dialog type.
        \tparam ColorDialog    A color dialog type.
        \tparam Canvas         A canvas type.
        \tparam FontColor      A font and color type.
        \tparam MessageCatalog A message catalog type.
    */
    template <
        typename Size,
        typename Dialog,
        typename ColorDialog,
        typename Canvas,
        typename FontColor,
        typename MessageCatalog
    >
    class diagram_color_button_mouse_clicked
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

        //! The font and color type.
        using font_color_type = FontColor;

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
            \param update                 An update function.
            \param message_catalog        A message catalog.
        */
        explicit diagram_color_button_mouse_clicked(
            dialog_type&                      dialog,
            std::vector<font_color_type>&     font_color_list,
            const boost::optional<size_type>& current_category_index,
            const update_type                 update,
            const message_catalog_type&       message_catalog
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
        {
            if (!m_current_category_index)
                return;

            color_dialog_type color_dialog{ m_font_color_list[*m_current_category_index].diagram_color(), m_dialog };

            const auto ok = color_dialog.do_modal();
            if (!ok)
                return;

            m_font_color_list[*m_current_category_index].set_diagram_color(boost::make_optional(color_dialog.result()));

            m_update();
        }


    private:
        // variables

        dialog_type& m_dialog;

        std::vector<font_color_type>& m_font_color_list;

        const boost::optional<size_type>& m_current_category_index;

        update_type m_update;

        const message_catalog_type& m_message_catalog;


    };


    /*!
        \brief The class template for a mouse click observer of the timetable font button.

        \tparam Size           A size type.
        \tparam Dialog         A dialog type.
        \tparam FontDialog     A font dialog type.
        \tparam Canvas         A canvas type.
        \tparam FontColor      A font and color type.
        \tparam MessageCatalog A message catalog type.
    */
    template <
        typename Size,
        typename Dialog,
        typename FontDialog,
        typename Canvas,
        typename FontColor,
        typename MessageCatalog
    >
    class timetable_font_button_mouse_clicked
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

        //! The font and color type.
        using font_color_type = FontColor;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The update type.
        using update_type = std::function<void ()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the timetable font button.

            \param dialog                 A dialog.
            \param font_color_list        A font and color list.
            \param current_category_index A current category index.
            \param update                 An update function.
            \param message_catalog        A message catalog.
        */
        timetable_font_button_mouse_clicked(
            dialog_type&                      dialog,
            std::vector<font_color_type>&     font_color_list,
            const boost::optional<size_type>& current_category_index,
            const update_type                 update,
            const message_catalog_type&       message_catalog
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
        {
            if (!m_current_category_index)
                return;

            font_dialog_type font_dialog{ *m_font_color_list[*m_current_category_index].timetable_font(), m_dialog };

            const auto ok = font_dialog.do_modal();
            if (!ok)
                return;

            m_font_color_list[*m_current_category_index].set_timetable_font(
                boost::make_optional(font_dialog.result())
            );

            m_update();
        }


    private:
        // variables

        dialog_type& m_dialog;

        std::vector<font_color_type>& m_font_color_list;

        const boost::optional<size_type>& m_current_category_index;

        update_type m_update;

        const message_catalog_type& m_message_catalog;


    };


    /*!
        \brief The class template for a mouse click observer of the timetable color button.

        \tparam Size           A size type.
        \tparam Dialog         A dialog type.
        \tparam ColorDialog    A color dialog type.
        \tparam Canvas         A canvas type.
        \tparam FontColor      A font and color type.
        \tparam MessageCatalog A message catalog type.
    */
    template <
        typename Size,
        typename Dialog,
        typename ColorDialog,
        typename Canvas,
        typename FontColor,
        typename MessageCatalog
    >
    class timetable_color_button_mouse_clicked
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

        //! The font and color type.
        using font_color_type = FontColor;

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
            \param update                 An update function.
            \param message_catalog        A message catalog.
        */
        explicit timetable_color_button_mouse_clicked(
            dialog_type&                      dialog,
            std::vector<font_color_type>&     font_color_list,
            const boost::optional<size_type>& current_category_index,
            const update_type                 update,
            const message_catalog_type&       message_catalog
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
        {
            if (!m_current_category_index)
                return;

            color_dialog_type color_dialog{ m_font_color_list[*m_current_category_index].timetable_color(), m_dialog };

            const auto ok = color_dialog.do_modal();
            if (!ok)
                return;

            m_font_color_list[*m_current_category_index].set_timetable_color(
                boost::make_optional(color_dialog.result())
            );

            m_update();
        }


    private:
        // variables

        dialog_type& m_dialog;

        std::vector<font_color_type>& m_font_color_list;

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
