/*! \file
    \brief The definition of bobura::message::train_kind_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TRAINKINDDIALOG_H)
#define BOBURA_MESSAGE_TRAINKINDDIALOG_H

#include <algorithm> // IWYU pragma: keep
#include <cassert>
#include <functional>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

#include <boost/throw_exception.hpp>

#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>


namespace bobura::message::train_kind_dialog {
    /*!
        \brief The class template for a selection change observer of the train kind list box.

        \tparam Size    A size type.
        \tparam ListBox A list box type.
    */
    template <typename Size, typename ListBox>
    class train_kind_list_box_selection_changed
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The list box type.
        using list_box_type = ListBox;

        //! The update type.
        using update_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Create a selection change observer of the train kind list box.

            \param current_train_kind_index A current train kind index.
            \param list_box                 A list box.
            \param update                   A update function.
        */
        train_kind_list_box_selection_changed(
            tetengo2::stdalt::optional<size_type>& current_train_kind_index,
            const list_box_type&                   list_box,
            const update_type                      update)
        : m_current_train_kind_index{ current_train_kind_index }, m_list_box{ list_box }, m_update{ update }
        {}


        // functions

        /*!
            \brief Called when the selection of the train kind list box is changed.
        */
        void operator()() const
        {
            m_current_train_kind_index = m_list_box.selected_value_index();
            m_update();
        }


    private:
        // variables

        tetengo2::stdalt::optional<size_type>& m_current_train_kind_index;

        const list_box_type& m_list_box;

        update_type m_update;
    };


    /*!
        \brief The class template for a mouse click observer of the add button.

        \tparam InfoSet        An information set type.
        \tparam Size           A size type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename InfoSet, typename Size, typename MessageCatalog>
    class add_button_mouse_clicked
    {
    public:
        // types

        //! The information set type.
        using info_set_type = InfoSet;

        //! The size type.
        using size_type = Size;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The sync type.
        using sync_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the add button.

            \param info_sets                Information sets.
            \param current_train_kind_index A current train kind index.
            \param sync                     A sync function type.
            \param message_catalog          A message catalog.
        */
        add_button_mouse_clicked(
            std::vector<info_set_type>&                  info_sets,
            const tetengo2::stdalt::optional<size_type>& current_train_kind_index,
            const sync_type                              sync,
            const message_catalog_type&                  message_catalog)
        : m_info_sets{ info_sets }, m_current_train_kind_index{ current_train_kind_index }, m_sync{ sync },
          m_message_catalog{ message_catalog }
        {}


        // functions

        /*!
            \brief Called when the add button is clicked.
        */
        void operator()() const
        {
            const auto insertion_position = m_current_train_kind_index ?
                                                std::next(m_info_sets.begin(), *m_current_train_kind_index) :
                                                m_info_sets.end();

            train_kind_type new_kind{ m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:New Kind")),
                                      train_kind_type::default_().abbreviation(),
                                      train_kind_type::default_().diagram_font(),
                                      train_kind_type::default_().diagram_color(),
                                      train_kind_type::default_().diagram_line_weight(),
                                      train_kind_type::default_().diagram_line_style(),
                                      train_kind_type::default_().timetable_font(),
                                      train_kind_type::default_().timetable_color() };
            m_info_sets.emplace(insertion_position, TETENGO2_STDALT_NULLOPT, false, std::move(new_kind));

            m_sync();
        }


    private:
        // types

        using train_kind_type = typename info_set_type::train_kind_type;

        using string_type = typename train_kind_type::string_type;

        using font_type = typename train_kind_type::font_type;

        using color_type = typename train_kind_type::color_type;


        // variables

        std::vector<info_set_type>& m_info_sets;

        const tetengo2::stdalt::optional<size_type>& m_current_train_kind_index;

        sync_type m_sync;

        const message_catalog_type& m_message_catalog;
    };


    /*!
        \brief The class template for a mouse click observer of the delete button.

        \tparam InfoSet An information set type.
        \tparam Size    A size type.
    */
    template <typename InfoSet, typename Size>
    class delete_button_mouse_clicked
    {
    public:
        // types

        //! The information set type.
        using info_set_type = InfoSet;

        //! The size type.
        using size_type = Size;

        //! The sync type.
        using sync_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the delete button.

            \param info_sets                Information sets.
            \param current_train_kind_index A current train kind index.
            \param sync                     A sync function type.
        */
        delete_button_mouse_clicked(
            std::vector<info_set_type>&            info_sets,
            tetengo2::stdalt::optional<size_type>& current_train_kind_index,
            const sync_type                        sync)
        : m_info_sets{ info_sets }, m_current_train_kind_index{ current_train_kind_index }, m_sync{ sync }
        {}


        // functions

        /*!
            \brief Called when the delete button is clicked.
        */
        void operator()() const
        {
            assert(m_current_train_kind_index);
            assert(*m_current_train_kind_index < m_info_sets.size());
            const auto deletion_position = std::next(m_info_sets.begin(), *m_current_train_kind_index);

            m_info_sets.erase(deletion_position);
            if (*m_current_train_kind_index >= m_info_sets.size())
            {
                if (m_info_sets.empty())
                    m_current_train_kind_index = TETENGO2_STDALT_NULLOPT;
                else
                    m_current_train_kind_index = tetengo2::stdalt::make_optional(m_info_sets.size() - 1);
            }

            m_sync();
        }


    private:
        // variables

        std::vector<info_set_type>& m_info_sets;

        tetengo2::stdalt::optional<size_type>& m_current_train_kind_index;

        sync_type m_sync;
    };


    /*!
        \brief The class template for a mouse click observer of the up button.

        \tparam InfoSet An information set type.
        \tparam Size    A size type.
    */
    template <typename InfoSet, typename Size>
    class up_button_mouse_clicked
    {
    public:
        // types

        //! The information set type.
        using info_set_type = InfoSet;

        //! The size type.
        using size_type = Size;

        //! The sync type.
        using sync_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the up button.

            \param info_sets                Information sets.
            \param current_train_kind_index A current train kind index.
            \param sync                     A sync function type.
        */
        up_button_mouse_clicked(
            std::vector<info_set_type>&            info_sets,
            tetengo2::stdalt::optional<size_type>& current_train_kind_index,
            const sync_type                        sync)
        : m_info_sets{ info_sets }, m_current_train_kind_index{ current_train_kind_index }, m_sync{ sync }
        {}


        // functions

        /*!
            \brief Called when the up button is clicked.
        */
        void operator()() const
        {
            assert(m_current_train_kind_index);
            assert(1 <= *m_current_train_kind_index && *m_current_train_kind_index < m_info_sets.size());

            std::swap(m_info_sets[*m_current_train_kind_index - 1], m_info_sets[*m_current_train_kind_index]);
            --(*m_current_train_kind_index);

            m_sync();
        }


    private:
        // variables

        std::vector<info_set_type>& m_info_sets;

        tetengo2::stdalt::optional<size_type>& m_current_train_kind_index;

        sync_type m_sync;
    };


    /*!
        \brief The class template for a mouse click observer of the down button.

        \tparam InfoSet An information set type.
        \tparam Size    A size type.
    */
    template <typename InfoSet, typename Size>
    class down_button_mouse_clicked
    {
    public:
        // types

        //! The information set type.
        using info_set_type = InfoSet;

        //! The size type.
        using size_type = Size;

        //! The sync type.
        using sync_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the down button.

            \param info_sets                Information sets.
            \param current_train_kind_index A current train kind index.
            \param sync                     A sync function type.
        */
        down_button_mouse_clicked(
            std::vector<info_set_type>&            info_sets,
            tetengo2::stdalt::optional<size_type>& current_train_kind_index,
            const sync_type                        sync)
        : m_info_sets{ info_sets }, m_current_train_kind_index{ current_train_kind_index }, m_sync{ sync }
        {}


        // functions

        /*!
            \brief Called when the down button is clicked.
        */
        void operator()() const
        {
            assert(m_current_train_kind_index);
            assert(*m_current_train_kind_index + 1 < m_info_sets.size());

            std::swap(m_info_sets[*m_current_train_kind_index], m_info_sets[*m_current_train_kind_index + 1]);
            ++(*m_current_train_kind_index);

            m_sync();
        }


    private:
        // variables

        std::vector<info_set_type>& m_info_sets;

        tetengo2::stdalt::optional<size_type>& m_current_train_kind_index;

        sync_type m_sync;
    };


    /*!
        \brief The class template for a change observer of the name text box.
    */
    class name_text_box_changed
    {
    public:
        // types

        //! The apply type.
        using apply_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Create a change observer of the name text box.

            \param apply An apply function
        */
        explicit name_text_box_changed(const apply_type apply) : m_apply{ apply } {}


        // functions

        /*!
            \brief Called when the name text box is changed.
        */
        void operator()() const
        {
            m_apply();
        }


    private:
        // variables

        apply_type m_apply;
    };


    /*!
        \brief The class template for a change observer of the abbreviation text box.
    */
    class abbreviation_text_box_changed
    {
    public:
        // types

        //! The apply type.
        using apply_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Create a change observer of the abbreviation text box.

            \param apply An apply function
        */
        explicit abbreviation_text_box_changed(const apply_type apply) : m_apply{ apply } {}


        // functions

        /*!
            \brief Called when the abbreviation text box is changed.
        */
        void operator()() const
        {
            m_apply();
        }


    private:
        // variables

        apply_type m_apply;
    };


    /*!
        \brief The class template for a mouse click observer of the diagram font button.

        \tparam Dialog     A dialog type.
        \tparam FontDialog A font dialog type.
    */
    template <typename Dialog, typename FontDialog>
    class diagram_font_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        using dialog_type = Dialog;

        //! The font dialog type.
        using font_dialog_type = FontDialog;

        //! The font type.
        using font_type = typename font_dialog_type::font_type;

        //! The apply type.
        using apply_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the diagram font button.

            \param dialog A dialog,
            \param font   A font.
            \param apply  An apply function.
        */
        diagram_font_button_mouse_clicked(dialog_type& dialog, font_type& font, const apply_type apply)
        : m_dialog{ dialog }, m_font{ font }, m_apply{ apply }
        {}


        // functions

        /*!
            \brief Called when the font button is clicked.
        */
        void operator()() const
        {
            font_dialog_type font_dialog{ m_font, m_dialog };

            const auto ok = font_dialog.do_modal();
            if (!ok)
                return;

            m_font = font_dialog.result();

            m_apply();
        }


    private:
        // variables

        dialog_type& m_dialog;

        font_type& m_font;

        apply_type m_apply;
    };


    /*!
        \brief The class template for a mouse click observer of the diagram color button.

        \tparam Dialog      A dialog type.
        \tparam ColorDialog A color dialog type.
    */
    template <typename Dialog, typename ColorDialog>
    class diagram_color_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        using dialog_type = Dialog;

        //! The color dialog type.
        using color_dialog_type = ColorDialog;

        //! The color type.
        using color_type = typename color_dialog_type::color_type;

        //! The apply type.
        using apply_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the diagram color button.

            \param dialog A dialog,
            \param color  A color.
            \param apply  An apply function.
        */
        diagram_color_button_mouse_clicked(dialog_type& dialog, color_type& color, const apply_type apply)
        : m_dialog{ dialog }, m_color{ color }, m_apply{ apply }
        {}


        // functions

        /*!
            \brief Called when the font button is clicked.
        */
        void operator()() const
        {
            color_dialog_type color_dialog{ m_color, m_dialog };

            const auto ok = color_dialog.do_modal();
            if (!ok)
                return;

            m_color = color_dialog.result();

            m_apply();
        }


    private:
        // variables

        dialog_type& m_dialog;

        color_type& m_color;

        apply_type m_apply;
    };


    /*!
        \brief The class template for a selection change observer of the diagram weight dropdown box.
    */
    class diagram_weight_dropdown_box_selection_changed
    {
    public:
        // types

        //! The apply type.
        using apply_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Create a selection change observer of the weight dropdown box.

            \param apply An apply function
        */
        explicit diagram_weight_dropdown_box_selection_changed(const apply_type apply) : m_apply{ apply } {}


        // functions

        /*!
            \brief Called when the selection of the weight dropdown box is changed.
        */
        void operator()() const
        {
            m_apply();
        }


    private:
        // variables

        apply_type m_apply;
    };


    /*!
        \brief The class template for a selection change observer of the diagram line style dropdown box.
    */
    class diagram_line_style_dropdown_box_selection_changed
    {
    public:
        // types

        //! The apply type.
        using apply_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Create a selection change observer of the line style dropdown box.

            \param apply An apply function
        */
        explicit diagram_line_style_dropdown_box_selection_changed(const apply_type apply) : m_apply{ apply } {}


        // functions

        /*!
            \brief Called when the selection of the line style dropdown box is changed.
        */
        void operator()() const
        {
            m_apply();
        }


    private:
        // variables

        apply_type m_apply;
    };


    /*!
        \brief The class template for a mouse click observer of the timetable font button.

        \tparam Dialog     A dialog type.
        \tparam FontDialog A font dialog type.
    */
    template <typename Dialog, typename FontDialog>
    class timetable_font_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        using dialog_type = Dialog;

        //! The font dialog type.
        using font_dialog_type = FontDialog;

        //! The font type.
        using font_type = typename font_dialog_type::font_type;

        //! The apply type.
        using apply_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the timetable font button.

            \param dialog A dialog,
            \param font   A font.
            \param apply  An apply function.
        */
        timetable_font_button_mouse_clicked(dialog_type& dialog, font_type& font, const apply_type apply)
        : m_dialog{ dialog }, m_font{ font }, m_apply{ apply }
        {}


        // functions

        /*!
            \brief Called when the font button is clicked.
        */
        void operator()() const
        {
            font_dialog_type font_dialog{ m_font, m_dialog };

            const auto ok = font_dialog.do_modal();
            if (!ok)
                return;

            m_font = font_dialog.result();

            m_apply();
        }


    private:
        // variables

        dialog_type& m_dialog;

        font_type& m_font;

        apply_type m_apply;
    };


    /*!
        \brief The class template for a mouse click observer of the timetable color button.

        \tparam Dialog      A dialog type.
        \tparam ColorDialog A color dialog type.
    */
    template <typename Dialog, typename ColorDialog>
    class timetable_color_button_mouse_clicked
    {
    public:
        // types

        //! The dialog type.
        using dialog_type = Dialog;

        //! The color dialog type.
        using color_dialog_type = ColorDialog;

        //! The color type.
        using color_type = typename color_dialog_type::color_type;

        //! The apply type.
        using apply_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Creates a mouse click observer of the timetable color button.

            \param dialog A dialog,
            \param color  A color.
            \param apply  An apply function.
        */
        timetable_color_button_mouse_clicked(dialog_type& dialog, color_type& color, const apply_type apply)
        : m_dialog{ dialog }, m_color{ color }, m_apply{ apply }
        {}


        // functions

        /*!
            \brief Called when the font button is clicked.
        */
        void operator()() const
        {
            color_dialog_type color_dialog{ m_color, m_dialog };

            const auto ok = color_dialog.do_modal();
            if (!ok)
                return;

            m_color = color_dialog.result();

            m_apply();
        }


    private:
        // variables

        dialog_type& m_dialog;

        color_type& m_color;

        apply_type m_apply;
    };


    /*!
        \brief The class template for a paint observer of the sample picture box.

        \tparam InfoSet An information set type.
        \tparam IntSize An integer size type.
        \tparam Canvas  A canvas type.
    */
    template <typename InfoSet, typename IntSize, typename Canvas>
    class sample_picture_box_paint
    {
    public:
        // types

        //! The information set type.
        using info_set_type = InfoSet;

        //! The integer size type.
        using int_size_type = IntSize;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The font type.
        using font_type = typename Canvas::font_type;

        //! The color type.
        using color_type = typename Canvas::color_type;

        //! The dimension type.
        using dimension_type = typename Canvas::dimension_type;


        // constructors and destructor

        /*!
            \brief Creates a paint observer of the sample picture box.

            \param info_sets                Information sets.
            \param current_train_kind_index A current train kind index.
            \param background_color         A background color.
            \param timetable_color          A timetable item color.
            \param canvas_dimension         A canvas dimension.
        */
        sample_picture_box_paint(
            const std::vector<info_set_type>&                info_sets,
            const tetengo2::stdalt::optional<int_size_type>& current_train_kind_index,
            const color_type&                                background_color,
            const color_type&                                timetable_color,
            const dimension_type&                            canvas_dimension)
        : m_info_sets{ info_sets }, m_current_train_kind_index{ current_train_kind_index },
          m_background_color{ background_color }, m_timetable_color{ timetable_color }, m_canvas_dimension{
              canvas_dimension
          }
        {}


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas) const
        {
            paint_background(canvas);

            if (!m_current_train_kind_index)
                return;
            const auto& train_kind = m_info_sets[*m_current_train_kind_index].train_kind();

            const position_type  diagram_part_position{};
            const dimension_type diagram_part_dimension{ m_canvas_dimension.width() / 2, m_canvas_dimension.height() };
            draw_diagram_part(train_kind, canvas, diagram_part_position, diagram_part_dimension);

            const position_type  timetable_part_position{ position_unit_type::from(diagram_part_dimension.width()),
                                                         position_unit_type{} };
            const dimension_type timetable_part_dimension{ m_canvas_dimension.width() / 2,
                                                           m_canvas_dimension.height() };
            draw_timetable_part(train_kind, canvas, timetable_part_position, timetable_part_dimension);
        }


    private:
        // types

        using string_type = typename canvas_type::string_type;

        using position_type = typename canvas_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using background_type = typename canvas_type::background_type;

        using solid_background_type = tetengo2::gui::drawing::solid_background;

        using train_kind_type = typename info_set_type::train_kind_type;


        // static functions

        static font_type fixed_size_font(const font_type& base)
        {
            return font_type{ base.family(),    font_type::dialog_font().size(),
                              base.bold(),      base.italic(),
                              base.underline(), base.strikeout() };
        }

        static typename canvas_type::line_style_type
        to_canvas_line_style(const typename train_kind_type::line_style_type line_style)
        {
            switch (line_style)
            {
            case train_kind_type::line_style_type::solid:
                return canvas_type::line_style_type::solid;
            case train_kind_type::line_style_type::dashed:
                return canvas_type::line_style_type::dashed;
            case train_kind_type::line_style_type::dotted:
                return canvas_type::line_style_type::dotted;
            case train_kind_type::line_style_type::dot_dashed:
                return canvas_type::line_style_type::dot_dashed;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown line style."));
            }
        }


        // variables

        const std::vector<info_set_type>& m_info_sets;

        const tetengo2::stdalt::optional<int_size_type>& m_current_train_kind_index;

        const color_type& m_background_color;

        const color_type& m_timetable_color;

        const dimension_type m_canvas_dimension;


        // functions

        void paint_background(canvas_type& canvas) const
        {
            auto p_background = std::make_unique<solid_background_type>(canvas.drawing_details(), m_background_color);
            canvas.set_background(std::move(p_background));
            canvas.fill_rectangle(position_type{}, m_canvas_dimension);
        }

        void draw_diagram_part(
            const train_kind_type& train_kind,
            canvas_type&           canvas,
            const position_type&   position,
            const dimension_type&  dimension) const
        {
            canvas.set_font(fixed_size_font(train_kind.diagram_font()));
            canvas.set_color(train_kind.diagram_color());

            const auto& text = train_kind.abbreviation().empty() ? train_kind.name() : train_kind.abbreviation();
            const auto  text_and_line_tops = diagram_sample_text_and_line_tops(canvas, position, dimension, text);
            canvas.draw_text(
                text, position_type{ position.left() + position_unit_type{ 1 }, text_and_line_tops.first });

            auto line_width = train_kind.diagram_line_weight() == train_kind_type::weight_type::bold ?
                                  dimension_unit_type{ 1 } / 6 :
                                  dimension_unit_type{ 1 } / 12;
            canvas.set_line_width(std::move(line_width));
            canvas.set_line_style(to_canvas_line_style(train_kind.diagram_line_style()));
            canvas.draw_line(
                position_type{ position.left(), text_and_line_tops.second },
                position_type{ position.left() + position_unit_type::from(dimension.width()),
                               text_and_line_tops.second });
        }

        std::pair<position_unit_type, position_unit_type> diagram_sample_text_and_line_tops(
            const canvas_type&    canvas,
            const position_type&  base_position,
            const dimension_type& base_dimension,
            const string_type&    text) const
        {
            const auto& canvas_height = base_dimension.height();
            const auto  text_dimension = canvas.calc_text_dimension(text);
            const auto& text_height = text_dimension.height();

            if (canvas_height > text_height)
            {
                const auto text_top = base_position.top() + position_unit_type::from((canvas_height - text_height) / 2);
                const auto line_top = text_top + position_unit_type::from(text_height);
                return std::make_pair(text_top, line_top);
            }
            else
            {
                const auto line_top = base_position.top() + position_unit_type::from(canvas_height);
                const auto text_top = line_top - position_unit_type::from(text_height);
                return std::make_pair(text_top, line_top);
            }
        }

        void draw_timetable_part(
            const train_kind_type& train_kind,
            canvas_type&           canvas,
            const position_type&   position,
            const dimension_type&  dimension) const
        {
            auto p_background = std::make_unique<solid_background_type>(canvas.drawing_details(), m_background_color);
            canvas.set_background(std::move(p_background));
            canvas.fill_rectangle(position, dimension);

            canvas.set_font(fixed_size_font(train_kind.timetable_font()));
            canvas.set_color(train_kind.timetable_color());

            const auto& text = train_kind.abbreviation().empty() ? train_kind.name() : train_kind.abbreviation();
            const auto  text_dimension = canvas.calc_text_dimension(text);
            const auto  text_position = timetable_sample_text_position(position, dimension, text_dimension);
            canvas.draw_text(text, text_position);

            canvas.set_line_width(dimension_unit_type{ 1 } / 12);
            canvas.set_line_style(canvas_type::line_style_type::solid);
            canvas.set_color(m_timetable_color);

            const auto  line_positions = timetable_sample_line_positions(position, dimension, text_dimension);
            const auto& box_left = std::get<0>(line_positions).left();
            const auto& box_top = std::get<0>(line_positions).top();
            const auto& box_right = std::get<1>(line_positions).left();
            const auto& box_bottom = std::get<1>(line_positions).top();
            const auto& line_left = std::get<2>(line_positions).left();
            const auto& line_bottom = std::get<2>(line_positions).top();
            const auto& line_right = std::get<3>(line_positions).left();
            canvas.draw_line(position_type{ line_left, box_top }, position_type{ line_right, box_top });
            canvas.draw_line(position_type{ line_left, box_bottom }, position_type{ line_right, box_bottom });
            canvas.draw_line(position_type{ box_left, box_top }, position_type{ box_left, line_bottom });
            canvas.draw_line(position_type{ box_right, box_top }, position_type{ box_right, line_bottom });
        }

        position_type timetable_sample_text_position(
            const position_type&  base_position,
            const dimension_type& base_dimension,
            const dimension_type& text_dimension) const
        {
            const auto& canvas_width = base_dimension.width();
            const auto& canvas_height = base_dimension.height();
            const auto& text_width = text_dimension.width();
            const auto& text_height = text_dimension.height();

            auto left = canvas_width > text_width ? position_unit_type::from((canvas_width - text_width) / 2) :
                                                    position_unit_type{};
            auto top = canvas_height > text_height ? position_unit_type::from((canvas_height - text_height) / 2) :
                                                     position_unit_type{};
            return position_type{ base_position.left() + left, base_position.top() + top };
        }

        std::tuple<position_type, position_type, position_type, position_type> timetable_sample_line_positions(
            const position_type&  base_position,
            const dimension_type& base_dimension,
            const dimension_type& text_dimension) const
        {
            const auto& canvas_left = base_position.left();
            const auto& canvas_top = base_position.top();
            const auto& canvas_width = base_dimension.width();
            const auto& canvas_height = base_dimension.height();

            const auto& text_width = text_dimension.width();
            const auto& text_height = text_dimension.height();

            const auto box_width = std::max(text_width + dimension_unit_type{ 1 } / 2, dimension_unit_type{ 5 } / 2);
            const auto box_height = std::max(text_height + dimension_unit_type{ 1 } / 2, dimension_unit_type{ 3 } / 2);
            const auto box_left = canvas_width > box_width ? position_unit_type::from((canvas_width - box_width) / 2) :
                                                             position_unit_type{};
            const auto box_right = box_left + position_unit_type::from(box_width);
            const auto box_top = canvas_height > box_height ?
                                     position_unit_type::from((canvas_height - box_height) / 2) :
                                     position_unit_type{};
            const auto box_bottom = box_top + position_unit_type::from(box_height);

            const auto line_left =
                box_left > position_unit_type{ 1 } / 2 ? box_left - position_unit_type{ 1 } / 2 : position_unit_type{};
            const auto line_right = box_right + position_unit_type{ 1 } / 2 < position_unit_type::from(canvas_width) ?
                                        box_right + position_unit_type{ 1 } / 2 :
                                        position_unit_type::from(canvas_width);
            const auto line_bottom = canvas_top + position_unit_type::from(canvas_height);

            return std::make_tuple(
                position_type{ canvas_left + box_left, canvas_top + box_top },
                position_type{ canvas_left + box_right, canvas_top + box_bottom },
                position_type{ canvas_left + line_left, canvas_top + line_bottom },
                position_type{ canvas_left + line_right, canvas_top + line_bottom });
        }
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
        explicit ok_button_mouse_clicked(dialog_type& dialog) : m_dialog{ dialog } {}


        // functions

        /*!
            \brief Called when the OK button is clicked.
        */
        void operator()() const
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
        explicit cancel_button_mouse_clicked(dialog_type& dialog) : m_dialog{ dialog } {}


        // functions

        /*!
            \brief Called when the cancel button is clicked.
        */
        void operator()() const
        {
            m_dialog.set_result(dialog_type::result_type::canceled);
            m_dialog.close();
        }


    private:
        // variables

        dialog_type& m_dialog;
    };
}


#endif
