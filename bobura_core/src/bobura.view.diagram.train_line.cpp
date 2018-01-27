/*! \file
    \brief The definition of bobura::view::diagram::train_line.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/format.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/none.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/range/adaptors.hpp>
#include <boost/rational.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/train_line.h>
#include <bobura/view/diagram/utility.h>


namespace bobura { namespace view { namespace diagram
{
    template <typename Traits>
    class train_line_fragment<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using size_type = typename traits_type::size_type;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename train_line_fragment::position_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using base_type = typename train_line_fragment::base_type;

        using selection_type = typename train_line_fragment::selection_type;

        using train_type = typename train_line_fragment::train_type;


        // constructors and destructor

        impl(
            const train_type&           train,
            const size_type             departure_stop_index,
            selection_type&,
            position_type               departure,
            position_type               arrival,
            const bool                  draw_train_name,
            const message_catalog_type& message_catalog
        )
        :
        m_p_train(&train),
        m_departure_stop_index(departure_stop_index),
        m_departure(std::move(departure)),
        m_arrival(std::move(arrival)),
        m_draw_train_name(draw_train_name),
        m_p_message_catalog(&message_catalog)
        {}

        impl(impl&& another)
        :
        m_p_train(another.m_p_train),
        m_departure_stop_index(another.m_departure_stop_index),
        m_departure(std::move(another.m_departure)),
        m_arrival(std::move(another.m_arrival)),
        m_draw_train_name(another.m_draw_train_name),
        m_p_message_catalog(another.m_p_message_catalog)
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_train = another.m_p_train;
            m_departure_stop_index = another.m_departure_stop_index;
            m_departure = std::move(another.m_departure);
            m_arrival = std::move(another.m_arrival);
            m_draw_train_name = another.m_draw_train_name;
            m_p_message_catalog = another.m_p_message_catalog;

            return *this;
        }

        void draw_on_impl(const train_line_fragment& self, canvas_type& canvas)
        const
        {
            draw_selectable_line(canvas, m_departure, m_arrival, self.selected());
            if (m_draw_train_name)
                draw_train_name(canvas);
        }

        base_type* p_item_by_position_impl(train_line_fragment& self, const position_type& position)
        {
            return
                calculate_distance(position, m_departure, m_arrival) <= selected_line_margin<dimension_unit_type>() ?
                &self : nullptr;
        }

        bool selected_impl(const train_line_fragment& self)
        const
        {
            return
                self.get_selection().selected(*m_p_train, boost::none) ||
                self.get_selection().selected(*m_p_train, boost::make_optional(m_departure_stop_index));
        }

        void select_impl(train_line_fragment& self, const bool switch_selection_style)
        {
            const auto whole_selected = self.get_selection().selected(*m_p_train, boost::none);
            const auto this_fragment_selected =
                self.get_selection().selected(*m_p_train, boost::make_optional(m_departure_stop_index));
            const auto any_fragment_selected =
                self.get_selection().selected(
                    *m_p_train, boost::make_optional(std::numeric_limits<size_type>::max())
                );

            auto select_fragment = false;
            if (switch_selection_style)
                select_fragment = whole_selected || (!this_fragment_selected && any_fragment_selected);
            else
                select_fragment = this_fragment_selected;
            self.get_selection().select(
                *m_p_train, boost::make_optional(select_fragment, m_departure_stop_index)
            );
        }


    private:
        // types

        using string_type = typename traits_type::string_type;

        using direction_type = typename train_type::direction_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_type = typename canvas_type::dimension_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using geo_vector_type = std::pair<double, double>;


        // static functions

        static string_type make_train_name(const train_type& train, const message_catalog_type& message_catalog)
        {
            std::basic_ostringstream<typename string_type::value_type> name;

            name << train.number();
            name << string_type{ TETENGO2_TEXT(" ") };
            if (train.name_number().empty())
            {
                name << train.name();
            }
            else
            {
                name <<
                    boost::basic_format<typename string_type::value_type>(
                        message_catalog.get(TETENGO2_TEXT("Diagram:%1% No. %2%"))
                    ) % train.name() % train.name_number();
            }

            return name.str();
        }

        static double calculate_train_name_angle(const position_type& departure, const position_type& arrival)
        {
            const auto height = arrival.top() - departure.top();
            const auto width = arrival.left() - departure.left();

            return
                std::atan2(boost::rational_cast<double>(height.value()), boost::rational_cast<double>(width.value()));
        }

        static position_type calculate_train_name_position(
            const position_type& departure,
            const string_type&   train_name,
            const double         angle,
            const direction_type direction,
            const canvas_type&   canvas
        )
        {
            const auto text_dimension = canvas.calc_text_dimension(train_name);
            const auto& text_height = text_dimension.height();

            if (direction == direction_type::down)
            {
                if (
                    -boost::math::constants::pi<double>() / 8 < angle &&
                    angle < boost::math::constants::pi<double>() / 8
                )
                {
                    return { departure.left(), departure.top() - text_height };
                }
                else
                {
                    const auto left_diff = boost::rational_cast<double>(text_height.value()) / std::sin(angle);
                    const auto left =
                        departure.left() +
                        typename position_unit_type::value_type{
                            static_cast<typename position_unit_type::value_type::int_type>(left_diff * 0x10000),
                            0x10000
                        };

                    return { left, departure.top() };
                }
            }
            else
            {
                const auto left_diff = boost::rational_cast<double>(text_height.value()) * std::sin(angle);
                const auto left =
                    departure.left() +
                    typename position_unit_type::value_type{
                        static_cast<typename position_unit_type::value_type::int_type>(left_diff * 0x10000), 0x10000
                    };

                const auto top_diff = boost::rational_cast<double>(text_height.value()) * std::cos(angle);
                const auto top =
                    departure.top() -
                    typename position_unit_type::value_type{
                        static_cast<typename position_unit_type::value_type::int_type>(top_diff * 0x10000), 0x10000
                    };

                return { left, top };
            }
        }

        static dimension_unit_type calculate_distance(
            const position_type& point,
            const position_type& line_segment_begin,
            const position_type& line_segment_end
        )
        {
            const auto p = to_geo_vector(point);
            const auto lsb = to_geo_vector(line_segment_begin);
            const auto lse = to_geo_vector(line_segment_end);

            auto d = 0.0;
            if      (geo_dot(geo_minus(lse, lsb), geo_minus(p, lsb)) < 0.0)
                d = geo_abs(geo_minus(p, lsb));
            else if (geo_dot(geo_minus(lsb, lse), geo_minus(p, lse)) < 0.0)
                d = geo_abs(geo_minus(p, lse));
            else
                d = std::abs(geo_cross(geo_minus(lse, lsb), geo_minus(p, lsb))) / geo_abs(geo_minus(lse, lsb));

            return to_size(d);
        }

        static geo_vector_type to_geo_vector(const position_type& position)
        {
            return
                {
                    boost::rational_cast<double>(position.left().value()),
                    boost::rational_cast<double>(position.top().value())
                };
        }

        static dimension_unit_type to_size(const double value)
        {
            return
                dimension_unit_type{
                    typename dimension_unit_type::value_type{
                        static_cast<typename dimension_unit_type::value_type::int_type>(value * 256.0), 256
                    }
                };
        }

        static geo_vector_type geo_minus(const geo_vector_type& v1, const geo_vector_type& v2)
        {
            return { v1.first - v2.first, v1.second - v2.second };
        }

        static double geo_abs(const geo_vector_type& v)
        {
            return std::sqrt(v.first * v.first + v.second * v.second);
        }

        static double geo_dot(const geo_vector_type& v1, const geo_vector_type& v2)
        {
            return v1.first * v2.first + v1.second * v2.second;
        }

        static double geo_cross(const geo_vector_type& v1, const geo_vector_type& v2)
        {
            return v1.first * v2.second - v1.second * v2.first;
        }


        // variables

        const train_type* m_p_train;

        size_type m_departure_stop_index;

        position_type m_departure;

        position_type m_arrival;

        bool m_draw_train_name;

        const message_catalog_type* m_p_message_catalog;


        // functions

        void draw_train_name(canvas_type& canvas)
        const
        {
            const auto train_name = make_train_name(*m_p_train, *m_p_message_catalog);
            const auto train_name_angle = calculate_train_name_angle(m_departure, m_arrival);
            canvas.draw_text(
                train_name,
                calculate_train_name_position(
                    m_departure, train_name, train_name_angle, m_p_train->direction(), canvas
                ),
                train_name_angle
            );
        }


    };


    template <typename Traits>
    train_line_fragment<Traits>::train_line_fragment(
        const train_type&           train,
        const size_type             departure_stop_index,
        selection_type&             selection,
        position_type               departure,
        position_type               arrival,
        const bool                  draw_train_name,
        const message_catalog_type& message_catalog
    )
    :
    base_type(selection),
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            train,
            departure_stop_index,
            selection,
            std::move(departure),
            std::move(arrival),
            draw_train_name,
            message_catalog
        )
    )
    {}

    template <typename Traits>
    train_line_fragment<Traits>::train_line_fragment(train_line_fragment&& another)
    :
    base_type(another.get_selection()),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    train_line_fragment<Traits>::~train_line_fragment()
    noexcept
    {}

    template <typename Traits>
    train_line_fragment<Traits>& train_line_fragment<Traits>::operator=(train_line_fragment&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void train_line_fragment<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(*this, canvas);
    }

    template <typename Traits>
    typename train_line_fragment<Traits>::base_type* train_line_fragment<Traits>::p_item_by_position_impl(
        const position_type& position
    )
    {
        return m_p_impl->p_item_by_position_impl(*this, position);
    }

    template <typename Traits>
    bool train_line_fragment<Traits>::selected_impl()
    const
    {
        return m_p_impl->selected_impl(*this);
    }

    template <typename Traits>
    void train_line_fragment<Traits>::select_impl(const bool switch_selection_style)
    {
        m_p_impl->select_impl(*this, switch_selection_style);
    }


    template <typename Traits>
    class train_line<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using scale_type = typename traits_type::scale_type;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename train_line::position_type;

        using position_unit_type = typename train_line::position_unit_type;

        using dimension_type = typename train_line::dimension_type;

        using dimension_unit_type = typename train_line::dimension_unit_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using base_type = typename train_line::base_type;

        using selection_type = typename train_line::selection_type;

        using train_type = typename train_line::train_type;

        using time_span_type = typename train_line::time_span_type;

        using train_kind_type = typename train_line::train_kind_type;

        using station_intervals_type = typename train_line::station_intervals_type;


        // constructors and destructor

        impl(
            const train_type&                      train,
            const train_kind_type&                 train_kind,
            const time_span_type&                  time_offset,
            selection_type&                        selection,
            const dimension_type&                  canvas_dimension,
            const position_type&                   scroll_bar_position,
            const position_unit_type&              station_header_right,
            const position_unit_type&              header_bottom,
            const dimension_unit_type&             time_header_height,
            const scale_type&                      horizontal_scale,
            const station_intervals_type&          station_intervals,
            const std::vector<position_unit_type>& station_positions,
            const message_catalog_type&            message_catalog
        )
        :
        m_p_train_kind(&train_kind),
        m_fragments(
            make_fragments(
                train,
                time_offset,
                selection,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                station_intervals,
                station_positions,
                message_catalog
            )
        )
        {}

        impl(impl&& another)
        :
        m_p_train_kind(another.m_p_train_kind),
        m_fragments(std::move(another.m_fragments))
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_train_kind = another.m_p_train_kind;
            m_fragments = std::move(another.m_fragments);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_font(m_p_train_kind->diagram_font());
            canvas.set_color(m_p_train_kind->diagram_color());
            canvas.set_line_width(
                m_p_train_kind->diagram_line_weight() == train_kind_type::weight_type::bold ?
                bold_line_width<dimension_unit_type>() : normal_line_width<dimension_unit_type>()
            );
            canvas.set_line_style(translate_line_style(m_p_train_kind->diagram_line_style()));

            for (const auto& fragment: m_fragments)
                fragment.draw_on(canvas);
        }

        base_type* p_item_by_position_impl(const position_type& position)
        {
            for (auto& fragment: boost::adaptors::reverse(m_fragments))
            {
                auto* const p_item = fragment.p_item_by_position(position);
                if (p_item)
                    return p_item;
            }

            return nullptr;
        }


    private:
        // types

        using size_type = typename traits_type::size_type;

        using time_type = typename train_line::time_type;

        using train_line_fragment_type = train_line_fragment<traits_type>;

        using direction_type = typename train_type::direction_type;

        using stop_type = typename train_type::stop_type;


        // static functions

        static std::vector<train_line_fragment_type> make_fragments(
            const train_type&                      train,
            const time_span_type&                  time_offset,
            selection_type&                        selection,
            const dimension_type&                  canvas_dimension,
            const position_type&                   scroll_bar_position,
            const position_unit_type&              station_header_right,
            const position_unit_type&              header_bottom,
            const dimension_unit_type&             time_header_height,
            const scale_type&                      horizontal_scale,
            const station_intervals_type&          station_intervals,
            const std::vector<position_unit_type>& station_positions,
            const message_catalog_type&            message_catalog
        )
        {
            std::vector<train_line_fragment_type> fragments{};

            auto train_name_drawn = false;
            if (train.direction() == direction_type::down)
            {
                for (size_type i = 0; i + 1 < train.stops().size(); )
                {
                    const auto from = i;

                    if (!has_time(train.stops()[from]))
                    {
                        ++i;
                        continue;
                    }

                    auto j = i + 1;
                    for (; j < train.stops().size(); ++j)
                    {
                        const auto to = j;

                        if (has_time(train.stops()[to]))
                        {
                            const auto& departure_time = get_departure_time(train.stops()[from]);
                            const auto arrival_time =
                                estimate_arrival_time(station_intervals, departure_time, train.stops()[to], from, to);

                            make_fragment(
                                train,
                                from,
                                departure_time,
                                to,
                                arrival_time,
                                !train_name_drawn,
                                time_offset,
                                selection,
                                canvas_dimension,
                                scroll_bar_position,
                                station_header_right,
                                header_bottom,
                                time_header_height,
                                horizontal_scale,
                                station_positions,
                                message_catalog,
                                fragments
                            );

                            if (!train_name_drawn)
                                train_name_drawn = true;

                            break;
                        }
                    }

                    i = j;
                }
            }
            else
            {
                for (size_type i = train.stops().size(); i > 1; )
                {
                    const auto from = i - 1;

                    if (!has_time(train.stops()[from]))
                    {
                        --i;
                        continue;
                    }

                    auto j = i - 1;
                    for (; j > 0; --j)
                    {
                        const auto to = j - 1;

                        if (has_time(train.stops()[to]))
                        {
                            const auto& departure_time = get_departure_time(train.stops()[from]);
                            const auto arrival_time =
                                estimate_arrival_time(station_intervals, departure_time, train.stops()[to], to, from);

                            make_fragment(
                                train,
                                from,
                                departure_time,
                                to,
                                arrival_time,
                                !train_name_drawn ,
                                time_offset,
                                selection,
                                canvas_dimension,
                                scroll_bar_position,
                                station_header_right,
                                header_bottom,
                                time_header_height,
                                horizontal_scale,
                                station_positions,
                                message_catalog,
                                fragments
                            );

                            if (!train_name_drawn)
                                train_name_drawn = true;

                            break;
                        }
                    }

                    i = j;
                }
            }

            return std::move(fragments);
        }

        static bool has_time(const stop_type& stop)
        {
            return stop.arrival().initialized() || stop.departure().initialized();
        }

        static const time_type& get_departure_time(const stop_type& stop)
        {
            assert(has_time(stop));
            if (stop.departure().initialized())
                return stop.departure();
            else
                return stop.arrival();
        }

        static time_type estimate_arrival_time(
            const station_intervals_type& station_intervals,
            const time_type&              from_departure,
            const stop_type&              to_stop,
            const size_type               upper_stop_index,
            const size_type               lower_stop_index
        )
        {
            if (to_stop.arrival().initialized())
                return to_stop.arrival();

            const auto departure_interval = to_stop.departure() - from_departure;
            const auto travel_time =
                std::accumulate(
                    station_intervals.begin() + upper_stop_index,
                    station_intervals.begin() + lower_stop_index,
                    time_span_type{ 0 }
                );

            return departure_interval < travel_time ? to_stop.departure() : from_departure + travel_time;
        }

        static void make_fragment(
            const train_type&                      train,
            const size_type                        departure_stop_index,
            const time_type&                       departure_time,
            const size_type                        arrival_stop_index,
            const time_type&                       arrival_time,
            const bool                             draw_train_name,
            const time_span_type&                  time_offset,
            selection_type&                        selection,
            const dimension_type&                  canvas_dimension,
            const position_type&                   scroll_bar_position,
            const position_unit_type&              station_header_right,
            const position_unit_type&              header_bottom,
            const dimension_unit_type&             time_header_height,
            const scale_type&                      horizontal_scale,
            const std::vector<position_unit_type>& station_positions,
            const message_catalog_type&            message_catalog,
            std::vector<train_line_fragment_type>& fragments
        )
        {
            if (departure_time - time_offset <= arrival_time - time_offset)
            {
                make_fragment_impl(
                    train,
                    departure_stop_index,
                    departure_time,
                    false,
                    arrival_stop_index,
                    arrival_time,
                    false,
                    draw_train_name,
                    time_offset,
                    selection,
                    canvas_dimension,
                    scroll_bar_position,
                    station_header_right,
                    header_bottom,
                    time_header_height,
                    horizontal_scale,
                    station_positions,
                    message_catalog,
                    fragments
                );
            }
            else
            {
                make_fragment_impl(
                    train,
                    departure_stop_index,
                    departure_time,
                    true,
                    arrival_stop_index,
                    arrival_time,
                    false,
                    draw_train_name,
                    time_offset,
                    selection,
                    canvas_dimension,
                    scroll_bar_position,
                    station_header_right,
                    header_bottom,
                    time_header_height,
                    horizontal_scale,
                    station_positions,
                    message_catalog,
                    fragments
                );
                make_fragment_impl(
                    train,
                    departure_stop_index,
                    departure_time,
                    false,
                    arrival_stop_index,
                    arrival_time,
                    true,
                    draw_train_name,
                    time_offset,
                    selection,
                    canvas_dimension,
                    scroll_bar_position,
                    station_header_right,
                    header_bottom,
                    time_header_height,
                    horizontal_scale,
                    station_positions,
                    message_catalog,
                    fragments
                );
            }
        }

        static void make_fragment_impl(
            const train_type&                      train,
            const size_type                        departure_stop_index,
            const time_type&                       departure_time,
            const bool                             previous_day_departure,
            const size_type                        arrival_stop_index,
            const time_type&                       arrival_time,
            const bool                             next_day_arrival,
            const bool                             draw_train_name,
            const time_span_type&                  time_offset,
            selection_type&                        selection,
            const dimension_type&                  canvas_dimension,
            const position_type&                   scroll_bar_position,
            const position_unit_type&              station_header_right,
            const position_unit_type&              header_bottom,
            const dimension_unit_type&             time_header_height,
            const scale_type&                      horizontal_scale,
            const std::vector<position_unit_type>& station_positions,
            const message_catalog_type&            message_catalog,
            std::vector<train_line_fragment_type>& fragments
        )
        {
            const auto& horizontal_scroll_bar_position = scroll_bar_position.left();
            const auto& vertical_scroll_bar_position = scroll_bar_position.top();

            const auto horizontal_scale_left = position_unit_type::from(dimension_unit_type{ horizontal_scale });
            const auto time_header_bottom = position_unit_type::from(time_header_height);
            position_type departure{
                time_to_left(
                    departure_time,
                    time_offset,
                    previous_day_departure ? -1 : 0,
                    horizontal_scroll_bar_position,
                    station_header_right,
                    horizontal_scale_left
                ),
                station_index_to_top(
                    station_positions,
                    departure_stop_index,
                    vertical_scroll_bar_position,
                    header_bottom,
                    time_header_bottom
                )
            };
            position_type arrival{
                time_to_left(
                    arrival_time,
                    time_offset,
                    next_day_arrival ? 1 : 0,
                    horizontal_scroll_bar_position,
                    station_header_right,
                    horizontal_scale_left
                ),
                station_index_to_top(
                    station_positions,
                    arrival_stop_index,
                    vertical_scroll_bar_position,
                    header_bottom,
                    time_header_bottom
                )
            };
            
            const auto& left_bound = departure.left();
            if (left_bound > position_unit_type::from(canvas_dimension.width()))
                return;
            const auto& right_bound = arrival.left();
            if (right_bound < station_header_right)
                return;
            const auto& upper_bound = departure_stop_index < arrival_stop_index ? departure.top() : arrival.top();
            if (upper_bound > position_unit_type::from(canvas_dimension.height()))
                return;
            const auto& lower_bound = departure_stop_index < arrival_stop_index ? arrival.top() : departure.top();
            if (lower_bound < header_bottom + time_header_bottom)
                return;

            fragments.emplace_back(
                train,
                departure_stop_index,
                selection,
                std::move(departure),
                std::move(arrival),
                draw_train_name,
                message_catalog
            );
        }

        static typename canvas_type::line_style_type translate_line_style(
            const typename train_kind_type::line_style_type line_style
        )
        {
            switch (line_style)
            {
            case train_kind_type::line_style_type::solid:
                return canvas_type::line_style_type::solid;
            case train_kind_type::line_style_type::dashed:
                return canvas_type::line_style_type::dashed;
            case train_kind_type::line_style_type::dotted:
                return canvas_type::line_style_type::dotted;
            case train_kind_type::line_style_type::dot_dashed:
                return canvas_type::line_style_type::dot_dashed;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown line style."));
            }
        }


        // variables

        const train_kind_type* m_p_train_kind;

        std::vector<train_line_fragment_type> m_fragments;


    };


    template <typename Traits>
    train_line<Traits>::train_line(
        const train_type&                      train,
        const train_kind_type&                 train_kind,
        const time_span_type&                  time_offset,
        selection_type&                        selection,
        const dimension_type&                  canvas_dimension,
        const position_type&                   scroll_bar_position,
        const position_unit_type&              station_header_right,
        const position_unit_type&              header_bottom,
        const dimension_unit_type&             time_header_height,
        const scale_type&                      horizontal_scale,
        const station_intervals_type&          station_intervals,
        const std::vector<position_unit_type>& station_positions,
        const message_catalog_type&            message_catalog
    )
    :
    base_type(selection),
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            train,
            train_kind,
            time_offset,
            selection,
            canvas_dimension,
            scroll_bar_position,
            station_header_right,
            header_bottom,
            time_header_height,
            horizontal_scale,
            station_intervals,
            station_positions,
            message_catalog
        )
    )
    {}

    template <typename Traits>
    train_line<Traits>::train_line(train_line&& another)
    :
    base_type(another.get_selection()),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    train_line<Traits>::~train_line()
    noexcept
    {}

    template <typename Traits>
    train_line<Traits>& train_line<Traits>::operator=(train_line&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void train_line<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        return m_p_impl->draw_on_impl(canvas);
    }

    template <typename Traits>
    typename train_line<Traits>::base_type* train_line<Traits>::p_item_by_position_impl(const position_type& position)
    {
        return m_p_impl->p_item_by_position_impl(position);
    }


    template <typename Traits>
    class train_line_list<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using scale_type = typename traits_type::scale_type;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename train_line_list::position_type;

        using position_unit_type = typename train_line_list::position_unit_type;

        using dimension_type = typename train_line_list::dimension_type;

        using dimension_unit_type = typename train_line_list::dimension_unit_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using base_type = typename train_line_list::base_type;

        using selection_type = typename train_line_list::selection_type;

        using model_type = typename train_line_list::model_type;

        using time_span_type = typename train_line_list::time_span_type;

        using station_intervals_type = typename train_line_list::station_intervals_type;


        // constructors and destructor

        impl(
            const model_type&                      model,
            const time_span_type&                  time_offset,
            selection_type&                        selection,
            const dimension_type&                  canvas_dimension,
            const position_type&                   scroll_bar_position,
            const position_unit_type&              station_header_right,
            const position_unit_type&              header_bottom,
            const dimension_unit_type&             time_header_height,
            const scale_type&                      horizontal_scale,
            const station_intervals_type&          station_intervals,
            const std::vector<position_unit_type>& station_positions,
            const message_catalog_type&            message_catalog
        )
        :
        m_train_lines(
            make_train_lines(
                model,
                time_offset,
                selection,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                station_intervals,
                station_positions,
                message_catalog
            )
        )
        {}

        impl(impl&& another)
        :
        m_train_lines(std::move(another.m_train_lines))
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_train_lines = std::move(another.m_train_lines);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            for (const auto& train_line: m_train_lines)
                train_line.draw_on(canvas);
        }

        base_type* p_item_by_position_impl(const position_type& position)
        {
            for (auto& train_line: boost::adaptors::reverse(m_train_lines))
            {
                auto* const p_item = train_line.p_item_by_position(position);
                if (p_item)
                    return p_item;
            }

            return nullptr;
        }


    private:
        // types

        using font_type = typename train_line_list::font_type;

        using train_line_type = train_line<traits_type>;

        using timetable_type = typename model_type::timetable_type;

        using trains_type = typename timetable_type::trains_type;

        using train_type = typename timetable_type::train_type;

        using train_kinds_type = typename timetable_type::train_kinds_type;

        using train_kind_type = typename timetable_type::train_kind_type;

        using font_color_set_type = typename timetable_type::font_color_set_type;


        // static functions

        std::vector<train_line_type> make_train_lines(
            const model_type&                       model,
            const time_span_type&                   time_offset,
            selection_type&                         selection,
            const dimension_type&                   canvas_dimension,
            const position_type&                    scroll_bar_position,
            const position_unit_type&               station_header_right,
            const position_unit_type&               header_bottom,
            const dimension_unit_type&              time_header_height,
            const scale_type&                       horizontal_scale,
            const station_intervals_type&           station_intervals,
            const std::vector<position_unit_type>&  station_positions,
            const message_catalog_type&             message_catalog
        )
        {
            std::vector<train_line_type> train_lines{};

            make_train_lines_impl(
                model.timetable().down_trains(),
                model.timetable().train_kinds(),
                time_offset,
                selection,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                station_intervals,
                station_positions,
                message_catalog,
                train_lines
            );
            make_train_lines_impl(
                model.timetable().up_trains(),
                model.timetable().train_kinds(),
                time_offset,
                selection,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                station_intervals,
                station_positions,
                message_catalog,
                train_lines
            );

            return std::move(train_lines);
        }

        void make_train_lines_impl(
            const trains_type&                     trains,
            const train_kinds_type&                train_kinds,
            const time_span_type&                  time_offset,
            selection_type&                        selection,
            const dimension_type&                  canvas_dimension,
            const position_type&                   scroll_bar_position,
            const position_unit_type&              station_header_right,
            const position_unit_type&              header_bottom,
            const dimension_unit_type&             time_header_height,
            const scale_type&                      horizontal_scale,
            const station_intervals_type&          station_intervals,
            const std::vector<position_unit_type>& station_positions,
            const message_catalog_type&            message_catalog,
            std::vector<train_line_type>&          train_lines
        )
        {
            for (const auto& train: trains)
            {
                train_lines.emplace_back(
                    train,
                    train_kinds[train.kind_index()],
                    time_offset,
                    selection,
                    canvas_dimension,
                    scroll_bar_position,
                    station_header_right,
                    header_bottom,
                    time_header_height,
                    horizontal_scale,
                    station_intervals,
                    station_positions,
                    message_catalog
                );
            }
        }


        // variables

        std::vector<train_line_type> m_train_lines;


    };


    template <typename Traits>
    train_line_list<Traits>::train_line_list(
        const model_type&             model,
        const time_span_type&         time_offset,
        selection_type&               selection,
        const dimension_type&         canvas_dimension,
        const position_type&          scroll_bar_position,
        const position_unit_type&              station_header_right,
        const position_unit_type&               header_bottom,
        const dimension_unit_type&            time_header_height,
        const scale_type&             horizontal_scale,
        const station_intervals_type& station_intervals,
        const std::vector<position_unit_type>&  station_positions,
        const message_catalog_type&   message_catalog
    )
    :
    base_type(selection),
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            model,
            time_offset,
            selection,
            canvas_dimension,
            scroll_bar_position,
            station_header_right,
            header_bottom,
            time_header_height,
            horizontal_scale,
            station_intervals,
            station_positions,
            message_catalog
        )
    )
    {}

    template <typename Traits>
    train_line_list<Traits>::train_line_list(train_line_list&& another)
    :
    base_type(another.get_selection()),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    train_line_list<Traits>::~train_line_list()
    noexcept
    {}

    template <typename Traits>
    train_line_list<Traits>& train_line_list<Traits>::operator=(train_line_list&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void train_line_list<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(canvas);
    }

    template <typename Traits>
    typename train_line_list<Traits>::base_type* train_line_list<Traits>::p_item_by_position_impl(
        const position_type& position
    )
    {
        return m_p_impl->p_item_by_position_impl(position);
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
    template class train_line_fragment<typename application::traits_type_list_type::diagram_view_type>;

    template class train_line<typename application::traits_type_list_type::diagram_view_type>;

    template class train_line_list<typename application::traits_type_list_type::diagram_view_type>;
#endif

    template class train_line_fragment<typename test::traits_type_list_type::diagram_view_type>;

    template class train_line<typename test::traits_type_list_type::diagram_view_type>;

    template class train_line_list<typename test::traits_type_list_type::diagram_view_type>;


}}}
