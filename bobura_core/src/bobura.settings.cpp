/*! \file
    \brief The definition of bobura::settings.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/predef.h>
#include <boost/program_options.hpp>
#include <boost/variant.hpp>

#include <tetengo2/config/cached_config.h>
#include <tetengo2/config/config_base.h>
#include <tetengo2/config/config_list.h>
#include <tetengo2/config/persistent_config.h>
#include <tetengo2/config/temporary_config.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/type_list.h>

#include <bobura/detail_type_list.h>
#include <bobura/settings.h>
#include <bobura/type_list.h>


namespace bobura {
    template <typename String, typename Position, typename Dimension>
    class settings<String, Position, Dimension>::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = String;

        using position_type = Position;

        using position_unit_type = typename position_type::unit_type;

        using dimension_type = Dimension;

        using dimension_unit_type = typename dimension_type::unit_type;


        // constructors and destructor

        impl(const std::vector<string_type>& command_line_arguments, string_type config_group_name)
        : m_base_path{}, m_input{}, m_p_config{}
        {
            initialize(command_line_arguments, std::move(config_group_name));
        }


        // functions

        const tetengo2::stdalt::filesystem::path& base_path() const
        {
            return m_base_path;
        }

        const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& input() const
        {
            return m_input;
        }

        tetengo2::stdalt::filesystem::path message_directory_path() const
        {
            return m_base_path / path_string_type{ TETENGO2_TEXT("messages") };
        }

        tetengo2::stdalt::filesystem::path image_directory_path() const
        {
            return m_base_path / path_string_type{ TETENGO2_TEXT("images") };
        }

        tetengo2::stdalt::optional<dimension_type> main_window_dimension() const
        {
            const auto width = m_p_config->get(string_type{ TETENGO2_TEXT("MainWindow/Width") });
            if (!width || tetengo2::stdalt::index(*width) != 1)
                return TETENGO2_STDALT_NULLOPT;
            const auto height = m_p_config->get(string_type{ TETENGO2_TEXT("MainWindow/Height") });
            if (!height || tetengo2::stdalt::index(*height) != 1)
                return TETENGO2_STDALT_NULLOPT;

            return tetengo2::stdalt::make_optional(
                dimension_type{ dimension_unit_type::from_pixels(tetengo2::stdalt::get<uint_type>(*width)),
                                dimension_unit_type::from_pixels(tetengo2::stdalt::get<uint_type>(*height)) });
        }

        void set_main_window_dimension(const dimension_type& dimension)
        {
            const auto& width = dimension.width();
            m_p_config->set(string_type{ TETENGO2_TEXT("MainWindow/Width") }, config_value_type{ width.to_pixels() });

            const auto& height = dimension.height();
            m_p_config->set(string_type{ TETENGO2_TEXT("MainWindow/Height") }, config_value_type{ height.to_pixels() });
        }

        tetengo2::stdalt::optional<bool> main_window_maximized() const
        {
            const auto status = m_p_config->get(string_type{ TETENGO2_TEXT("MainWindow/Maximized") });
            if (!status || tetengo2::stdalt::index(*status) != 1)
                return TETENGO2_STDALT_NULLOPT;

            return tetengo2::stdalt::make_optional(tetengo2::stdalt::get<uint_type>(*status) != 0);
        }

        void set_main_window_maximized(const bool status)
        {
            m_p_config->set(string_type{ TETENGO2_TEXT("MainWindow/Maximized") }, config_value_type{ status ? 1 : 0 });
        }

        tetengo2::stdalt::optional<dimension_unit_type> property_bar_width() const
        {
            const auto width = m_p_config->get(string_type{ TETENGO2_TEXT("MainWindow/PropertyBarWidth") });
            if (!width || tetengo2::stdalt::index(*width) != 1)
                return TETENGO2_STDALT_NULLOPT;

            return tetengo2::stdalt::make_optional(
                dimension_unit_type::from_pixels(tetengo2::stdalt::get<uint_type>(*width)));
        }

        void set_property_bar_width(const dimension_unit_type& width)
        {
            m_p_config->set(
                string_type{ TETENGO2_TEXT("MainWindow/PropertyBarWidth") }, config_value_type{ width.to_pixels() });
        }

        tetengo2::stdalt::optional<bool> property_bar_minimized() const
        {
            const auto status = m_p_config->get(string_type{ TETENGO2_TEXT("MainWindow/PropertyBarMinimized") });
            if (!status || tetengo2::stdalt::index(*status) != 1)
                return TETENGO2_STDALT_NULLOPT;

            return tetengo2::stdalt::make_optional(tetengo2::stdalt::get<uint_type>(*status) != 0);
        }

        void set_property_bar_minimized(const bool status)
        {
            m_p_config->set(
                string_type{ TETENGO2_TEXT("MainWindow/PropertyBarMinimized") }, config_value_type{ status ? 1 : 0 });
        }

        tetengo2::stdalt::optional<position_unit_type> property_bar_splitter_position() const
        {
            const auto position =
                m_p_config->get(string_type{ TETENGO2_TEXT("MainWindow/PropertyBarSplitterPosition") });
            if (!position || tetengo2::stdalt::index(*position) != 1)
                return TETENGO2_STDALT_NULLOPT;

            return tetengo2::stdalt::make_optional(
                position_unit_type::from_pixels(tetengo2::stdalt::get<uint_type>(*position)));
        }

        void set_property_bar_splitter_position(const position_unit_type& position)
        {
            m_p_config->set(
                string_type{ TETENGO2_TEXT("MainWindow/PropertyBarSplitterPosition") },
                config_value_type{ position.to_pixels() });
        }

        void clear_config()
        {
            m_p_config->clear();
        }


    private:
        // types

        using path_string_type = typename tetengo2::stdalt::filesystem::path::string_type;

        using uint_type = tetengo2::type_list::size_type;

        using config_base_type = tetengo2::config::config_base;

        using config_value_type = typename config_base_type::value_type;

        using config_list_type = tetengo2::config::config_list;

        using cached_config_type = tetengo2::config::cached_config;

        using temporary_config_type = tetengo2::config::temporary_config;

        using persistent_config_type = tetengo2::config::persistent_config;

        template <typename T, typename Str>
        struct value_impl;

        template <typename T>
        struct value_impl<T, std::string>
        {
            boost::program_options::typed_value<T, char>* operator()() const
            {
                return boost::program_options::value<T>();
            }
        };

        template <typename T>
        struct value_impl<T, std::wstring>
        {
            boost::program_options::typed_value<T, wchar_t>* operator()() const
            {
                return boost::program_options::wvalue<T>();
            }
        };


        // static functions

        static boost::program_options::variables_map
        parse_command_line_arguments(const std::vector<string_type>& command_line_arguments)
        {
            boost::program_options::options_description visible_options{};
            visible_options.add_options()("dimension,d", value<string_type, string_type>());

            boost::program_options::options_description hidden_options{};
            hidden_options.add_options()("exe", value<string_type, string_type>())(
                "input", value<std::vector<string_type>, string_type>());

            boost::program_options::options_description options{};
            options.add(visible_options).add(hidden_options);

            boost::program_options::positional_options_description positional_options{};
            positional_options.add("exe", 1);
            positional_options.add("input", -1);

            boost::program_options::variables_map option_values{};
            try
            {
                using command_line_parser_type =
                    boost::program_options::basic_command_line_parser<typename string_type::value_type>;
                const auto parsed_options = command_line_parser_type{ command_line_arguments }
                                                .options(std::move(options))
                                                .positional(std::move(positional_options))
                                                .run();
                boost::program_options::store(parsed_options, option_values);
            }
            catch (const boost::program_options::error&)
            {
            }
            boost::program_options::notify(option_values);

            return option_values;
        }

        template <typename T, typename Str>
        static boost::program_options::typed_value<T, typename Str::value_type>* value()
        {
            return value_impl<T, Str>()();
        }

        static std::unique_ptr<config_base_type>
        create_config(const boost::program_options::variables_map& options, string_type group_name)
        {
            std::vector<std::unique_ptr<config_base_type>> p_configs{};
            p_configs.push_back(create_temporary_config(options));
            p_configs.push_back(create_persistent_config(std::move(group_name)));

            return std::make_unique<config_list_type>(std::move(p_configs));
        }

        static std::unique_ptr<config_base_type>
        create_temporary_config(const boost::program_options::variables_map& options)
        {
            std::vector<std::pair<string_type, config_value_type>> values;
            {
                const auto main_window_dimension_ = main_window_dimension_in_command_line(options);
                if (main_window_dimension_)
                {
                    values.emplace_back(
                        string_type{ TETENGO2_TEXT("MainWindow/Width") },
                        config_value_type{ main_window_dimension_->first });
                    values.emplace_back(
                        string_type{ TETENGO2_TEXT("MainWindow/Height") },
                        config_value_type{ main_window_dimension_->second });
                }
            }

            auto p_config = std::make_unique<temporary_config_type>();
            for (auto&& value : values)
            {
                p_config->set(value.first, std::move(value.second));
            }
            return std::move(p_config);
        }

        static tetengo2::stdalt::optional<std::pair<uint_type, uint_type>>
        main_window_dimension_in_command_line(const boost::program_options::variables_map& options)
        {
            const auto found = options.find("dimension");
            if (found == options.end())
                return TETENGO2_STDALT_NULLOPT;

            const auto width_and_height = parse_dimension(found->second.as<string_type>());
            if (!width_and_height)
                return TETENGO2_STDALT_NULLOPT;

            return width_and_height;
        }

        static tetengo2::stdalt::optional<std::pair<uint_type, uint_type>>
        parse_dimension(const string_type& dimension_string)
        {
            std::vector<string_type> result{};
            using char_type = typename string_type::value_type;
            boost::split(result, dimension_string, [](const char_type character) {
                return character == char_type{ TETENGO2_TEXT('x') };
            });
            if (result.size() < 2)
                return TETENGO2_STDALT_NULLOPT;

            try
            {
                return std::make_pair(
                    boost::lexical_cast<uint_type>(result[0]), boost::lexical_cast<uint_type>(result[1]));
            }
            catch (const boost::bad_lexical_cast&)
            {
                return TETENGO2_STDALT_NULLOPT;
            }
        }

        static std::unique_ptr<config_base_type> create_persistent_config(string_type group_name)
        {
            return std::make_unique<cached_config_type>(
                std::make_unique<persistent_config_type>(std::move(group_name)));
        }


        // variables

        tetengo2::stdalt::filesystem::path m_base_path;

        tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path> m_input;

        std::unique_ptr<config_base_type> m_p_config;


        // functions

        void initialize(const std::vector<string_type>& command_line_arguments, string_type config_group_name)
        {
            const auto options = parse_command_line_arguments(command_line_arguments);

            assert(options.find("exe") != options.end());
            m_base_path = tetengo2::stdalt::filesystem::path(options["exe"].template as<string_type>()).parent_path();

            if (options.find("input") != options.end())
            {
                const auto& input_values = options["input"].template as<std::vector<string_type>>();
                if (!input_values.empty())
                    m_input = tetengo2::stdalt::optional<string_type>{ input_values[0] };
            }

            m_p_config = create_config(options, std::move(config_group_name));
        }
    };


    template <typename String, typename Position, typename Dimension>
    settings<String, Position, Dimension>::settings(
        const std::vector<string_type>& command_line_arguments,
        string_type                     config_group_name)
    : m_p_impl{ std::make_unique<impl>(command_line_arguments, std::move(config_group_name)) }
    {}

    template <typename String, typename Position, typename Dimension>
    settings<String, Position, Dimension>::~settings() noexcept
    {}

    template <typename String, typename Position, typename Dimension>
    const tetengo2::stdalt::filesystem::path& settings<String, Position, Dimension>::base_path() const
    {
        return m_p_impl->base_path();
    }

    template <typename String, typename Position, typename Dimension>
    const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>&
    settings<String, Position, Dimension>::input() const
    {
        return m_p_impl->input();
    }

    template <typename String, typename Position, typename Dimension>
    tetengo2::stdalt::filesystem::path settings<String, Position, Dimension>::message_directory_path() const
    {
        return m_p_impl->message_directory_path();
    }

    template <typename String, typename Position, typename Dimension>
    tetengo2::stdalt::filesystem::path settings<String, Position, Dimension>::image_directory_path() const
    {
        return m_p_impl->image_directory_path();
    }

    template <typename String, typename Position, typename Dimension>
    tetengo2::stdalt::optional<typename settings<String, Position, Dimension>::dimension_type>
    settings<String, Position, Dimension>::main_window_dimension() const
    {
        return m_p_impl->main_window_dimension();
    }

    template <typename String, typename Position, typename Dimension>
    void settings<String, Position, Dimension>::set_main_window_dimension(const dimension_type& dimension)
    {
        m_p_impl->set_main_window_dimension(dimension);
    }

    template <typename String, typename Position, typename Dimension>
    tetengo2::stdalt::optional<bool> settings<String, Position, Dimension>::main_window_maximized() const
    {
        return m_p_impl->main_window_maximized();
    }

    template <typename String, typename Position, typename Dimension>
    void settings<String, Position, Dimension>::set_main_window_maximized(const bool status)
    {
        return m_p_impl->set_main_window_maximized(status);
    }

    template <typename String, typename Position, typename Dimension>
    tetengo2::stdalt::optional<typename settings<String, Position, Dimension>::dimension_unit_type>
    settings<String, Position, Dimension>::property_bar_width() const
    {
        return m_p_impl->property_bar_width();
    }

    template <typename String, typename Position, typename Dimension>
    void settings<String, Position, Dimension>::set_property_bar_width(const dimension_unit_type& width)
    {
        return m_p_impl->set_property_bar_width(width);
    }

    template <typename String, typename Position, typename Dimension>
    tetengo2::stdalt::optional<bool> settings<String, Position, Dimension>::property_bar_minimized() const
    {
        return m_p_impl->property_bar_minimized();
    }

    template <typename String, typename Position, typename Dimension>
    void settings<String, Position, Dimension>::set_property_bar_minimized(const bool status)
    {
        return m_p_impl->set_property_bar_minimized(status);
    }

    template <typename String, typename Position, typename Dimension>
    tetengo2::stdalt::optional<typename settings<String, Position, Dimension>::position_unit_type>
    settings<String, Position, Dimension>::property_bar_splitter_position() const
    {
        return m_p_impl->property_bar_splitter_position();
    }

    template <typename String, typename Position, typename Dimension>
    void settings<String, Position, Dimension>::set_property_bar_splitter_position(const position_unit_type& position)
    {
        return m_p_impl->set_property_bar_splitter_position(position);
    }

    template <typename String, typename Position, typename Dimension>
    void settings<String, Position, Dimension>::clear_config()
    {
        return m_p_impl->clear_config();
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class settings<
        typename application::common_type_list_type::string_type,
        typename application::ui_type_list_type::position_type,
        typename application::ui_type_list_type::dimension_type>;
#endif

    template class settings<
        typename test::common_type_list_type::string_type,
        typename test::ui_type_list_type::position_type,
        typename test::ui_type_list_type::dimension_type>;
}
