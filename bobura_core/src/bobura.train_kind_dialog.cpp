/*! \file
    \brief The definition of bobura::train_kind_dialog.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/format.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/rational.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/message/train_kind_dialog.h>
#include <bobura/train_kind_dialog.h>
#include <bobura/type_list.h>


namespace bobura
{
    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    class train_kind_dialog<Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::impl :
        private boost::noncopyable
    {
    public:
        // types

        using traits_type = typename train_kind_dialog::traits_type;

        using size_type = typename train_kind_dialog::size_type;

        using base_type = typename train_kind_dialog::base_type;

        using message_catalog_type = typename train_kind_dialog::message_catalog_type;

        using font_type = typename train_kind_dialog::font_type;

        using color_type = typename train_kind_dialog::color_type;

        using canvas_type = typename train_kind_dialog::canvas_type;

        using font_dialog_type = typename train_kind_dialog::font_dialog_type;

        using point_unit_size_type = typename train_kind_dialog::point_unit_size_type;

        using color_dialog_type = typename train_kind_dialog::color_dialog_type;

        using info_set_type = typename train_kind_dialog::info_set_type;


        // constructors and destructor

        impl(
            base_type&                  base,
            const color_type&           background_color,
            const color_type&           timetable_color,
            const message_catalog_type& message_catalog
        )
        :
        m_base(base),
        m_message_catalog(message_catalog),
        m_info_sets(),
        m_current_train_kind_index(),
        m_current_diagram_font(font_type::dialog_font()),
        m_current_diagram_color(0, 0, 0),
        m_current_timetable_font(font_type::dialog_font()),
        m_current_timetable_color(0, 0, 0),
        m_p_train_kind_label(),
        m_p_train_kind_list_box(),
        m_p_add_button(),
        m_p_delete_button(),
        m_p_up_button(),
        m_p_down_button(),
        m_p_name_label(),
        m_p_name_text_box(),
        m_p_abbreviation_label(),
        m_p_abbreviation_text_box(),
        m_p_diagram_label(),
        m_p_diagram_font_button(),
        m_p_diagram_font_text_box(),
        m_p_diagram_color_button(),
        m_p_diagram_weight_label(),
        m_p_diagram_weight_dropdown_box(),
        m_p_diagram_line_style_label(),
        m_p_diagram_line_style_dropdown_box(),
        m_p_timetable_label(),
        m_p_timetable_font_button(),
        m_p_timetable_font_text_box(),
        m_p_timetable_color_button(),
        m_p_sample_picture_box(),
        m_p_ok_button(),
        m_p_cancel_button()
        {
            initialize_dialog(background_color, timetable_color);
        }


        // functions

        const std::vector<info_set_type> info_sets()
        const
        {
            return m_info_sets;
        }

        void set_info_sets(std::vector<info_set_type> info_sets)
        {
            m_info_sets = std::move(info_sets);
        }

        void do_modal_impl()
        {
            sync();
        }



    private:
        // types

        using string_type = typename traits_type::string_type;

        using position_type = typename traits_type::position_type;

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        using dimension_type = typename traits_type::dimension_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;

        using label_type = typename traits_type::label_type;

        using button_type = typename traits_type::button_type;

        using text_box_type = typename traits_type::text_box_type;

        using list_box_type = typename traits_type::list_box_type;

        using dropdown_box_type = typename traits_type::dropdown_box_type;

        using picture_box_type = typename traits_type::picture_box_type;

        using transparent_background_type = typename traits_type::transparent_background_type;

        using train_kind_list_box_selection_changed_observer_type =
            message::train_kind_dialog::train_kind_list_box_selection_changed<size_type, list_box_type>;

        using add_button_mouse_clicked_observer_type =
            message::train_kind_dialog::add_button_mouse_clicked<info_set_type, size_type, message_catalog_type>;

        using delete_button_mouse_clicked_observer_type =
            message::train_kind_dialog::delete_button_mouse_clicked<info_set_type, size_type>;

        using up_button_mouse_clicked_observer_type =
            message::train_kind_dialog::up_button_mouse_clicked<info_set_type, size_type>;

        using down_button_mouse_clicked_observer_type =
            message::train_kind_dialog::down_button_mouse_clicked<info_set_type, size_type>;

        using name_text_box_changed_observer_type = message::train_kind_dialog::name_text_box_changed;

        using abbreviation_text_box_changed_observer_type = message::train_kind_dialog::abbreviation_text_box_changed;

        using diagram_font_button_mouse_clicked_observer_type =
            message::train_kind_dialog::diagram_font_button_mouse_clicked<base_type, font_dialog_type>;

        using diagram_color_button_mouse_clicked_observer_type =
            message::train_kind_dialog::diagram_color_button_mouse_clicked<base_type, color_dialog_type>;

        using diagram_weight_dropdown_box_selection_changed_observer_type =
            message::train_kind_dialog::diagram_weight_dropdown_box_selection_changed;

        using diagram_line_style_dropdown_box_selection_changed_observer_type =
            message::train_kind_dialog::diagram_line_style_dropdown_box_selection_changed;

        using timetable_font_button_mouse_clicked_observer_type =
            message::train_kind_dialog::timetable_font_button_mouse_clicked<base_type, font_dialog_type>;

        using timetable_color_button_mouse_clicked_observer_type =
            message::train_kind_dialog::timetable_color_button_mouse_clicked<base_type, color_dialog_type>;

        using sample_picture_box_paint_observer_type =
            message::train_kind_dialog::sample_picture_box_paint<info_set_type, size_type, Canvas>;

        using ok_button_mouse_clicked_observer_type = message::train_kind_dialog::ok_button_mouse_clicked<base_type>;

        using cancel_button_mouse_clicked_observer_type =
            message::train_kind_dialog::cancel_button_mouse_clicked<base_type>;

        using train_kind_type = typename info_set_type::train_kind_type;

        using weight_type = typename train_kind_type::weight_type;

        using line_style_type = typename train_kind_type::line_style_type;


        // static functions

        static size_type to_weight_dropdown_box_index(const weight_type weight)
        {
            switch (weight)
            {
            case weight_type::normal:
                return 0;
            case weight_type::bold:
                return 1;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid weight."));
            }
        }

        static weight_type to_weight(const size_type dropdown_box_index)
        {
            switch (dropdown_box_index)
            {
            case 0:
                return weight_type::normal;
            case 1:
                return weight_type::bold;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid weight dropdown box index."));
            }
        }

        static size_type to_line_style_dropdown_box_index(const line_style_type line_style)
        {
            switch (line_style)
            {
            case line_style_type::solid:
                return 0;
            case line_style_type::dashed:
                return 1;
            case line_style_type::dotted:
                return 2;
            case line_style_type::dot_dashed:
                return 3;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid line style."));
            }
        }

        static line_style_type to_line_style(const size_type dropdown_box_index)
        {
            switch (dropdown_box_index)
            {
            case 0:
                return line_style_type::solid;
            case 1:
                return line_style_type::dashed;
            case 2:
                return line_style_type::dotted;
            case 3:
                return line_style_type::dot_dashed;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid line style dropdown box index."));
            }
        }


        // variables

        base_type& m_base;

        const message_catalog_type& m_message_catalog;

        std::vector<info_set_type> m_info_sets;

        boost::optional<size_type> m_current_train_kind_index;

        font_type m_current_diagram_font;

        color_type m_current_diagram_color;

        font_type m_current_timetable_font;

        color_type m_current_timetable_color;

        std::unique_ptr<label_type> m_p_train_kind_label;

        std::unique_ptr<list_box_type> m_p_train_kind_list_box;

        std::unique_ptr<button_type> m_p_add_button;

        std::unique_ptr<button_type> m_p_delete_button;

        std::unique_ptr<button_type> m_p_up_button;

        std::unique_ptr<button_type> m_p_down_button;

        std::unique_ptr<label_type> m_p_name_label;

        std::unique_ptr<text_box_type> m_p_name_text_box;

        std::unique_ptr<label_type> m_p_abbreviation_label;

        std::unique_ptr<text_box_type> m_p_abbreviation_text_box;

        std::unique_ptr<label_type> m_p_diagram_label;

        std::unique_ptr<button_type> m_p_diagram_font_button;

        std::unique_ptr<text_box_type> m_p_diagram_font_text_box;

        std::unique_ptr<button_type> m_p_diagram_color_button;

        std::unique_ptr<label_type> m_p_diagram_weight_label;

        std::unique_ptr<dropdown_box_type> m_p_diagram_weight_dropdown_box;

        std::unique_ptr<label_type> m_p_diagram_line_style_label;

        std::unique_ptr<dropdown_box_type> m_p_diagram_line_style_dropdown_box;

        std::unique_ptr<label_type> m_p_timetable_label;

        std::unique_ptr<button_type> m_p_timetable_font_button;

        std::unique_ptr<text_box_type> m_p_timetable_font_text_box;

        std::unique_ptr<button_type> m_p_timetable_color_button;

        std::unique_ptr<label_type> m_p_sample_label;

        std::unique_ptr<picture_box_type> m_p_sample_picture_box;

        std::unique_ptr<button_type> m_p_ok_button;

        std::unique_ptr<button_type> m_p_cancel_button;


        // functions

        void initialize_dialog(const color_type& background_color, const color_type& timetable_color)
        {
            m_base.set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Train Kinds")));

            m_p_train_kind_label = create_train_kind_label();
            m_p_train_kind_list_box = create_train_kind_list_box();
            m_p_add_button = create_add_button();
            m_p_delete_button = create_delete_button();
            m_p_up_button = create_up_button();
            m_p_down_button = create_down_button();
            m_p_name_label = create_name_label();
            m_p_name_text_box = create_name_text_box();
            m_p_abbreviation_label = create_abbreviation_label();
            m_p_abbreviation_text_box = create_abbreviation_text_box();
            m_p_diagram_label = create_diagram_label();
            m_p_diagram_font_button = create_diagram_font_button();
            m_p_diagram_font_text_box = create_diagram_font_text_box();
            m_p_diagram_color_button = create_diagram_color_button();
            m_p_diagram_weight_label = create_diagram_weight_label();
            m_p_diagram_weight_dropdown_box = create_diagram_weight_dropdown_box();
            m_p_diagram_line_style_label = create_diagram_line_style_label();
            m_p_diagram_line_style_dropdown_box = create_diagram_line_style_dropdown_box();
            m_p_timetable_label = create_timetable_label();
            m_p_timetable_font_button = create_timetable_font_button();
            m_p_timetable_font_text_box = create_timetable_font_text_box();
            m_p_timetable_color_button = create_timetable_color_button();
            m_p_sample_label = create_sample_label();
            m_p_sample_picture_box = create_sample_picture_box(background_color, timetable_color);
            m_p_ok_button = create_ok_button();
            m_p_cancel_button = create_cancel_button();

            locate_controls();
        }

        std::unique_ptr<label_type> create_train_kind_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Train &Kinds:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<list_box_type> create_train_kind_list_box()
        {
            auto p_list_box =
                tetengo2::stdalt::make_unique<list_box_type>(m_base, list_box_type::scroll_bar_style_type::vertical);

            p_list_box->list_selection_observer_set().selection_changed().connect(
                train_kind_list_box_selection_changed_observer_type{
                    m_current_train_kind_index, *p_list_box, [this]() { this->update(); }
                }
            );

            return std::move(p_list_box);
        }

        std::unique_ptr<button_type> create_add_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Add")));
            p_button->mouse_observer_set().clicked().connect(
                add_button_mouse_clicked_observer_type{
                    m_info_sets, m_current_train_kind_index, [this]() { this->sync(); }, m_message_catalog
                }
            );

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_delete_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:D&elete")));
            p_button->mouse_observer_set().clicked().connect(
                delete_button_mouse_clicked_observer_type{
                    m_info_sets, m_current_train_kind_index, [this]() { this->sync(); }
                }
            );

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_up_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Up")));
            p_button->mouse_observer_set().clicked().connect(
                up_button_mouse_clicked_observer_type{
                    m_info_sets, m_current_train_kind_index, [this]() { this->sync(); }
                }
            );

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_down_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Down")));
            p_button->mouse_observer_set().clicked().connect(
                down_button_mouse_clicked_observer_type{
                    m_info_sets, m_current_train_kind_index, [this]() { this->sync(); }
                }
            );

            return std::move(p_button);
        }

        std::unique_ptr<label_type> create_name_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Name:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<text_box_type> create_name_text_box()
        {
            auto p_text_box =
                tetengo2::stdalt::make_unique<text_box_type>(m_base, list_box_type::scroll_bar_style_type::none);

            p_text_box->text_box_observer_set().changed().connect(
                name_text_box_changed_observer_type{ [this]() { this->apply(); } }
            );

            return std::move(p_text_box);
        }

        std::unique_ptr<label_type> create_abbreviation_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:A&bbreviation:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<text_box_type> create_abbreviation_text_box()
        {
            auto p_text_box =
                tetengo2::stdalt::make_unique<text_box_type>(m_base, list_box_type::scroll_bar_style_type::none);

            p_text_box->text_box_observer_set().changed().connect(
                abbreviation_text_box_changed_observer_type{ [this]() { this->apply(); } }
            );

            return std::move(p_text_box);
        }

        std::unique_ptr<label_type> create_diagram_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Diagram:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<button_type> create_diagram_font_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Font...")));
            p_button->mouse_observer_set().clicked().connect(
                diagram_font_button_mouse_clicked_observer_type{
                    m_base, m_current_diagram_font, [this]() { this->apply(); }
                }
            );

            return std::move(p_button);
        }

        std::unique_ptr<text_box_type> create_diagram_font_text_box()
        {
            auto p_text_box =
                tetengo2::stdalt::make_unique<text_box_type>(m_base, list_box_type::scroll_bar_style_type::none);

            p_text_box->set_read_only(true);

            return std::move(p_text_box);
        }

        std::unique_ptr<button_type> create_diagram_color_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Color...")));
            p_button->mouse_observer_set().clicked().connect(
                diagram_color_button_mouse_clicked_observer_type{
                    m_base, m_current_diagram_color, [this]() { this->apply(); }
                }
            );

            return std::move(p_button);
        }

        std::unique_ptr<label_type> create_diagram_weight_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Line &Weight:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<dropdown_box_type> create_diagram_weight_dropdown_box()
        {
            auto p_dropdown_box = tetengo2::stdalt::make_unique<dropdown_box_type>(m_base);

            p_dropdown_box->insert_value(
                p_dropdown_box->value_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Normal"))
            );
            p_dropdown_box->insert_value(
                p_dropdown_box->value_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Bold"))
            );
            p_dropdown_box->select_value(0);

            p_dropdown_box->list_selection_observer_set().selection_changed().connect(
                diagram_weight_dropdown_box_selection_changed_observer_type{ [this]() { this->apply(); } }
            );

            return std::move(p_dropdown_box);
        }

        std::unique_ptr<label_type> create_diagram_line_style_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Line &Style:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<dropdown_box_type> create_diagram_line_style_dropdown_box()
        {
            auto p_dropdown_box = tetengo2::stdalt::make_unique<dropdown_box_type>(m_base);

            p_dropdown_box->insert_value(
                p_dropdown_box->value_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Solid"))
            );
            p_dropdown_box->insert_value(
                p_dropdown_box->value_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Dashed"))
            );
            p_dropdown_box->insert_value(
                p_dropdown_box->value_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Dotted"))
            );
            p_dropdown_box->insert_value(
                p_dropdown_box->value_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Dot-Dashed"))
            );
            p_dropdown_box->select_value(0);

            p_dropdown_box->list_selection_observer_set().selection_changed().connect(
                diagram_line_style_dropdown_box_selection_changed_observer_type{ [this]() { this->apply(); } }
            );

            return std::move(p_dropdown_box);
        }

        std::unique_ptr<label_type> create_timetable_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Timetable:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<button_type> create_timetable_font_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:F&ont...")));
            p_button->mouse_observer_set().clicked().connect(
                timetable_font_button_mouse_clicked_observer_type{
                    m_base, m_current_timetable_font, [this]() { this->apply(); }
                }
            );

            return std::move(p_button);
        }

        std::unique_ptr<text_box_type> create_timetable_font_text_box()
        {
            auto p_text_box =
                tetengo2::stdalt::make_unique<text_box_type>(m_base, list_box_type::scroll_bar_style_type::none);

            p_text_box->set_read_only(true);

            return std::move(p_text_box);
        }

        std::unique_ptr<button_type> create_timetable_color_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Co&lor...")));
            p_button->mouse_observer_set().clicked().connect(
                timetable_color_button_mouse_clicked_observer_type{
                    m_base, m_current_timetable_color, [this]() { this->apply(); }
                }
            );

            return std::move(p_button);
        }

        std::unique_ptr<label_type> create_sample_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Sample:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<picture_box_type> create_sample_picture_box(
            const color_type& background_color,
            const color_type& timetable_color
        )
        {
            auto p_picture_box =
                tetengo2::stdalt::make_unique<picture_box_type>(m_base, list_box_type::scroll_bar_style_type::none);

            p_picture_box->set_dimension(dimension_type{ width_type{ 22 }, height_type{ 4 } });
            p_picture_box->fast_paint_observer_set().paint().connect(
                sample_picture_box_paint_observer_type{
                    m_info_sets,
                    m_current_train_kind_index,
                    background_color,
                    timetable_color,
                    p_picture_box->client_dimension()
                }
            );

            return std::move(p_picture_box);
        }

        std::unique_ptr<button_type> create_ok_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base, button_type::style_type::default_);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:OK")));
            p_button->mouse_observer_set().clicked().connect(ok_button_mouse_clicked_observer_type{ m_base });

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_cancel_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base, button_type::style_type::cancel);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:Cancel")));
            p_button->mouse_observer_set().clicked().connect(cancel_button_mouse_clicked_observer_type{ m_base });

            return std::move(p_button);
        }

        void locate_controls()
        {
            m_base.set_client_dimension(dimension_type{ width_type{ 48 }, height_type{ 37 } });

            const left_type train_kind_label_left{ 2 };
            {
                m_p_train_kind_label->fit_to_content();
                m_p_train_kind_label->set_position(position_type{ train_kind_label_left, top_type{ 1 } });

                const width_type list_box_width{ 20 };
                const height_type list_box_height{ 28 };
                m_p_train_kind_list_box->set_dimension(dimension_type{ list_box_width, list_box_height });
                m_p_train_kind_list_box->set_position(
                    position_type{
                        train_kind_label_left,
                        tetengo2::gui::position<position_type>::top(m_p_train_kind_label->position()) +
                            top_type::from(
                                tetengo2::gui::dimension<dimension_type>::height(m_p_train_kind_label->dimension())
                            )
                    }
                );

                const width_type list_box_button_width{ typename width_type::value_type{ 9, 2 } };
                left_type list_box_button_left{
                    train_kind_label_left + left_type::from(list_box_width) - left_type::from(list_box_button_width)
                };
                const top_type list_box_button_top{
                    tetengo2::gui::position<position_type>::top(m_p_train_kind_list_box->position()) +
                        top_type::from(list_box_height)
                };
                m_p_down_button->set_dimension(dimension_type{ list_box_button_width, height_type{ 2 } });
                m_p_down_button->set_position(position_type{ list_box_button_left, list_box_button_top });

                list_box_button_left -=
                    left_type::from(list_box_button_width) + left_type{ typename left_type::value_type{ 1, 4 } };
                m_p_up_button->set_dimension(dimension_type{ list_box_button_width, height_type{ 2 } });
                m_p_up_button->set_position(position_type{ list_box_button_left, list_box_button_top });

                list_box_button_left -=
                    left_type::from(list_box_button_width) + left_type{ typename left_type::value_type{ 1, 2 } };
                m_p_delete_button->set_dimension(dimension_type{ list_box_button_width, height_type{ 2 } });
                m_p_delete_button->set_position(position_type{ list_box_button_left, list_box_button_top });

                list_box_button_left -=
                    left_type::from(list_box_button_width) + left_type{ typename left_type::value_type{ 1, 4 } };
                m_p_add_button->set_dimension(dimension_type{ list_box_button_width, height_type{ 2 } });
                m_p_add_button->set_position(position_type{ list_box_button_left, list_box_button_top });
            }

            const left_type name_label_left{ 24 };
            const left_type font_button_left{ 25 };
            const left_type name_text_box_left{ 32 };
            const left_type font_text_box_left{ 34 };
            {
                m_p_name_label->fit_to_content();
                m_p_name_label->set_position(position_type{ name_label_left, top_type{ 1 } });

                m_p_name_text_box->set_dimension(dimension_type{ width_type{ 14 }, height_type{ 2 } });
                m_p_name_text_box->set_position(position_type{ name_text_box_left, top_type{ 1 } });

                m_p_abbreviation_label->fit_to_content();
                m_p_abbreviation_label->set_position(position_type{ name_label_left, top_type{ 4 } });

                m_p_abbreviation_text_box->set_dimension(dimension_type{ width_type{ 14 }, height_type{ 2 } });
                m_p_abbreviation_text_box->set_position(position_type{ name_text_box_left, top_type{ 4 } });
            }
            {
                m_p_diagram_label->fit_to_content();
                m_p_diagram_label->set_position(position_type{ name_label_left, top_type{ 7 } });

                const auto font_button_top =
                    tetengo2::gui::position<position_type>::top(m_p_diagram_label->position()) +
                    top_type::from(tetengo2::gui::dimension<dimension_type>::height(m_p_diagram_label->dimension()));

                m_p_diagram_font_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
                m_p_diagram_font_button->set_position(position_type{ font_button_left, font_button_top });

                m_p_diagram_font_text_box->set_dimension(dimension_type{ width_type{ 12 }, height_type{ 2 } });
                m_p_diagram_font_text_box->set_position(position_type{ font_text_box_left, font_button_top });

                const auto color_button_top =
                    tetengo2::gui::position<position_type>::top(m_p_diagram_font_button->position()) +
                    top_type::from(
                        tetengo2::gui::dimension<dimension_type>::height(m_p_diagram_font_button->dimension())
                    ) +
                    top_type{ 1 } / 2;

                m_p_diagram_color_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
                m_p_diagram_color_button->set_position(position_type{ font_button_left, color_button_top });

                const auto weight_label_top =
                    tetengo2::gui::position<position_type>::top(m_p_diagram_color_button->position()) +
                    top_type::from(
                        tetengo2::gui::dimension<dimension_type>::height(m_p_diagram_color_button->dimension())
                    ) +
                    top_type{ 1 } / 2;

                m_p_diagram_weight_label->fit_to_content();
                m_p_diagram_weight_label->set_position(position_type{ font_button_left, weight_label_top });

                m_p_diagram_weight_dropdown_box->set_dimension(dimension_type{ width_type{ 12 }, height_type{ 2 } });
                m_p_diagram_weight_dropdown_box->set_position(position_type{ font_text_box_left, weight_label_top });

                const auto line_style_label_top =
                    tetengo2::gui::position<position_type>::top(m_p_diagram_weight_dropdown_box->position()) +
                    top_type::from(
                        tetengo2::gui::dimension<dimension_type>::height(m_p_diagram_weight_dropdown_box->dimension())
                    ) +
                    top_type{ 1 } / 2;

                m_p_diagram_line_style_label->fit_to_content();
                m_p_diagram_line_style_label->set_position(position_type{ font_button_left, line_style_label_top });

                m_p_diagram_line_style_dropdown_box->set_dimension(
                    dimension_type{ width_type{ 12 }, height_type{ 2 } }
                );
                m_p_diagram_line_style_dropdown_box->set_position(
                    position_type{ font_text_box_left, line_style_label_top }
                );
            }
            {
                m_p_timetable_label->fit_to_content();
                m_p_timetable_label->set_position(position_type{ name_label_left, top_type{ 20 } });

                const auto font_button_top =
                    tetengo2::gui::position<position_type>::top(m_p_timetable_label->position()) +
                    top_type::from(tetengo2::gui::dimension<dimension_type>::height(m_p_timetable_label->dimension()));

                m_p_timetable_font_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
                m_p_timetable_font_button->set_position(position_type{ font_button_left, font_button_top });

                m_p_timetable_font_text_box->set_dimension(dimension_type{ width_type{ 12 }, height_type{ 2 } });
                m_p_timetable_font_text_box->set_position(position_type{ font_text_box_left, font_button_top });

                const auto color_button_top =
                    tetengo2::gui::position<position_type>::top(m_p_timetable_font_button->position()) +
                    top_type::from(
                        tetengo2::gui::dimension<dimension_type>::height(m_p_timetable_font_button->dimension())
                    ) +
                    top_type{ 1 } / 2;

                m_p_timetable_color_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
                m_p_timetable_color_button->set_position(position_type{ font_button_left, color_button_top });
            }
            {
                m_p_sample_label->fit_to_content();
                m_p_sample_label->set_dimension(
                    dimension_type{
                        std::max(
                            tetengo2::gui::dimension<dimension_type>::width(m_p_sample_label->dimension()),
                            width_type{ m_p_sample_label->text().length() }
                        ),
                        tetengo2::gui::dimension<dimension_type>::height(m_p_sample_label->dimension())
                    }
                );
                m_p_sample_label->set_position(position_type{ name_label_left, top_type{ 27 } });

                m_p_sample_picture_box->set_position(
                    position_type{
                        name_label_left,
                        tetengo2::gui::position<position_type>::top(m_p_sample_label->position()) +
                            top_type::from(
                                tetengo2::gui::dimension<dimension_type>::height(m_p_sample_label->dimension())
                            )
                    }
                );
            }
            {
                m_p_ok_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
                m_p_ok_button->set_position(position_type{ left_type{ 29 }, top_type{ 34 } });

                m_p_cancel_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
                m_p_cancel_button->set_position(position_type{ left_type{ 38 }, top_type{ 34 } });
            }
        }

        void sync()
        {
            m_p_train_kind_list_box->clear();
            for (auto i = m_info_sets.begin(); i != m_info_sets.end(); ++i)
            {
                m_p_train_kind_list_box->insert_value(
                    m_p_train_kind_list_box->value_count(), i->train_kind().name()
                );
            }

            if (m_p_train_kind_list_box->value_count() > 0)
            {
                if (!m_current_train_kind_index)
                    m_current_train_kind_index = boost::make_optional<size_type>(0);
                m_p_train_kind_list_box->select_value(*m_current_train_kind_index);
            }
            update();
        }

        void update()
        {
            assert(m_p_train_kind_list_box->value_count() == m_info_sets.size());

            const auto& selected_index = m_p_train_kind_list_box->selected_value_index();
            assert(selected_index == m_current_train_kind_index);

            m_p_delete_button->set_enabled(selected_index && !m_info_sets[*selected_index].referred());
            m_p_up_button->set_enabled(selected_index && *selected_index > 0);
            m_p_down_button->set_enabled(
                selected_index && *selected_index + 1 < m_p_train_kind_list_box->value_count()
            );

            m_p_name_label->set_enabled(static_cast<bool>(selected_index));
            m_p_name_text_box->set_enabled(static_cast<bool>(selected_index));
            m_p_abbreviation_label->set_enabled(static_cast<bool>(selected_index));
            m_p_abbreviation_text_box->set_enabled(static_cast<bool>(selected_index));
            m_p_diagram_font_button->set_enabled(static_cast<bool>(selected_index));
            m_p_diagram_color_button->set_enabled(static_cast<bool>(selected_index));
            m_p_diagram_weight_label->set_enabled(static_cast<bool>(selected_index));
            m_p_diagram_weight_dropdown_box->set_enabled(static_cast<bool>(selected_index));
            m_p_diagram_line_style_label->set_enabled(static_cast<bool>(selected_index));
            m_p_diagram_line_style_dropdown_box->set_enabled(static_cast<bool>(selected_index));
            m_p_timetable_font_button->set_enabled(static_cast<bool>(selected_index));
            m_p_timetable_color_button->set_enabled(static_cast<bool>(selected_index));

            if (static_cast<bool>(selected_index))
            {
                assert(m_info_sets.size() == m_p_train_kind_list_box->value_count());
                const auto& train_kind = m_info_sets[*selected_index].train_kind();

                m_current_diagram_font = train_kind.diagram_font();
                m_current_diagram_color = train_kind.diagram_color();
                m_current_timetable_font = train_kind.timetable_font();
                m_current_timetable_color = train_kind.timetable_color();
                m_p_name_text_box->set_text(train_kind.name());
                m_p_abbreviation_text_box->set_text(train_kind.abbreviation());
                m_p_diagram_font_text_box->set_text(font_name_and_size(m_current_diagram_font));
                m_p_diagram_weight_dropdown_box->select_value(
                    to_weight_dropdown_box_index(train_kind.diagram_line_weight())
                );
                m_p_diagram_line_style_dropdown_box->select_value(
                    to_line_style_dropdown_box_index(train_kind.diagram_line_style())
                );
                m_p_timetable_font_text_box->set_text(font_name_and_size(m_current_timetable_font));
            }
            else
            {
                m_current_diagram_font = font_type::dialog_font();
                m_current_diagram_color = color_type{ 0, 0, 0 };
                m_current_timetable_font = font_type::dialog_font();
                m_current_timetable_color = color_type{ 0, 0, 0 };
                m_p_name_text_box->set_text(string_type{});
                m_p_abbreviation_text_box->set_text(string_type{});
                m_p_diagram_font_text_box->set_text(string_type{});
                m_p_diagram_weight_dropdown_box->select_value(0);
                m_p_diagram_line_style_dropdown_box->select_value(0);
                m_p_timetable_font_text_box->set_text(string_type{});
            }

            m_p_sample_picture_box->repaint();
        }

        void apply()
        {
            if (!m_current_train_kind_index)
                return;

            auto& train_kind = m_info_sets[*m_current_train_kind_index].train_kind();

            assert(m_p_diagram_weight_dropdown_box->selected_value_index());
            train_kind =
                train_kind_type{
                    m_p_name_text_box->text(),
                    m_p_abbreviation_text_box->text(),
                    m_current_diagram_font,
                    m_current_diagram_color,
                    to_weight(*m_p_diagram_weight_dropdown_box->selected_value_index()),
                    to_line_style(*m_p_diagram_line_style_dropdown_box->selected_value_index()),
                    m_current_timetable_font,
                    m_current_timetable_color
                };

            m_p_train_kind_list_box->set_value(*m_current_train_kind_index, train_kind.name());
            m_p_train_kind_list_box->select_value(*m_current_train_kind_index);

            m_p_diagram_font_text_box->set_text(font_name_and_size(m_current_diagram_font));
            m_p_timetable_font_text_box->set_text(font_name_and_size(m_current_timetable_font));
            m_p_sample_picture_box->repaint();
        }

        string_type font_name_and_size(const font_type& font)
        const
        {
            std::basic_ostringstream<typename string_type::value_type> stream;
            stream <<
                boost::basic_format<typename string_type::value_type>(string_type{ TETENGO2_TEXT("%s, %dpt") }) %
                font.family() %
                boost::rational_cast<int>(point_unit_size_type::from_pixels(font.size()).value());

            return stream.str();
        }


    };


    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::info_set_type::info_set_type(
        boost::optional<size_type> original_index,
        const bool                 referred,
        train_kind_type            train_kind
    )
    :
    m_original_index(std::move(original_index)),
    m_referred(referred),
    m_train_kind(std::move(train_kind))
    {}


    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const boost::optional<
        typename train_kind_dialog<
            Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
        >::size_type
    >&
    train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::info_set_type::original_index()
    const
    {
        return m_original_index;
    }

    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    bool train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::info_set_type::referred()
    const
    {
        return m_referred;
    }

    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const typename train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::info_set_type::train_kind_type&
    train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::info_set_type::train_kind()
    const
    {
        return m_train_kind;
    }

    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    typename train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::info_set_type::train_kind_type&
    train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::info_set_type::train_kind()
    {
        return m_train_kind;
    }

    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::train_kind_dialog(
        abstract_window_type&       parent,
        const color_type&           background_color,
        const color_type&           timetable_color,
        const message_catalog_type& message_catalog
    )
    :
    base_type(parent),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(*this, background_color, timetable_color, message_catalog))
    {}

    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::~train_kind_dialog()
    noexcept
    {}
    
    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const std::vector<
        typename train_kind_dialog<
            Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
        >::info_set_type
    >
    train_kind_dialog<Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::info_sets()
    const
    {
        return m_p_impl->info_sets();
    }

    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::set_info_sets(
        std::vector<info_set_type> info_sets
    )
    {
        m_p_impl->set_info_sets(std::move(info_sets));
    }

    template <
        typename Traits,
        typename Size,
        typename String,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void train_kind_dialog<
        Traits, Size, String, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::do_modal_impl()
    {
        m_p_impl->do_modal_impl();
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using common_dialog_type_list_type = type_list::common_dialog<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using common_dialog_type_list_type = type_list::common_dialog<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class train_kind_dialog<
        typename application::traits_type_list_type::dialog_type,
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::string_type,
        typename application::ui_type_list_type::fast_font_type,
        typename application::ui_type_list_type::point_unit_size_type,
        typename application::ui_type_list_type::color_type,
        typename application::ui_type_list_type::fast_canvas_type,
        typename application::common_dialog_type_list_type::font_type,
        typename application::common_dialog_type_list_type::color_type
    >;
#endif

    template class train_kind_dialog<
        typename test::traits_type_list_type::dialog_type,
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::string_type,
        typename test::ui_type_list_type::font_type,
        typename test::ui_type_list_type::point_unit_size_type,
        typename test::ui_type_list_type::color_type,
        typename test::ui_type_list_type::fast_canvas_type,
        typename test::common_dialog_type_list_type::font_type,
        typename test::common_dialog_type_list_type::color_type
    >;


}
