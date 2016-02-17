/*! \file
    \brief The definition of bobura::font_color_dialog.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/format.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/rational.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/font_color_dialog.h>
#include <bobura/message/font_color_dialog.h>
#include <bobura/type_list.h>


namespace bobura
{
    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    class font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::impl :
        private boost::noncopyable
    {
    public:
        // types

        using traits_type = typename font_color_dialog::traits_type;

        using size_type = typename font_color_dialog::size_type;

        using base_type = typename font_color_dialog::base_type;

        using message_catalog_type = typename font_color_dialog::message_catalog_type;

        using font_type = typename font_color_dialog::font_type;

        using point_unit_size_type = typename font_color_dialog::point_unit_size_type;

        using color_type = typename font_color_dialog::color_type;

        using canvas_type = typename font_color_dialog::canvas_type;

        using font_dialog_type = typename font_color_dialog::font_dialog_type;

        using color_dialog_type = typename font_color_dialog::color_dialog_type;

        using font_color_type = typename font_color_dialog::font_color_type;


        // constructors and destructor

        impl(base_type& base, const message_catalog_type& message_catalog)
        :
        m_base(base),
        m_font_color_list(9, font_color_type{}),
        m_message_catalog(message_catalog),
        m_current_category_index(),
        m_p_category_label(),
        m_p_category_list_box(),
        m_p_diagram_label(),
        m_p_diagram_font_button(),
        m_p_diagram_font_text_box(),
        m_p_diagram_color_button(),
        m_p_timetable_label(),
        m_p_timetable_font_button(),
        m_p_timetable_font_text_box(),
        m_p_timetable_color_button(),
        m_p_sample_label(),
        m_p_sample_picture_box(),
        m_p_ok_button(),
        m_p_cancel_button()
        {
            initialize_dialog();
        }


        // functions

        const font_color_type& background()
        const
        {
            return m_font_color_list[0];
        }

        void set_background(font_color_type font_color)
        {
            m_font_color_list[0] = std::move(font_color);
        }

        const font_color_type& company_name()
        const
        {
            return m_font_color_list[1];
        }

        void set_company_name(font_color_type font_color)
        {
            m_font_color_list[1] = std::move(font_color);
        }

        const font_color_type& line_name()
        const
        {
            return m_font_color_list[2];
        }

        void set_line_name(font_color_type font_color)
        {
            m_font_color_list[2] = std::move(font_color);
        }

        const font_color_type& note()
        const
        {
            return m_font_color_list[3];
        }

        void set_note(font_color_type font_color)
        {
            m_font_color_list[3] = std::move(font_color);
        }

        const font_color_type& time_line()
        const
        {
            return m_font_color_list[4];
        }

        void set_time_line(font_color_type font_color)
        {
            m_font_color_list[4] = std::move(font_color);
        }

        const font_color_type& local_station()
        const
        {
            return m_font_color_list[5];
        }

        void set_local_station(font_color_type font_color)
        {
            m_font_color_list[5] = std::move(font_color);
        }

        const font_color_type& principal_station()
        const
        {
            return m_font_color_list[6];
        }

        void set_principal_station(font_color_type font_color)
        {
            m_font_color_list[6] = std::move(font_color);
        }

        const font_color_type& local_terminal_station()
        const
        {
            return m_font_color_list[7];
        }

        void set_local_terminal_station(font_color_type font_color)
        {
            m_font_color_list[7] = std::move(font_color);
        }

        const font_color_type& principal_terminal_station()
        const
        {
            return m_font_color_list[8];
        }

        void set_principal_terminal_station(font_color_type font_color)
        {
            m_font_color_list[8] = std::move(font_color);
        }

        void do_modal_impl()
        {
            m_p_category_list_box->select_value(0);
            m_current_category_index = boost::make_optional<size_type>(0);
            update();
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

        using picture_box_type = typename traits_type::picture_box_type;

        using transparent_background_type = typename traits_type::transparent_background_type;

        using category_list_box_selection_changed_observer_type =
            message::font_color_dialog::category_list_box_selection_changed<size_type, list_box_type>;

        using sample_picture_box_paint_observer_type =
            message::font_color_dialog::sample_picture_box_paint<
                size_type, canvas_type, font_color_type, message_catalog_type
            >;

        using diagram_font_button_mouse_clicked_observer_type =
            message::font_color_dialog::diagram_font_button_mouse_clicked<
                size_type, base_type, FontDialog, canvas_type, font_color_type, message_catalog_type
            >;

        using diagram_color_button_mouse_clicked_observer_type =
            message::font_color_dialog::diagram_color_button_mouse_clicked<
                size_type, base_type, ColorDialog, canvas_type, font_color_type, message_catalog_type
            >;

        using timetable_font_button_mouse_clicked_observer_type =
            message::font_color_dialog::timetable_font_button_mouse_clicked<
                size_type, base_type, FontDialog, canvas_type, font_color_type, message_catalog_type
            >;

        using timetable_color_button_mouse_clicked_observer_type =
            message::font_color_dialog::timetable_color_button_mouse_clicked<
                size_type, base_type, ColorDialog, canvas_type, font_color_type, message_catalog_type
            >;

        using ok_button_mouse_clicked_observer_type = message::font_color_dialog::ok_button_mouse_clicked<base_type>;

        using cancel_button_mouse_clicked_observer_type =
            message::font_color_dialog::cancel_button_mouse_clicked<base_type>;


        // variables

        base_type& m_base;

        std::vector<font_color_type> m_font_color_list;

        const message_catalog_type& m_message_catalog;

        boost::optional<size_type> m_current_category_index;

        std::unique_ptr<label_type> m_p_category_label;

        std::unique_ptr<list_box_type> m_p_category_list_box;

        std::unique_ptr<label_type> m_p_diagram_label;

        std::unique_ptr<button_type> m_p_diagram_font_button;

        std::unique_ptr<text_box_type> m_p_diagram_font_text_box;

        std::unique_ptr<button_type> m_p_diagram_color_button;

        std::unique_ptr<label_type> m_p_timetable_label;

        std::unique_ptr<button_type> m_p_timetable_font_button;

        std::unique_ptr<text_box_type> m_p_timetable_font_text_box;

        std::unique_ptr<button_type> m_p_timetable_color_button;

        std::unique_ptr<label_type> m_p_sample_label;

        std::unique_ptr<picture_box_type> m_p_sample_picture_box;

        std::unique_ptr<button_type> m_p_ok_button;

        std::unique_ptr<button_type> m_p_cancel_button;


        // functions

        void initialize_dialog()
        {
            m_base.set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Fonts And Colors")));

            m_p_category_label = create_category_label();
            m_p_category_list_box = create_category_list_box();
            m_p_diagram_label = create_diagram_label();
            m_p_diagram_font_button = create_diagram_font_button();
            m_p_diagram_font_text_box = create_diagram_font_text_box();
            m_p_diagram_color_button = create_diagram_color_button();
            m_p_timetable_label = create_timetable_label();
            m_p_timetable_font_button = create_timetable_font_button();
            m_p_timetable_font_text_box = create_timetable_font_text_box();
            m_p_timetable_color_button = create_timetable_color_button();
            m_p_sample_label = create_sample_label();
            m_p_sample_picture_box = create_sample_picture_box();
            m_p_ok_button = create_ok_button();
            m_p_cancel_button = create_cancel_button();

            locate_controls();

            insert_category_list_box_values();
        }

        std::unique_ptr<label_type> create_category_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:C&ategories:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<list_box_type> create_category_list_box()
        {
            auto p_list_box =
                tetengo2::stdalt::make_unique<list_box_type>(m_base, list_box_type::scroll_bar_style_type::vertical);

            p_list_box->list_selection_observer_set().selection_changed().connect(
                category_list_box_selection_changed_observer_type{
                    m_current_category_index, *p_list_box, [this]() { this->update(); }
                }
            );

            return std::move(p_list_box);
        }

        std::unique_ptr<label_type> create_diagram_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Diagram:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<button_type> create_diagram_font_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base, button_type::style_type::normal);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:&Font...")));
            p_button->mouse_observer_set().clicked().connect(
                diagram_font_button_mouse_clicked_observer_type{
                    m_base,
                    m_font_color_list,
                    m_current_category_index,
                    [this]() { this->update(); },
                    m_message_catalog
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
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base, button_type::style_type::normal);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:&Color...")));
            p_button->mouse_observer_set().clicked().connect(
                diagram_color_button_mouse_clicked_observer_type{
                    m_base,
                    m_font_color_list,
                    m_current_category_index,
                    [this]() { this->update(); },
                    m_message_catalog
                }
            );

            return std::move(p_button);
        }

        std::unique_ptr<label_type> create_timetable_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Timetable:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<button_type> create_timetable_font_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base, button_type::style_type::normal);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:&Font...")));
            p_button->mouse_observer_set().clicked().connect(
                timetable_font_button_mouse_clicked_observer_type{
                    m_base,
                    m_font_color_list,
                    m_current_category_index,
                    [this]() { this->update(); },
                    m_message_catalog
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
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base, button_type::style_type::normal);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:&Color...")));
            p_button->mouse_observer_set().clicked().connect(
                timetable_color_button_mouse_clicked_observer_type{
                    m_base,
                    m_font_color_list,
                    m_current_category_index,
                    [this]() { this->update(); },
                    m_message_catalog
                }
            );

            return std::move(p_button);
        }

        std::unique_ptr<label_type> create_sample_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Sample:")));
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<picture_box_type> create_sample_picture_box()
        {
            auto p_picture_box =
                tetengo2::stdalt::make_unique<picture_box_type>(
                    m_base, list_box_type::scroll_bar_style_type::none
                );

            p_picture_box->set_dimension(dimension_type{ width_type{ 25 }, height_type{ 8 } });
            p_picture_box->fast_paint_observer_set().paint().connect(
                sample_picture_box_paint_observer_type{
                    m_font_color_list,
                    m_current_category_index,
                    p_picture_box->client_dimension(),
                    m_message_catalog
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
            m_base.set_client_dimension(dimension_type{ width_type{ 47 }, height_type{ 29 } });

            const left_type category_label_left{ 2 };

            m_p_category_label->fit_to_content();
            m_p_category_label->set_position(position_type{ category_label_left, top_type{ 1 } });

            m_p_category_list_box->set_dimension(dimension_type{ width_type{ 16 }, height_type{ 16 } });
            m_p_category_list_box->set_position(
                position_type{
                    category_label_left,
                    tetengo2::gui::position<position_type>::top(m_p_category_label->position()) +
                    top_type::from(
                        tetengo2::gui::dimension<dimension_type>::height(m_p_category_label->dimension())
                    )
                }
            );

            const left_type diagram_label_left{ 20 };
            const auto diagram_font_button_left = diagram_label_left + left_type{ 1 };
            
            m_p_diagram_label->fit_to_content();
            m_p_diagram_label->set_position(position_type{ diagram_label_left, top_type{ 1 } });

            m_p_diagram_font_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
            m_p_diagram_font_button->set_position(position_type{ diagram_font_button_left, top_type{ 3 } });

            m_p_diagram_font_text_box->set_dimension(dimension_type{ width_type{ 16 }, height_type{ 2 } });
            m_p_diagram_font_text_box->set_position(
                position_type{ diagram_font_button_left + left_type{ 8 }, top_type{ 3 } }
            );

            m_p_diagram_color_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
            m_p_diagram_color_button->set_position(position_type{ diagram_font_button_left, top_type{ 5 } });

            m_p_timetable_label->fit_to_content();
            m_p_timetable_label->set_position(position_type{ diagram_label_left, top_type{ 8 } });

            m_p_timetable_font_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
            m_p_timetable_font_button->set_position(position_type{ diagram_font_button_left, top_type{ 10 } });

            m_p_timetable_font_text_box->set_dimension(dimension_type{ width_type{ 16 }, height_type{ 2 } });
            m_p_timetable_font_text_box->set_position(
                position_type{ diagram_font_button_left + left_type{ 8 }, top_type{ 10 } }
            );

            m_p_timetable_color_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
            m_p_timetable_color_button->set_position(position_type{ diagram_font_button_left, top_type{ 12 } });

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
            m_p_sample_label->set_position(position_type{ diagram_label_left, top_type{ 15 } });

            m_p_sample_picture_box->set_position(
                position_type{
                    diagram_label_left,
                    tetengo2::gui::position<position_type>::top(m_p_sample_label->position()) +
                    top_type::from(
                        tetengo2::gui::dimension<dimension_type>::height(m_p_sample_label->dimension())
                    )
                }
            );

            m_p_ok_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
            m_p_ok_button->set_position(position_type{ left_type{ 27 }, top_type{ 26 } });

            m_p_cancel_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
            m_p_cancel_button->set_position(position_type{ left_type{ 36 }, top_type{ 26 } });
        }

        void insert_category_list_box_values()
        {
            m_p_category_list_box->insert_value(
                m_p_category_list_box->value_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Background"))
            );
            m_p_category_list_box->insert_value(
                m_p_category_list_box->value_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Company Name"))
            );
            m_p_category_list_box->insert_value(
                m_p_category_list_box->value_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Line Name"))
            );
            m_p_category_list_box->insert_value(
                m_p_category_list_box->value_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Note"))
            );
            m_p_category_list_box->insert_value(
                m_p_category_list_box->value_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Time Lines"))
            );
            m_p_category_list_box->insert_value(
                m_p_category_list_box->value_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Local Stations"))
            );
            m_p_category_list_box->insert_value(
                m_p_category_list_box->value_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Principal Stations"))
            );
            m_p_category_list_box->insert_value(
                m_p_category_list_box->value_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Local Terminal Stations"))
            );
            m_p_category_list_box->insert_value(
                m_p_category_list_box->value_count(),
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Principal Terminal Stations"))
            );

            assert(m_p_category_list_box->value_count() == m_font_color_list.size());
        }

        void update()
        {
            {
                const auto font_name_and_size_ = diagram_font_name_and_size();
                m_p_diagram_font_text_box->set_text(font_name_and_size_);
                m_p_diagram_font_text_box->set_enabled(!font_name_and_size_.empty());
                m_p_diagram_font_button->set_enabled(!font_name_and_size_.empty());

                m_p_diagram_color_button->set_enabled(diagram_color_enabled());
            }
            {
                const auto font_name_and_size_ = timetable_font_name_and_size();
                m_p_timetable_font_text_box->set_text(font_name_and_size_);
                m_p_timetable_font_text_box->set_enabled(!font_name_and_size_.empty());
                m_p_timetable_font_button->set_enabled(!font_name_and_size_.empty());

                m_p_timetable_color_button->set_enabled(timetable_color_enabled());
            }

            m_p_sample_picture_box->repaint();
        }

        string_type diagram_font_name_and_size()
        const
        {
            if (!m_current_category_index)
                return {};

            return font_name_and_size(m_font_color_list[*m_current_category_index].diagram_font());
        }

        string_type timetable_font_name_and_size()
        const
        {
            if (!m_current_category_index)
                return {};

            return font_name_and_size(m_font_color_list[*m_current_category_index].timetable_font());
        }

        string_type font_name_and_size(const boost::optional<font_type>& font)
        const
        {
            if (!font)
                return {};

            std::basic_ostringstream<typename string_type::value_type> stream;
            stream <<
                boost::basic_format<typename string_type::value_type>(string_type{ TETENGO2_TEXT("%s, %dpt") }) %
                font->family() %
                boost::rational_cast<int>(point_unit_size_type::from_pixels(font->size()).value());

            return stream.str();
        }

        bool diagram_color_enabled()
        const
        {
            return m_current_category_index && m_font_color_list[*m_current_category_index].diagram_color();
        }

        bool timetable_color_enabled()
        const
        {
            return m_current_category_index && m_font_color_list[*m_current_category_index].timetable_color();
        }


    };


    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::font_color_dialog(
        abstract_window_type&       parent,
        const message_catalog_type& message_catalog
    )
    :
    base_type(parent),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(*this, message_catalog))
    {}

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::~font_color_dialog()
    noexcept
    {}

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const typename font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::font_color_type&
    font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::background()
    const
    {
        return m_p_impl->background();
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::set_background(
        font_color_type font_color
    )
    {
        m_p_impl->set_background(std::move(font_color));
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const typename font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::font_color_type&
    font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::company_name()
    const
    {
        return m_p_impl->company_name();
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::set_company_name(font_color_type font_color)
    {
        m_p_impl->set_company_name(std::move(font_color));
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const typename font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::font_color_type&
    font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::line_name()
    const
    {
        return m_p_impl->line_name();
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::set_line_name(font_color_type font_color)
    {
        m_p_impl->set_line_name(std::move(font_color));
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const typename font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::font_color_type&
    font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::note()
    const
    {
        return m_p_impl->note();
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::set_note(
        font_color_type font_color
    )
    {
        m_p_impl->set_note(std::move(font_color));
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const typename font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::font_color_type&
    font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::time_line()
    const
    {
        return m_p_impl->time_line();
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::set_time_line(
        font_color_type font_color
    )
    {
        m_p_impl->set_time_line(std::move(font_color));
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const typename font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::font_color_type&
    font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::local_station()
    const
    {
        return m_p_impl->local_station();
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::set_local_station(
        font_color_type font_color
    )
    {
        m_p_impl->set_local_station(std::move(font_color));
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const typename font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::font_color_type&
    font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::principal_station()
    const
    {
        return m_p_impl->principal_station();
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::set_principal_station(
        font_color_type font_color
    )
    {
        m_p_impl->set_principal_station(std::move(font_color));
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const typename font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::font_color_type&
    font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::local_terminal_station()
    const
    {
        return m_p_impl->local_terminal_station();
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::set_local_terminal_station(
        font_color_type font_color
    )
    {
        m_p_impl->set_local_terminal_station(std::move(font_color));
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    const typename font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::font_color_type&
    font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::principal_terminal_station()
    const
    {
        return m_p_impl->principal_terminal_station();
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void font_color_dialog<
        Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog
    >::set_principal_terminal_station(
        font_color_type font_color
    )
    {
        m_p_impl->set_principal_terminal_station(std::move(font_color));
    }

    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    void font_color_dialog<Traits, Size, Font, PointUnitSize, Color, Canvas, FontDialog, ColorDialog>::do_modal_impl()
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
    template class font_color_dialog<
        typename application::traits_type_list_type::dialog_type,
        typename application::common_type_list_type::size_type,
        typename application::ui_type_list_type::fast_font_type,
        typename application::ui_type_list_type::point_unit_size_type,
        typename application::ui_type_list_type::color_type,
        typename application::ui_type_list_type::fast_canvas_type,
        typename application::common_dialog_type_list_type::font_type,
        typename application::common_dialog_type_list_type::color_type
    >;
#endif

    template class font_color_dialog<
        typename test::traits_type_list_type::dialog_type,
        typename test::common_type_list_type::size_type,
        typename test::ui_type_list_type::font_type,
        typename test::ui_type_list_type::point_unit_size_type,
        typename test::ui_type_list_type::color_type,
        typename test::ui_type_list_type::fast_canvas_type,
        typename test::common_dialog_type_list_type::font_type,
        typename test::common_dialog_type_list_type::color_type
    >;


}
