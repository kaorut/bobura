/*! \file
    \brief The definition of bobura::command::set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <memory>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>

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
#include <bobura/command/train_kind.h>
#include <bobura/type_list.h>
#include <bobura/command/vertically_zoom_in.h>
#include <bobura/command/vertically_zoom_out.h>


namespace bobura { namespace command
{
    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    class set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::impl
    {
    public:
        // types

        using traits_type = typename set::traits_type;

        using view_traits_type = typename set::view_traits_type;

        using load_save_traits_type = typename set::load_save_traits_type;

        using size_type = typename set::size_type;

        using position_type = typename set::position_type;

        using dimension_type = typename set::dimension_type;

        using dialog_type = typename set::dialog_type;

        using color_type = typename set::color_type;

        using point_unit_size_type = typename set::point_unit_size_type;

        using config_traits_type = typename set::config_traits_type;

        using message_catalog_type = typename set::message_catalog_type;

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
        m_p_ask_file_path_and_save_to_file(create_save_to_file(ask_file_path_and_save_to_file)),
        m_p_set_horizontal_scale(create_set_horizontal_scale(diagram_view)),
        m_p_set_vertical_scale(create_set_vertical_scale(diagram_view)),
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
                tetengo2::stdalt::make_unique<command::load_from_file<
                    traits_type, load_save_traits_type
                >::parameter_type>(path);
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

        using scale_list_type = typename boost::mpl::at<view_type_list, type::view::scale_list>::type;


        // static functions

        static command_ptr_type create_about(
            const message_catalog_type& message_catalog,
            const settings_type&        settings
        )
        {
            return
                tetengo2::stdalt::make_unique<
                    command::about<
                        traits_type,
                        position_type,
                        dimension_type,
                        dialog_type,
                        config_traits_type,
                        message_catalog_type
                    >
                >(message_catalog, settings);
        }

        static command_ptr_type create_exit()
        {
            return tetengo2::stdalt::make_unique<command::exit<traits_type>>();
        }

        static command_ptr_type create_file_property(const message_catalog_type& message_catalog)
        {
            return
                tetengo2::stdalt::make_unique<command::file_property<traits_type, dialog_type, message_catalog_type>>(
                    message_catalog
                );
        }

        static command_ptr_type create_font_color(const message_catalog_type& message_catalog)
        {
            return
                tetengo2::stdalt::make_unique<
                    command::font_color<
                        traits_type, dialog_type, point_unit_size_type, color_type, message_catalog_type
                    >
                >(message_catalog);
        }

        static command_ptr_type create_horizontally_zoom_in(diagram_view_type& diagram_view)
        {
            return
                tetengo2::stdalt::make_unique<command::horizontally_zoom_in<traits_type, view_traits_type>>(
                    diagram_view
                );
        }

        static command_ptr_type create_horizontally_zoom_out(diagram_view_type& diagram_view)
        {
            return
                tetengo2::stdalt::make_unique<command::horizontally_zoom_out<traits_type, view_traits_type>>(
                    diagram_view
                );
        }

        static command_ptr_type create_load_from_file(const load_from_file_type& load_from_file)
        {
            return
                tetengo2::stdalt::make_unique<command::load_from_file<traits_type, load_save_traits_type>>(
                    load_from_file
                );
        }

        static command_ptr_type create_new_file(const new_file_type& new_file)
        {
            return tetengo2::stdalt::make_unique<command::new_file<traits_type, load_save_traits_type>>(new_file);
        }

        static command_ptr_type create_nop()
        {
            return tetengo2::stdalt::make_unique<command::nop<traits_type>>();
        }

        static command_ptr_type create_open_www_tetengo_org()
        {
            return tetengo2::stdalt::make_unique<command::open_www_tetengo_org<traits_type>>();
        }

        static command_ptr_type create_save_to_file(const save_to_file_type& save_to_file)
        {
            return
                tetengo2::stdalt::make_unique<command::save_to_file<traits_type, load_save_traits_type>>(save_to_file);
        }

        static std::vector<command_ptr_type> create_set_horizontal_scale(diagram_view_type& diagram_view)
        {
            const scale_list_type scale_list{};

            std::vector<command_ptr_type> commands{};
            commands.reserve(scale_list.size());

            for (size_type i = 0; i < scale_list.size(); ++i)
            {
                commands.push_back(
                    tetengo2::stdalt::make_unique<command::set_horizontal_scale<traits_type>>(
                        diagram_view, scale_list.at(i)
                    )
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
                    tetengo2::stdalt::make_unique<command::set_vertical_scale<traits_type>>(
                        diagram_view, scale_list.at(i)
                    )
                );
            }

            return commands;
        }

        static command_ptr_type create_train_kind(const message_catalog_type& message_catalog)
        {
            return tetengo2::stdalt::make_unique<command::train_kind<traits_type>>(message_catalog);
        }

        static command_ptr_type create_vertically_zoom_in(diagram_view_type& diagram_view)
        {
            return
                tetengo2::stdalt::make_unique<command::vertically_zoom_in<traits_type, view_traits_type>>(
                    diagram_view
                );
        }

        static command_ptr_type create_vertically_zoom_out(diagram_view_type& diagram_view)
        {
            return
                tetengo2::stdalt::make_unique<command::vertically_zoom_out<traits_type, view_traits_type>>(
                    diagram_view
                );
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

        const command_ptr_type m_p_train_kind;

        const command_ptr_type m_p_vertically_zoom_in;

        const command_ptr_type m_p_vertically_zoom_out;


    };


    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::set(
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

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::~set()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::about()
    const
    {
        return m_p_impl->about();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::ask_file_path_and_save_to_file()
    const
    {
        return m_p_impl->ask_file_path_and_save_to_file();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::exit()
    const
    {
        return m_p_impl->exit();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::file_property()
    const
    {
        return m_p_impl->file_property();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::font_color()
    const
    {
        return m_p_impl->font_color();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::horizontally_zoom_in()
    const
    {
        return m_p_impl->horizontally_zoom_in();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::horizontally_zoom_out()
    const
    {
        return m_p_impl->horizontally_zoom_out();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::load_from_file()
    const
    {
        return m_p_impl->load_from_file();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    std::unique_ptr<
        typename set<
            Traits,
            ViewTraits,
            LoadSaveTraits,
            Position,
            Dimension,
            Dialog,
            Color,
            PointUnitSize,
            ConfigTraits,
            MessageCatalog
        >::parameter_type
    >
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::create_load_from_file_parameter(const boost::filesystem::path& path)
    const
    {
        return m_p_impl->create_load_from_file_parameter(path);
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::new_file()
    const
    {
        return m_p_impl->new_file();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::nop()
    const
    {
        return m_p_impl->nop();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::open_www_tetengo_org()
    const
    {
        return m_p_impl->open_www_tetengo_org();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::reload()
    const
    {
        return m_p_impl->reload();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::save_to_file()
    const
    {
        return m_p_impl->save_to_file();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::set_horizontal_scale(const size_type index)
    const
    {
        return m_p_impl->set_horizontal_scale(index);
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::set_vertical_scale(const size_type index)
    const
    {
        return m_p_impl->set_vertical_scale(index);
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::train_kind()
    const
    {
        return m_p_impl->train_kind();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::vertically_zoom_in()
    const
    {
        return m_p_impl->vertically_zoom_in();
    }

    template <
        typename Traits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename ConfigTraits,
        typename MessageCatalog
    >
    typename const set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::command_type&
    set<
        Traits,
        ViewTraits,
        LoadSaveTraits,
        Position,
        Dimension,
        Dialog,
        Color,
        PointUnitSize,
        ConfigTraits,
        MessageCatalog
    >::vertically_zoom_out()
    const
    {
        return m_p_impl->vertically_zoom_out();
    }


    template class set<
        traits<
            boost::mpl::at<common_type_list, type::size>::type,
            boost::mpl::at<common_type_list, type::difference>::type,
            boost::mpl::at<common_type_list, type::string>::type,
            boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            boost::mpl::at<model_type_list, type::model::speed>::type,
            boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            boost::mpl::at<ui_type_list, type::ui::abstract_window>::type
        >,
        typename boost::mpl::at<view_type_list, type::view::traits>::type,
        typename boost::mpl::at<load_save_type_list, type::load_save::traits>::type,
        typename boost::mpl::at<ui_type_list, type::ui::position>::type,
        typename boost::mpl::at<ui_type_list, type::ui::dimension>::type,
        typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
        typename boost::mpl::at<ui_type_list, type::ui::color>::type,
        typename boost::mpl::at<ui_type_list, type::ui::point_unit_size>::type,
        typename boost::mpl::at<bobura::setting_type_list, bobura::type::setting::config_traits>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
    >;


}}
