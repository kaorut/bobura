/*! \file
    \brief The definition of bobura::command::set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/command/about.h>
#include <bobura/command/command_base.h>
#include <bobura/command/exit.h>
#include <bobura/command/file_property.h>
#include <bobura/command/font_color.h>
#include <bobura/command/horizontally_zoom_in.h>
#include <bobura/command/horizontally_zoom_out.h>
#include <bobura/command/load_from_file.h>
#include <bobura/command/new_file.h>
#include <bobura/command/nop.h>
#include <bobura/command/open_www_tetengo_org.h>
#include <bobura/command/save_to_file.h>
#include <bobura/command/set.h>
#include <bobura/command/set_horizontal_scale.h>
#include <bobura/command/set_vertical_scale.h>
#include <bobura/command/show_diagram.h>
#include <bobura/command/show_timetable_down.h>
#include <bobura/command/show_timetable_up.h>
#include <bobura/command/train_kind.h>
#include <bobura/command/vertically_zoom_in.h>
#include <bobura/command/vertically_zoom_out.h>
#include <bobura/type_list.h>
#include <bobura/view/scale_list.h>


namespace bobura { namespace command
{
    template <typename Traits>
    class set<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = typename set::traits_type;

        using size_type = typename set::size_type;

        using string_type = typename set::string_type;

        using position_type = typename set::position_type;

        using dimension_type = typename set::dimension_type;

        using dialog_type = typename set::dialog_type;

        using color_type = typename set::color_type;

        using point_unit_size_type = typename set::point_unit_size_type;

        using canvas_type = typename set::canvas_type;

        using scale_type = typename set::scale_type;

        using shell_type = typename set::shell_type;

        using font_dialog_type = typename set::font_dialog_type;

        using color_dialog_type = typename set::color_dialog_type;

        using message_catalog_type = typename set::message_catalog_type;

        using command_traits_type = typename set::command_traits_type;

        using main_window_traits_type = typename set::main_window_traits_type;

        using diagram_view_traits_type = typename set::diagram_view_traits_type;

        using load_save_traits_type = typename set::load_save_traits_type;

        using dialog_traits_type = typename set::dialog_traits_type;

        using new_file_type = typename set::new_file_type;

        using load_from_file_type = typename set::load_from_file_type;

        using save_to_file_type = typename set::save_to_file_type;

        using diagram_view_type = typename set::diagram_view_type;

        using settings_type = typename set::settings_type;

        using command_type = typename set::command_type;

        using parameter_type = typename set::parameter_type;


        // constructors and destructor

        impl(
            const new_file_type&          new_file,
            const load_from_file_type&    load_from_file,
            const load_from_file_type&    reload,
            const save_to_file_type&      save_to_file,
            const save_to_file_type&      ask_file_path_and_save_to_file,
            diagram_view_type&            diagram_view,
            const settings_type&          settings,
            const message_catalog_type&   message_catalog
        )
        :
        m_p_about(create_about(message_catalog, settings)),
        m_p_ask_file_path_and_save_to_file(create_save_to_file(ask_file_path_and_save_to_file)),
        m_p_exit(create_exit()),
        m_p_file_property(create_file_property(message_catalog)),
        m_p_font_color(create_font_color(message_catalog)),
        m_p_horizontally_zoom_in(create_horizontally_zoom_in(diagram_view)),
        m_p_horizontally_zoom_out(create_horizontally_zoom_out(diagram_view)),
        m_p_load_from_file(create_load_from_file(load_from_file)),
        m_p_new_file(create_new_file(new_file)),
        m_p_nop(create_nop()),
        m_p_open_www_tetengo_org(create_open_www_tetengo_org()),
        m_p_reload(create_load_from_file(reload)),
        m_p_save_to_file(create_save_to_file(save_to_file)),
        m_p_set_horizontal_scale(create_set_horizontal_scale(diagram_view)),
        m_p_set_vertical_scale(create_set_vertical_scale(diagram_view)),
        m_p_show_diagram(create_show_diagram()),
        m_p_show_timetable_down(create_show_timetable_down()),
        m_p_show_timetable_up(create_show_timetable_up()),
        m_p_train_kind(create_train_kind(message_catalog)),
        m_p_vertically_zoom_in(create_vertically_zoom_in(diagram_view)),
        m_p_vertically_zoom_out(create_vertically_zoom_out(diagram_view))
        {}


        // functions

        const command_type& about()
        const
        {
            return *m_p_about;
        }

        const command_type& ask_file_path_and_save_to_file()
        const
        {
            return *m_p_ask_file_path_and_save_to_file;
        }

        const command_type& exit()
        const
        {
            return *m_p_exit;
        }

        const command_type& file_property()
        const
        {
            return *m_p_file_property;
        }

        const command_type& font_color()
        const
        {
            return *m_p_font_color;
        }

        const command_type& horizontally_zoom_in()
        const
        {
            return *m_p_horizontally_zoom_in;
        }

        const command_type& horizontally_zoom_out()
        const
        {
            return *m_p_horizontally_zoom_out;
        }

        const command_type& load_from_file()
        const
        {
            return *m_p_load_from_file;
        }

        std::unique_ptr<parameter_type> create_load_from_file_parameter(const boost::filesystem::path& path)
        const
        {
            return
                tetengo2::stdalt::make_unique<
                    typename command::load_from_file<command_traits_type, load_save_traits_type>::parameter_type
                >(path);
        }

        const command_type& new_file()
        const
        {
            return *m_p_new_file;
        }

        const command_type& nop()
        const
        {
            return *m_p_nop;
        }

        const command_type& open_www_tetengo_org()
        const
        {
            return *m_p_open_www_tetengo_org;
        }

        const command_type& reload()
        const
        {
            return *m_p_reload;
        }

        const command_type& save_to_file()
        const
        {
            return *m_p_save_to_file;
        }

        const command_type& set_horizontal_scale(const size_type index)
        const
        {
            return *m_p_set_horizontal_scale[index];
        }

        const command_type& set_vertical_scale(const size_type index)
        const
        {
            return *m_p_set_vertical_scale[index];
        }

        const command_type& show_diagram()
        const
        {
            return *m_p_show_diagram;
        }

        const command_type& show_timetable_down()
        const
        {
            return *m_p_show_timetable_down;
        }

        const command_type& show_timetable_up()
        const
        {
            return *m_p_show_timetable_up;
        }

        const command_type& train_kind()
        const
        {
            return *m_p_train_kind;
        }

        const command_type& vertically_zoom_in()
        const
        {
            return *m_p_vertically_zoom_in;
        }

        const command_type& vertically_zoom_out()
        const
        {
            return *m_p_vertically_zoom_out;
        }


    private:
        // types

        using command_ptr_type = std::unique_ptr<command_type>;

        using scale_list_type = view::scale_list<size_type, string_type, scale_type>;


        // static functions

        static command_ptr_type create_about(
            const message_catalog_type& message_catalog,
            const settings_type&        settings
        )
        {
            return
                tetengo2::stdalt::make_unique<
                    command::about<
                        command_traits_type,
                        position_type,
                        dimension_type,
                        message_catalog_type,
                        dialog_traits_type
                    >
                >(message_catalog, settings);
        }

        static command_ptr_type create_exit()
        {
            return tetengo2::stdalt::make_unique<command::exit<command_traits_type>>();
        }

        static command_ptr_type create_file_property(const message_catalog_type& message_catalog)
        {
            return
                tetengo2::stdalt::make_unique<
                    command::file_property<command_traits_type, dialog_type, message_catalog_type, dialog_traits_type>
                >(message_catalog);
        }

        static command_ptr_type create_font_color(const message_catalog_type& message_catalog)
        {
            return
                tetengo2::stdalt::make_unique<
                    command::font_color<
                        command_traits_type,
                        dialog_type,
                        point_unit_size_type,
                        color_type,
                        canvas_type,
                        font_dialog_type,
                        color_dialog_type,
                        message_catalog_type,
                        dialog_traits_type
                    >
                >(message_catalog);
        }

        static command_ptr_type create_horizontally_zoom_in(diagram_view_type& diagram_view)
        {
            return
                tetengo2::stdalt::make_unique<
                    command::horizontally_zoom_in<
                        command_traits_type, traits_type, main_window_traits_type, diagram_view_traits_type
                    >
                >(diagram_view);
        }

        static command_ptr_type create_horizontally_zoom_out(diagram_view_type& diagram_view)
        {
            return
                tetengo2::stdalt::make_unique<
                    command::horizontally_zoom_out<
                        command_traits_type, traits_type, main_window_traits_type, diagram_view_traits_type
                    >
                >(diagram_view);
        }

        static command_ptr_type create_load_from_file(const load_from_file_type& load_from_file)
        {
            return
                tetengo2::stdalt::make_unique<command::load_from_file<command_traits_type, load_save_traits_type>>(
                    load_from_file
                );
        }

        static command_ptr_type create_new_file(const new_file_type& new_file)
        {
            return
                tetengo2::stdalt::make_unique<command::new_file<command_traits_type, load_save_traits_type>>(new_file);
        }

        static command_ptr_type create_nop()
        {
            return tetengo2::stdalt::make_unique<command::nop<command_traits_type>>();
        }

        static command_ptr_type create_open_www_tetengo_org()
        {
            return tetengo2::stdalt::make_unique<command::open_www_tetengo_org<command_traits_type, shell_type>>();
        }

        static command_ptr_type create_save_to_file(const save_to_file_type& save_to_file)
        {
            return
                tetengo2::stdalt::make_unique<
                    command::save_to_file<command_traits_type, load_save_traits_type>
                >(save_to_file);
        }

        static std::vector<command_ptr_type> create_set_horizontal_scale(diagram_view_type& diagram_view)
        {
            const scale_list_type scale_list{};

            std::vector<command_ptr_type> commands{};
            commands.reserve(scale_list.size());

            for (size_type i = 0; i < scale_list.size(); ++i)
            {
                commands.push_back(
                    tetengo2::stdalt::make_unique<
                        command::set_horizontal_scale<
                            command_traits_type,
                            scale_type,
                            traits_type,
                            main_window_traits_type,
                            diagram_view_traits_type
                        >
                    >(diagram_view, scale_list.at(i))
                );
            }

            return commands;
        }

        static std::vector<command_ptr_type> create_set_vertical_scale(diagram_view_type& diagram_view)
        {
            const scale_list_type scale_list{};

            std::vector<command_ptr_type> commands{};
            commands.reserve(scale_list.size());

            for (size_type i = 0; i < scale_list.size(); ++i)
            {
                commands.push_back(
                    tetengo2::stdalt::make_unique<
                        command::set_vertical_scale<
                            command_traits_type,
                            scale_type,
                            traits_type,
                            main_window_traits_type,
                            diagram_view_traits_type
                        >
                    >(diagram_view, scale_list.at(i))
                );
            }

            return commands;
        }

        static command_ptr_type create_show_diagram()
        {
            return
                tetengo2::stdalt::make_unique<
                    command::show_diagram<command_traits_type, traits_type, main_window_traits_type>
                >();
        }

        static command_ptr_type create_show_timetable_down()
        {
            return
                tetengo2::stdalt::make_unique<
                    command::show_timetable_down<command_traits_type, traits_type, main_window_traits_type>
                >();
        }

        static command_ptr_type create_show_timetable_up()
        {
            return
                tetengo2::stdalt::make_unique<
                    command::show_timetable_up<command_traits_type, traits_type, main_window_traits_type>
                >();
        }

        static command_ptr_type create_train_kind(const message_catalog_type& message_catalog)
        {
            return
                tetengo2::stdalt::make_unique<
                    command::train_kind<
                        command_traits_type,
                        dialog_type,
                        point_unit_size_type,
                        color_type,
                        canvas_type,
                        font_dialog_type,
                        color_dialog_type,
                        message_catalog_type,
                        dialog_traits_type
                    >
                >(message_catalog);
        }

        static command_ptr_type create_vertically_zoom_in(diagram_view_type& diagram_view)
        {
            return
                tetengo2::stdalt::make_unique<
                    command::vertically_zoom_in<
                        command_traits_type, traits_type, main_window_traits_type, diagram_view_traits_type
                    >
                >(diagram_view);
        }

        static command_ptr_type create_vertically_zoom_out(diagram_view_type& diagram_view)
        {
            return
                tetengo2::stdalt::make_unique<
                    command::vertically_zoom_out<
                        command_traits_type, traits_type, main_window_traits_type, diagram_view_traits_type
                    >
                >(diagram_view);
        }


        // variables

        const command_ptr_type m_p_about;

        const command_ptr_type m_p_ask_file_path_and_save_to_file;

        const command_ptr_type m_p_exit;

        const command_ptr_type m_p_file_property;

        const command_ptr_type m_p_font_color;

        const command_ptr_type m_p_horizontally_zoom_in;

        const command_ptr_type m_p_horizontally_zoom_out;

        const command_ptr_type m_p_load_from_file;

        const command_ptr_type m_p_new_file;

        const command_ptr_type m_p_nop;

        const command_ptr_type m_p_open_www_tetengo_org;

        const command_ptr_type m_p_reload;

        const command_ptr_type m_p_save_to_file;

        const std::vector<command_ptr_type> m_p_set_horizontal_scale;

        const std::vector<command_ptr_type> m_p_set_vertical_scale;

        const command_ptr_type m_p_show_diagram;

        const command_ptr_type m_p_show_timetable_down;

        const command_ptr_type m_p_show_timetable_up;

        const command_ptr_type m_p_train_kind;

        const command_ptr_type m_p_vertically_zoom_in;

        const command_ptr_type m_p_vertically_zoom_out;


    };


    template <typename Traits>
    set<Traits>::set(
        const new_file_type&          new_file,
        const load_from_file_type&    load_from_file,
        const load_from_file_type&    reload,
        const save_to_file_type&      save_to_file,
        const save_to_file_type&      ask_file_path_and_save_to_file,
        diagram_view_type&            diagram_view,
        const settings_type&          settings,
        const message_catalog_type&   message_catalog
    )
    :
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            new_file,
            load_from_file,
            reload,
            save_to_file,
            ask_file_path_and_save_to_file,
            diagram_view,
            settings,
            message_catalog
        )
    )
    {}

    template <typename Traits>
    set<Traits>::~set()
    noexcept
    {}

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::about()
    const
    {
        return m_p_impl->about();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::ask_file_path_and_save_to_file()
    const
    {
        return m_p_impl->ask_file_path_and_save_to_file();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::exit()
    const
    {
        return m_p_impl->exit();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::file_property()
    const
    {
        return m_p_impl->file_property();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::font_color()
    const
    {
        return m_p_impl->font_color();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::horizontally_zoom_in()
    const
    {
        return m_p_impl->horizontally_zoom_in();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::horizontally_zoom_out()
    const
    {
        return m_p_impl->horizontally_zoom_out();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::load_from_file()
    const
    {
        return m_p_impl->load_from_file();
    }

    template <typename Traits>
    std::unique_ptr<typename set<Traits>::parameter_type> set<Traits>::create_load_from_file_parameter(
        const boost::filesystem::path& path
    )
    const
    {
        return m_p_impl->create_load_from_file_parameter(path);
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::new_file()
    const
    {
        return m_p_impl->new_file();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::nop()
    const
    {
        return m_p_impl->nop();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::open_www_tetengo_org()
    const
    {
        return m_p_impl->open_www_tetengo_org();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::reload()
    const
    {
        return m_p_impl->reload();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::save_to_file()
    const
    {
        return m_p_impl->save_to_file();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::set_horizontal_scale(const size_type index)
    const
    {
        return m_p_impl->set_horizontal_scale(index);
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::set_vertical_scale(const size_type index)
    const
    {
        return m_p_impl->set_vertical_scale(index);
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::show_diagram()
    const
    {
        return m_p_impl->show_diagram();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::show_timetable_down()
    const
    {
        return m_p_impl->show_timetable_down();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::show_timetable_up()
    const
    {
        return m_p_impl->show_timetable_up();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::train_kind()
    const
    {
        return m_p_impl->train_kind();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::vertically_zoom_in()
    const
    {
        return m_p_impl->vertically_zoom_in();
    }

    template <typename Traits>
    const typename set<Traits>::command_type& set<Traits>::vertically_zoom_out()
    const
    {
        return m_p_impl->vertically_zoom_out();
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class set<typename application::traits_type_list_type::command_set_type>;
#endif

    template class set<typename test::traits_type_list_type::command_set_type>;


}}
