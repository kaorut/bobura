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

#include <bobura/basic_type_list.h>
#include <bobura/command/train_kind.h>
#include <bobura/command/traits.h>
#include <bobura/model/train_kind.h>
#include <bobura/train_kind_dialog.h>


namespace bobura { namespace command
{
    template <typename Traits, typename Dialog, typename Color, typename MessageCatalog>
    class train_kind<Traits, Dialog, Color, MessageCatalog>::impl
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

        using message_catalog_type = typename train_kind::message_catalog_type;

        using train_kind_dialog_type =
            train_kind_dialog<
                size_type,
                dialog_type,
                model::train_kind<string_type>,
                font_type, color_type,
                message_catalog_type
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


    template <typename Traits, typename Dialog, typename Color, typename MessageCatalog>
    train_kind<Traits, Dialog, Color, MessageCatalog>::train_kind(const message_catalog_type& message_catalog)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(message_catalog))
    {}

    template <typename Traits, typename Dialog, typename Color, typename MessageCatalog>
    train_kind<Traits, Dialog, Color, MessageCatalog>::~train_kind()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename Dialog, typename Color, typename MessageCatalog>
    void train_kind<Traits, Dialog, Color, MessageCatalog>::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class train_kind<
        traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type
        >,
        typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
        typename boost::mpl::at<ui_type_list, type::ui::color>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
    >;


}}
