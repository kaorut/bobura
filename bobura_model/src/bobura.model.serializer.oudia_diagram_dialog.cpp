/*! \file
    \brief The definition of bobura::model::serializer::oudia_diagram_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/message/oudia_diagram_dialog.h>
#include <bobura/model/serializer/oudia_diagram_dialog.h>
#include <bobura/type_list.h>


namespace bobura::model::serializer {
    template <typename Traits, typename Size>
    class oudia_diagram_dialog<Traits, Size>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = typename oudia_diagram_dialog::traits_type;

        using string_type = typename oudia_diagram_dialog::string_type;

        using base_type = typename oudia_diagram_dialog::base_type;

        using message_catalog_type = typename oudia_diagram_dialog::message_catalog_type;

        using size_type = typename oudia_diagram_dialog::size_type;


        // constructors and destructor

        impl(base_type& base, const message_catalog_type& message_catalog)
        : m_base{ base }, m_message_catalog{ message_catalog }, m_file_name{}, m_names{}, m_selected_index{},
          m_p_file_name_label{}, m_p_prompt_label{}, m_p_diagram_list_box{}, m_p_ok_button{}, m_p_cancel_button{}
        {
            initialize_dialog();
        }


        // functions

        const string_type& file_name() const
        {
            return m_file_name;
        }

        void set_file_name(string_type file_name)
        {
            m_file_name = std::move(file_name);
            if (!m_p_file_name_label->destroyed())
                m_p_file_name_label->set_text(m_file_name);
        }

        const std::vector<string_type>& names() const
        {
            return m_names;
        }

        void set_names(std::vector<string_type> names)
        {
            m_names = std::move(names);
            if (!m_p_diagram_list_box->destroyed())
            {
                m_p_diagram_list_box->clear();
                for (const auto& name : m_names)
                {
                    m_p_diagram_list_box->insert_value(m_p_diagram_list_box->value_count(), name);
                }
            }

            m_selected_index = m_p_diagram_list_box->selected_value_index();
        }

        const tetengo2::stdalt::optional<size_type>& selected_index() const
        {
            return m_selected_index;
        }

        void set_selected_index(const size_type index)
        {
            if (index >= m_p_diagram_list_box->value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is greater than the diagram count."));

            m_selected_index = tetengo2::stdalt::make_optional(size_type{ index });
            if (!m_p_diagram_list_box->destroyed())
                m_p_diagram_list_box->select_value(*m_selected_index);
        }

        void set_result_impl()
        {
            m_selected_index = m_p_diagram_list_box->selected_value_index();
        }


    private:
        // types

        using position_type = typename traits_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_type = typename traits_type::dimension_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using label_type = typename traits_type::label_type;

        using button_type = typename traits_type::button_type;

        using list_box_type = typename traits_type::list_box_type;

        using transparent_background_type = typename traits_type::transparent_background_type;

        using ok_button_mouse_clicked_type = message::oudia_diagram_dialog::ok_button_mouse_clicked<base_type>;

        using cancel_button_mouse_clicked_type = message::oudia_diagram_dialog::cancel_button_mouse_clicked<base_type>;


        // variables

        base_type& m_base;

        const message_catalog_type& m_message_catalog;

        string_type m_file_name;

        std::vector<string_type> m_names;

        tetengo2::stdalt::optional<size_type> m_selected_index;

        std::unique_ptr<label_type> m_p_file_name_label;

        std::unique_ptr<label_type> m_p_prompt_label;

        std::unique_ptr<list_box_type> m_p_diagram_list_box;

        std::unique_ptr<button_type> m_p_ok_button;

        std::unique_ptr<button_type> m_p_cancel_button;


        // functions

        void initialize_dialog()
        {
            m_base.set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:OuDiaDiagram:Diagram Selection")));

            m_p_file_name_label = create_file_name_label();
            m_p_prompt_label = create_prompt_label();
            m_p_diagram_list_box = create_diagram_list_box();
            m_p_ok_button = create_ok_button();
            m_p_cancel_button = create_cancel_button();

            locate_controls();
        }

        std::unique_ptr<label_type> create_file_name_label()
        {
            auto p_label = std::make_unique<label_type>(m_base);

            p_label->set_text(m_file_name);
            auto p_background = std::make_unique<transparent_background_type>(tetengo2::detail::gui_detail_impl_set().drawing_());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<label_type> create_prompt_label()
        {
            auto p_label = std::make_unique<label_type>(m_base);

            p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:OuDiaDiagram:&Select a diagram to load:")));
            auto p_background = std::make_unique<transparent_background_type>(tetengo2::detail::gui_detail_impl_set().drawing_());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<list_box_type> create_diagram_list_box()
        {
            auto p_list_box = std::make_unique<list_box_type>(m_base, list_box_type::scroll_bar_style_type::vertical);

            p_list_box->mouse_observer_set().doubleclicked().connect(ok_button_mouse_clicked_type{ m_base });

            return std::move(p_list_box);
        }

        std::unique_ptr<button_type> create_ok_button()
        {
            auto p_button = std::make_unique<button_type>(m_base, button_type::style_type::default_);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:OK")));
            p_button->mouse_observer_set().clicked().connect(ok_button_mouse_clicked_type{ m_base });

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_cancel_button()
        {
            auto p_button = std::make_unique<button_type>(m_base, button_type::style_type::cancel);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:Cancel")));
            p_button->mouse_observer_set().clicked().connect(cancel_button_mouse_clicked_type{ m_base });

            return std::move(p_button);
        }

        void locate_controls()
        {
            m_base.set_client_dimension(dimension_type{ dimension_unit_type{ 32 }, dimension_unit_type{ 19 } });

            const position_unit_type  label_left{ 2 };
            const dimension_unit_type control_width{ 28 };

            m_p_file_name_label->set_dimension(dimension_type{ control_width, dimension_unit_type{ 2 } });
            m_p_file_name_label->set_position(position_type{ label_left, position_unit_type{ 1 } });

            m_p_prompt_label->fit_to_content(control_width);
            m_p_prompt_label->set_position(position_type{ label_left, position_unit_type{ 3 } });

            m_p_diagram_list_box->set_dimension(dimension_type{ control_width, dimension_unit_type{ 10 } });
            m_p_diagram_list_box->set_position(
                position_type{ label_left,
                               m_p_prompt_label->position().top() +
                                   position_unit_type::from(m_p_prompt_label->dimension().height()) });

            m_p_ok_button->set_dimension(dimension_type{ dimension_unit_type{ 8 }, dimension_unit_type{ 2 } });
            m_p_ok_button->set_position(position_type{ position_unit_type{ 13 }, position_unit_type{ 16 } });

            m_p_cancel_button->set_dimension(dimension_type{ dimension_unit_type{ 8 }, dimension_unit_type{ 2 } });
            m_p_cancel_button->set_position(position_type{ position_unit_type{ 22 }, position_unit_type{ 16 } });
        }
    };


    template <typename Traits, typename Size>
    oudia_diagram_dialog<Traits, Size>::oudia_diagram_dialog(
        abstract_window_type&       parent,
        const message_catalog_type& message_catalog)
    : base_type{ parent }, m_p_impl{ std::make_unique<impl>(*this, message_catalog) }
    {}

    template <typename Traits, typename Size>
    oudia_diagram_dialog<Traits, Size>::~oudia_diagram_dialog() noexcept
    {}

    template <typename Traits, typename Size>
    const typename oudia_diagram_dialog<Traits, Size>::string_type&
    oudia_diagram_dialog<Traits, Size>::file_name() const
    {
        return m_p_impl->file_name();
    }

    template <typename Traits, typename Size>
    void oudia_diagram_dialog<Traits, Size>::set_file_name(string_type file_name)
    {
        m_p_impl->set_file_name(std::move(file_name));
    }

    template <typename Traits, typename Size>
    const std::vector<typename oudia_diagram_dialog<Traits, Size>::string_type>&
    oudia_diagram_dialog<Traits, Size>::names() const
    {
        return m_p_impl->names();
    }

    template <typename Traits, typename Size>
    void oudia_diagram_dialog<Traits, Size>::set_names(std::vector<string_type> names)
    {
        m_p_impl->set_names(std::move(names));
    }

    template <typename Traits, typename Size>
    const tetengo2::stdalt::optional<typename oudia_diagram_dialog<Traits, Size>::size_type>&
    oudia_diagram_dialog<Traits, Size>::selected_index() const
    {
        return m_p_impl->selected_index();
    }

    template <typename Traits, typename Size>
    void oudia_diagram_dialog<Traits, Size>::set_selected_index(const size_type index)
    {
        m_p_impl->set_selected_index(index);
    }

    template <typename Traits, typename Size>
    void oudia_diagram_dialog<Traits, Size>::set_result_impl()
    {
        m_p_impl->set_result_impl();
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class oudia_diagram_dialog<
        typename application::traits_type_list_type::dialog_type,
        typename application::common_type_list_type::size_type>;
#endif

    template class oudia_diagram_dialog<
        typename test::traits_type_list_type::dialog_type,
        typename test::common_type_list_type::size_type>;
}
