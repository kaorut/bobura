/*! \file
    \brief The definition of bobura::command::train_kind.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>

#include <tetengo2.h>

#include <bobura/command/train_kind.h>
#include <bobura/type_list.h>
#include <bobura/train_kind_dialog.h>


namespace bobura { namespace command
{
    template <
        typename Traits,
        typename Dialog,
        typename Color,
        typename Canvas,
        typename ColorDialog,
        typename MessageCatalog,
        typename DialogTraits
    >
    class train_kind<Traits, Dialog, Color, Canvas, ColorDialog, MessageCatalog, DialogTraits>::impl
    {
    public:
        // types

        using model_type = typename train_kind::model_type;

        using abstract_window_type = typename train_kind::abstract_window_type;

        using size_type = typename train_kind::size_type;

        using string_type = typename train_kind::string_type;

        using font_type = typename train_kind::font_type;

        using dialog_type = typename train_kind::dialog_type;

        using color_type = typename train_kind::color_type;

        using canvas_type = typename train_kind::canvas_type;

        using color_dialog_type = typename train_kind::color_dialog_type;

        using message_catalog_type = typename train_kind::message_catalog_type;

        using dialog_traits_type = typename train_kind::dialog_traits_type;

        using train_kind_dialog_type =
            train_kind_dialog<
                dialog_traits_type, size_type, string_type, font_type, color_type, canvas_type, color_dialog_type
            >;


        // constructors and destructor

        explicit impl(const message_catalog_type& message_catalog)
        :
        m_message_catalog(message_catalog)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            const auto& font_color_set = model.timetable().font_color_set();
            train_kind_dialog_type dialog{
                parent, font_color_set.train_name(), font_color_set.background(), m_message_catalog
            };

            auto info_sets = to_info_sets(model.timetable());
            dialog.set_info_sets(std::move(info_sets));

            dialog.do_modal();
            if (dialog.result() != dialog_type::result_type::accepted)
                return;
        
            model.timetable().assign_train_kinds(
                to_train_kinds(dialog.info_sets()),
                to_train_kind_index_map(dialog.info_sets(), model.timetable().train_kinds().size())
            );
        }


    private:
        // types

        using info_set_type = typename train_kind_dialog_type::info_set_type;

        using timetable_type = typename model_type::timetable_type;

        using train_kinds_type = typename timetable_type::train_kinds_type;

        using train_kind_index_type = typename timetable_type::size_type;

        using train_kind_type = typename timetable_type::train_kind_type;

        using font_color_set_type = typename timetable_type::font_color_set_type;


        // static functions

        static std::vector<info_set_type> to_info_sets(const timetable_type& timetable)
        {
            std::vector<info_set_type> info_sets{};
            info_sets.reserve(timetable.train_kinds().size());

            for (auto i = timetable.train_kinds().begin(); i != timetable.train_kinds().end(); ++i)
            {
                const size_type index = std::distance(timetable.train_kinds().begin(), i);
                info_sets.emplace_back(boost::make_optional(index), timetable.train_kind_referred(i), *i);
            }

            return info_sets;
        }

        static train_kinds_type to_train_kinds(const std::vector<info_set_type>& info_sets)
        {
            train_kinds_type train_kinds{};
            train_kinds.reserve(info_sets.size());

            std::transform(
                info_sets.begin(),
                info_sets.end(),
                std::back_inserter(train_kinds),
                [](const info_set_type& info_set) { return info_set.train_kind(); }
            );

            return train_kinds;
        }

        static std::vector<train_kind_index_type> to_train_kind_index_map(
            const std::vector<info_set_type>& info_sets,
            const train_kind_index_type       original_train_kind_count
        )
        {
            std::vector<train_kind_index_type> map(original_train_kind_count, 0);

            for (train_kind_index_type i = 0; i < info_sets.size(); ++i)
            {
                if (!info_sets[i].original_index())
                    continue;

                assert(*info_sets[i].original_index() < original_train_kind_count);
                map[*info_sets[i].original_index()] = i;
            }

            return map;
        }


        // variables

        const message_catalog_type& m_message_catalog;


    };


    template <
        typename Traits,
        typename Dialog,
        typename Color,
        typename Canvas,
        typename ColorDialog,
        typename MessageCatalog,
        typename DialogTraits
    >
    train_kind<Traits, Dialog, Color, Canvas, ColorDialog, MessageCatalog, DialogTraits>::train_kind(
        const message_catalog_type& message_catalog
    )
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(message_catalog))
    {}

    template <
        typename Traits,
        typename Dialog,
        typename Color,
        typename Canvas,
        typename ColorDialog,
        typename MessageCatalog,
        typename DialogTraits
    >
    train_kind<Traits, Dialog, Color, Canvas, ColorDialog, MessageCatalog, DialogTraits>::~train_kind()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <
        typename Traits,
        typename Dialog,
        typename Color,
        typename Canvas,
        typename ColorDialog,
        typename MessageCatalog,
        typename DialogTraits
    >
    void train_kind<Traits, Dialog, Color, Canvas, ColorDialog, MessageCatalog, DialogTraits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    namespace
    {
        namespace application
        {
            using detail_type_list_type = detail_type_list_for_application;

            using locale_type_list_type = locale_type_list<detail_type_list_type>;
    
            using ui_type_list_type = ui_type_list<detail_type_list_type>;

            using common_dialog_type_list_type = common_dialog_type_list<detail_type_list_type>;

            using traits_type_list_type = traits_type_list<detail_type_list_type>;

        }

    }

    template class train_kind<
        typename boost::mpl::at<application::traits_type_list_type, type::traits::command>::type,
        typename boost::mpl::at<application::ui_type_list_type, type::ui::dialog>::type,
        typename boost::mpl::at<application::ui_type_list_type, type::ui::color>::type,
        typename boost::mpl::at<application::ui_type_list_type, type::ui::fast_canvas>::type,
        typename boost::mpl::at<application::common_dialog_type_list_type, type::common_dialog::color>::type,
        typename boost::mpl::at<application::locale_type_list_type, type::locale::message_catalog>::type,
        typename boost::mpl::at<application::traits_type_list_type, type::traits::dialog>::type
    >;


}}