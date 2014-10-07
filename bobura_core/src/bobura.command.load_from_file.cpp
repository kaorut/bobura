/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>

#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>

#include <tetengo2.h>

#include <bobura/command/load_from_file.h>
#include <bobura/command/traits.h>
#include <bobura/load_save/traits.h>
#include <bobura/oudia_diagram_dialog.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits, typename LoadSaveTraits>
    class load_from_file<Traits, LoadSaveTraits>::impl
    {
    public:
        // types

        using model_type = typename load_from_file::model_type;

        using abstract_window_type = typename load_from_file::abstract_window_type;

        using load_from_file_type = typename load_from_file::load_from_file_type;

        using parameter_type = typename load_from_file::parameter_type;


        // constructors and destructor

        explicit impl(const load_from_file_type& load_from_file)
        :
        m_load_from_file(load_from_file)
        {}


        // functions

        bool enabled(const model_type& model)
        const
        {
            return m_load_from_file.reloadable(model, boost::none);
        }

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            m_load_from_file(model, boost::none, parent);
        }

        void execute(model_type& model, abstract_window_type& parent, const parameter_base& parameter)
        const
        {
            m_load_from_file(model, boost::make_optional(parameter.as<parameter_type>().path()), parent);
        }


    private:
        // variables

        const load_from_file_type& m_load_from_file;


    };


    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::parameter_type::parameter_type(boost::filesystem::path path)
    :
    m_path(std::move(path))
    {}

    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::parameter_type::~parameter_type()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <typename Traits, typename LoadSaveTraits>
    const boost::filesystem::path& load_from_file<Traits, LoadSaveTraits>::parameter_type::path()
    const
    {
        return m_path;
    }

    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::load_from_file(const load_from_file_type& load_from_file)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(load_from_file))
    {}

    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::~load_from_file()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename LoadSaveTraits>
    bool load_from_file<Traits, LoadSaveTraits>::enabled_impl(const model_type& model)
    const
    {
        return m_p_impl->enabled(model);
    }

    template <typename Traits, typename LoadSaveTraits>
    void load_from_file<Traits, LoadSaveTraits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }

    template <typename Traits, typename LoadSaveTraits>
    void load_from_file<Traits, LoadSaveTraits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent,
        const parameter_base& parameter
    )
    const
    {
        m_p_impl->execute(model, parent, parameter);
    }


    template class load_from_file<
        traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
            typename boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type
        >,
        load_save::traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<common_type_list, type::input_stream_iterator>::type,
            typename boost::mpl::at<common_type_list, type::output_stream>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
            typename boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
            typename boost::mpl::at<common_dialog_type_list, type::common_dialog::file_open_dialog>::type,
            typename boost::mpl::at<common_dialog_type_list, type::common_dialog::file_save_dialog>::type,
            oudia_diagram_dialog<
                typename boost::mpl::at<common_type_list, type::size>::type,
                typename boost::mpl::at<common_type_list, type::string>::type,
                typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >,
            typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
            typename boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type,
            typename boost::mpl::at<locale_type_list, type::locale::windia_file_encoder>::type
        >
    >;


}}
