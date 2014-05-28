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

#include <boost/optional.hpp>

#include <tetengo2.h>

#include <bobura/command/train_kind.h>


namespace bobura { namespace command
{
    class train_kind::impl
    {
    public:
        // types

        using model_type = train_kind::model_type;

        using abstract_window_type = train_kind::abstract_window_type;

        using train_kind_dialog_type = train_kind::train_kind_dialog_type;

        using dialog_base_type = train_kind::dialog_base_type;

        using message_catalog_type = train_kind::message_catalog_type;


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
            train_kind_dialog_type dialog(
                parent, m_message_catalog, font_color_set.train_name(), font_color_set.background()
            );

            auto info_sets = to_info_sets(model.timetable());
            dialog.set_info_sets(std::move(info_sets));

            dialog.do_modal();
            if (dialog.result() != dialog_base_type::result_type::accepted)
                return;
        
            model.timetable().assign_train_kinds(
                to_train_kinds(dialog.info_sets()),
                to_train_kind_index_map(dialog.info_sets(), model.timetable().train_kinds().size())
            );
        }


    private:
        // types

        using int_size_type = train_kind_dialog_type::int_size_type;

        using info_set_type = train_kind_dialog_type::info_set_type;

        using timetable_type = model_type::timetable_type;

        using train_kinds_type = timetable_type::train_kinds_type;

        using train_kind_index_type = timetable_type::train_kind_index_type;

        using train_kind_type = timetable_type::train_kind_type;

        using font_color_set_type = timetable_type::font_color_set_type;


        // static functions

        static std::vector<info_set_type> to_info_sets(const timetable_type& timetable)
        {
            std::vector<info_set_type> info_sets{};
            info_sets.reserve(timetable.train_kinds().size());

            for (auto i = timetable.train_kinds().begin(); i != timetable.train_kinds().end(); ++i)
            {
                const int_size_type index = std::distance(timetable.train_kinds().begin(), i);
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


    train_kind::train_kind(const message_catalog_type& message_catalog)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(message_catalog))
    {}

    train_kind::~train_kind()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    void train_kind::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
