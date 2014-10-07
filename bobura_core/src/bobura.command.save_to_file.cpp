/*! \file
    \brief The definition of bobura::command::save_to_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/save_to_file.h>
#include <bobura/command/traits.h>
#include <bobura/load_save/traits.h>
#include <bobura/oudia_diagram_dialog.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits, typename LoadSaveTraits>
    class save_to_file<Traits, LoadSaveTraits>::impl
    {
    public:
        // types

        using model_type = typename save_to_file::model_type;

        using abstract_window_type = typename save_to_file::abstract_window_type;

        using save_to_file_type = typename save_to_file::save_to_file_type;


        // constructors and destructor

        explicit impl(const save_to_file_type& save_to_file)
        :
        m_save_to_file(save_to_file)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            m_save_to_file(model, parent);
        }


    private:
        // variables

        const save_to_file_type& m_save_to_file;


    };


    template <typename Traits, typename LoadSaveTraits>
    save_to_file<Traits, LoadSaveTraits>::save_to_file(const save_to_file_type& save_to_file)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(save_to_file))
    {}

    template <typename Traits, typename LoadSaveTraits>
    save_to_file<Traits, LoadSaveTraits>::~save_to_file()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename LoadSaveTraits>
    void save_to_file<Traits, LoadSaveTraits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class save_to_file<
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
