/*! \file
    \brief The definition of bobura::file_property_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/file_property_dialog.h>
#include <bobura/message/file_property_dialog.h>
#include <bobura/type_list.h>


namespace bobura {
    template <typename Traits>
    class file_property_dialog<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = typename file_property_dialog::traits_type;

        using string_type = typename file_property_dialog::string_type;

        using base_type = typename file_property_dialog::base_type;

        using message_catalog_type = typename file_property_dialog::message_catalog_type;

        using background_type = typename file_property_dialog::background_type;


        // constructors and destructor

        impl(base_type& base, const message_catalog_type& message_catalog)
        : m_base{ base }, m_message_catalog{ message_catalog }, m_company_name{}, m_line_name{}, m_note{},
          m_file_name{}, m_p_company_name_label{}, m_p_company_name_text_box{}, m_p_line_name_label{},
          m_p_line_name_text_box{}, m_p_note_label{}, m_p_note_text_box{}, m_p_file_name_label{},
          m_p_file_name_text_box{}, m_p_ok_button{}, m_p_cancel_button{}
        {
            initialize_dialog();
        }


        // functions

        const string_type& company_name() const
        {
            return m_company_name;
        }

        void set_company_name(string_type company_name)
        {
            m_company_name = std::move(company_name);
            if (!m_p_company_name_text_box->destroyed())
                m_p_company_name_text_box->set_text(m_company_name);
        }

        const string_type& line_name() const
        {
            return m_line_name;
        }

        void set_line_name(string_type line_name)
        {
            m_line_name = std::move(line_name);
            if (!m_p_line_name_text_box->destroyed())
                m_p_line_name_text_box->set_text(m_line_name);
        }

        const string_type& note() const
        {
            return m_note;
        }

        void set_note(string_type note)
        {
            m_note = std::move(note);
            if (!m_p_note_text_box->destroyed())
                m_p_note_text_box->set_text(m_note);
        }

        const string_type& file_name() const
        {
            return m_file_name;
        }

        void set_file_name(string_type file_name)
        {
            m_file_name = std::move(file_name);
            if (!m_p_file_name_text_box->destroyed())
                m_p_file_name_text_box->set_text(m_file_name);
        }

        void set_result_impl()
        {
            m_company_name = m_p_company_name_text_box->text();
            m_line_name = m_p_line_name_text_box->text();
            m_note = m_p_note_text_box->text();
        }


    private:
        // types

        using position_type = typename traits_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_type = typename traits_type::dimension_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using label_type = typename traits_type::label_type;

        using button_type = typename traits_type::button_type;

        using text_box_type = typename traits_type::text_box_type;

        using transparent_background_type = typename traits_type::transparent_background_type;

        using ok_button_mouse_clicked_observer_type = message::file_property_dialog::ok_button_mouse_clicked<base_type>;

        using cancel_button_mouse_clicked_observer_type =
            message::file_property_dialog::cancel_button_mouse_clicked<base_type>;


        // variables

        base_type& m_base;

        const message_catalog_type& m_message_catalog;

        string_type m_company_name;

        string_type m_line_name;

        string_type m_note;

        string_type m_file_name;

        std::unique_ptr<label_type> m_p_company_name_label;

        std::unique_ptr<text_box_type> m_p_company_name_text_box;

        std::unique_ptr<label_type> m_p_line_name_label;

        std::unique_ptr<text_box_type> m_p_line_name_text_box;

        std::unique_ptr<label_type> m_p_note_label;

        std::unique_ptr<text_box_type> m_p_note_text_box;

        std::unique_ptr<label_type> m_p_file_name_label;

        std::unique_ptr<text_box_type> m_p_file_name_text_box;

        std::unique_ptr<button_type> m_p_ok_button;

        std::unique_ptr<button_type> m_p_cancel_button;


        // functions

        void initialize_dialog()
        {
            m_base.set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FileProperty:File Property")));

            m_p_company_name_label = create_company_name_label();
            m_p_company_name_text_box = create_company_name_text_box();
            m_p_line_name_label = create_line_name_label();
            m_p_line_name_text_box = create_line_name_text_box();
            m_p_note_label = create_note_label();
            m_p_note_text_box = create_note_text_box();
            m_p_file_name_label = create_file_name_label();
            m_p_file_name_text_box = create_file_name_text_box();
            m_p_ok_button = create_ok_button();
            m_p_cancel_button = create_cancel_button();

            locate_controls();
        }

        std::unique_ptr<label_type> create_company_name_label()
        {
            auto p_label = std::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FileProperty:&Company Name:")));
            auto p_background =
                std::make_unique<transparent_background_type>(tetengo2::detail::gui_detail_impl_set().drawing_());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<text_box_type> create_company_name_text_box()
        {
            auto p_text_box = std::make_unique<text_box_type>(m_base, text_box_type::scroll_bar_style_type::none);

            return std::move(p_text_box);
        }

        std::unique_ptr<label_type> create_line_name_label()
        {
            auto p_label = std::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FileProperty:&Line Name:")));
            auto p_background =
                std::make_unique<transparent_background_type>(tetengo2::detail::gui_detail_impl_set().drawing_());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<text_box_type> create_line_name_text_box()
        {
            auto p_text_box = std::make_unique<text_box_type>(m_base, text_box_type::scroll_bar_style_type::none);

            return std::move(p_text_box);
        }

        std::unique_ptr<label_type> create_note_label()
        {
            auto p_label = std::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FileProperty:&Note:")));
            auto p_background =
                std::make_unique<transparent_background_type>(tetengo2::detail::gui_detail_impl_set().drawing_());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<text_box_type> create_note_text_box()
        {
            auto p_text_box = std::make_unique<text_box_type>(m_base, text_box_type::scroll_bar_style_type::none);

            return std::move(p_text_box);
        }

        std::unique_ptr<label_type> create_file_name_label()
        {
            auto p_label = std::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FileProperty:&File Name:")));
            auto p_background =
                std::make_unique<transparent_background_type>(tetengo2::detail::gui_detail_impl_set().drawing_());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<text_box_type> create_file_name_text_box()
        {
            auto p_text_box = std::make_unique<text_box_type>(m_base, text_box_type::scroll_bar_style_type::none);

            p_text_box->set_read_only(true);

            return std::move(p_text_box);
        }

        std::unique_ptr<button_type> create_ok_button()
        {
            auto p_button = std::make_unique<button_type>(m_base, button_type::style_type::default_);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:OK")));
            p_button->mouse_observer_set().clicked().connect(ok_button_mouse_clicked_observer_type{ m_base });

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_cancel_button()
        {
            auto p_button = std::make_unique<button_type>(m_base, button_type::style_type::cancel);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:Cancel")));
            p_button->mouse_observer_set().clicked().connect(cancel_button_mouse_clicked_observer_type{ m_base });

            return std::move(p_button);
        }

        void locate_controls()
        {
            m_base.set_client_dimension(dimension_type{ dimension_unit_type{ 36 }, dimension_unit_type{ 21 } });

            const position_unit_type label_left{ 2 };

            m_p_company_name_label->fit_to_content();
            m_p_company_name_label->set_position(position_type{ label_left, position_unit_type{ 1 } });

            m_p_company_name_text_box->set_dimension(
                dimension_type{ dimension_unit_type{ 32 }, dimension_unit_type{ 2 } });
            m_p_company_name_text_box->set_position(
                position_type{ label_left,
                               m_p_company_name_label->position().top() +
                                   position_unit_type::from(m_p_company_name_label->dimension().height()) });

            m_p_line_name_label->fit_to_content();
            m_p_line_name_label->set_position(position_type{ label_left, position_unit_type{ 5 } });

            m_p_line_name_text_box->set_dimension(
                dimension_type{ dimension_unit_type{ 32 }, dimension_unit_type{ 2 } });
            m_p_line_name_text_box->set_position(
                position_type{ label_left,
                               m_p_line_name_label->position().top() +
                                   position_unit_type::from(m_p_line_name_label->dimension().height()) });

            m_p_note_label->fit_to_content();
            m_p_note_label->set_position(position_type{ label_left, position_unit_type{ 9 } });

            m_p_note_text_box->set_dimension(dimension_type{ dimension_unit_type{ 32 }, dimension_unit_type{ 2 } });
            m_p_note_text_box->set_position(position_type{
                label_left,
                m_p_note_label->position().top() + position_unit_type::from(m_p_note_label->dimension().height()) });

            m_p_file_name_label->fit_to_content();
            m_p_file_name_label->set_position(position_type{ label_left, position_unit_type{ 13 } });

            m_p_file_name_text_box->set_dimension(
                dimension_type{ dimension_unit_type{ 32 }, dimension_unit_type{ 2 } });
            m_p_file_name_text_box->set_position(
                position_type{ label_left,
                               m_p_file_name_label->position().top() +
                                   position_unit_type::from(m_p_file_name_label->dimension().height()) });

            m_p_ok_button->set_dimension(dimension_type{ dimension_unit_type{ 8 }, dimension_unit_type{ 2 } });
            m_p_ok_button->set_position(position_type{ position_unit_type{ 17 }, position_unit_type{ 18 } });

            m_p_cancel_button->set_dimension(dimension_type{ dimension_unit_type{ 8 }, dimension_unit_type{ 2 } });
            m_p_cancel_button->set_position(position_type{ position_unit_type{ 26 }, position_unit_type{ 18 } });
        }
    };


    template <typename Traits>
    file_property_dialog<Traits>::file_property_dialog(
        abstract_window_type&       parent,
        const message_catalog_type& message_catalog)
    : base_type{ parent }, m_p_impl{ std::make_unique<impl>(*this, message_catalog) }
    {}

    template <typename Traits>
    file_property_dialog<Traits>::~file_property_dialog() noexcept
    {}

    template <typename Traits>
    const typename file_property_dialog<Traits>::string_type& file_property_dialog<Traits>::company_name() const
    {
        return m_p_impl->company_name();
    }

    template <typename Traits>
    void file_property_dialog<Traits>::set_company_name(string_type company_name)
    {
        m_p_impl->set_company_name(std::move(company_name));
    }

    template <typename Traits>
    const typename file_property_dialog<Traits>::string_type& file_property_dialog<Traits>::line_name() const
    {
        return m_p_impl->line_name();
    }

    template <typename Traits>
    void file_property_dialog<Traits>::set_line_name(string_type line_name)
    {
        m_p_impl->set_line_name(std::move(line_name));
    }

    template <typename Traits>
    const typename file_property_dialog<Traits>::string_type& file_property_dialog<Traits>::note() const
    {
        return m_p_impl->note();
    }

    template <typename Traits>
    void file_property_dialog<Traits>::set_note(string_type note)
    {
        m_p_impl->set_note(std::move(note));
    }

    template <typename Traits>
    const typename file_property_dialog<Traits>::string_type& file_property_dialog<Traits>::file_name() const
    {
        return m_p_impl->file_name();
    }

    template <typename Traits>
    void file_property_dialog<Traits>::set_file_name(string_type file_name)
    {
        m_p_impl->set_file_name(std::move(file_name));
    }

    template <typename Traits>
    void file_property_dialog<Traits>::set_result_impl()
    {
        m_p_impl->set_result_impl();
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class file_property_dialog<typename application::traits_type_list_type::dialog_type>;
#endif

    template class file_property_dialog<typename test::traits_type_list_type::dialog_type>;
}
