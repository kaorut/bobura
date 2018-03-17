/*! \file
    \brief The definition of bobura::view::timetable::train_number_header.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <bobura/type_list.h>
#include <bobura/view/timetable/train_number_header.h>
#include <bobura/view/timetable/utility.h>


namespace bobura { namespace view { namespace timetable {
    template <typename Traits>
    class operating_distance_header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using string_type = typename traits_type::string_type;

        using canvas_type = typename traits_type::canvas_type;

        using font_type = typename canvas_type::font_type;

        using color_type = typename canvas_type::color_type;

        using position_type = typename canvas_type::position_type;

        using dimension_type = typename canvas_type::dimension_type;


        // constructors and destructor

        impl(string_type description, const font_type& font, const color_type& color)
        : m_description{ std::move(description) }, m_p_font{ &font }, m_p_color{ &color }
        {}

        impl(impl&& another)
        : m_description{ std::move(another.m_description) }, m_p_font{ another.m_p_font }, m_p_color{
              another.m_p_color
          }
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_description = std::move(another.m_description);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;

            return *this;
        }

        void draw_on_impl(canvas_type& canvas, const operating_distance_header& base) const
        {
            canvas.set_line_width(normal_line_width<dimension_unit_type>());
            canvas.set_line_style(canvas_type::line_style_type::solid);
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);

            const auto& left = base.position().left();
            const auto& top = base.position().top();
            const auto& width = base.dimension().width();
            const auto& height = base.dimension().height();
            const auto  right = left + position_unit_type::from(width);
            const auto  bottom = top + position_unit_type::from(height);

            canvas.draw_line(position_type{ right, top }, position_type{ right, bottom });

            const auto  text_dimension = canvas.calc_vertical_text_dimension(m_description);
            const auto& text_width = text_dimension.width();
            const auto& text_height = text_dimension.height();
            const auto  text_left =
                left + (width > text_width ? position_unit_type::from((width - text_width) / 2) : position_unit_type{});
            const auto text_top = top + (height > text_height ? position_unit_type::from((height - text_height) / 2) :
                                                                position_unit_type{});

            canvas.draw_vertical_text(m_description, position_type{ text_left, text_top });
        }


    private:
        // types

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename canvas_type::dimension_unit_type;


        // variables

        string_type m_description;

        const font_type* m_p_font;

        const color_type* m_p_color;
    };


    template <typename Traits>
    operating_distance_header<Traits>::operating_distance_header(
        string_type       description,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension)
    : base_type{}, m_p_impl{ tetengo2::stdalt::make_unique<impl>(std::move(description), font, color) }
    {
        this->set_position(std::move(position));
        this->set_dimension(std::move(dimension));
    }

    template <typename Traits>
    operating_distance_header<Traits>::operating_distance_header(operating_distance_header&& another)
    : base_type{}, m_p_impl{ tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)) }
    {
        this->set_position(std::move(another.position()));
        this->set_dimension(std::move(another.dimension()));
    }

    template <typename Traits>
    operating_distance_header<Traits>::~operating_distance_header() noexcept
    {}

    template <typename Traits>
    operating_distance_header<Traits>& operating_distance_header<Traits>::operator=(operating_distance_header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void operating_distance_header<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas, *this);
    }


    template <typename Traits>
    class train_number_description_header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using string_type = typename traits_type::string_type;

        using canvas_type = typename traits_type::canvas_type;

        using font_type = typename canvas_type::font_type;

        using color_type = typename canvas_type::color_type;

        using position_type = typename canvas_type::position_type;

        using dimension_type = typename canvas_type::dimension_type;


        // constructors and destructor

        impl(string_type description, const font_type& font, const color_type& color)
        : m_description{ std::move(description) }, m_p_font{ &font }, m_p_color{ &color }
        {}

        impl(impl&& another)
        : m_description{ std::move(another.m_description) }, m_p_font{ another.m_p_font }, m_p_color{
              another.m_p_color
          }
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_description = std::move(another.m_description);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;

            return *this;
        }

        void draw_on_impl(canvas_type& canvas, const train_number_description_header& base) const
        {
            canvas.set_line_width(normal_line_width<dimension_unit_type>());
            canvas.set_line_style(canvas_type::line_style_type::solid);
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);

            const auto& left = base.position().left();
            const auto& top = base.position().top();
            const auto& width = base.dimension().width();
            const auto& height = base.dimension().height();
            const auto  right = left + position_unit_type::from(width);
            const auto  bottom = top + position_unit_type::from(height);

            canvas.draw_line(position_type{ left, bottom }, position_type{ right, bottom });

            const auto  text_dimension = canvas.calc_text_dimension(m_description);
            const auto& text_width = text_dimension.width();
            const auto& text_height = text_dimension.height();
            const auto  text_left =
                left + (width > text_width ? position_unit_type::from((width - text_width) / 2) : position_unit_type{});
            const auto text_top = top + (height > text_height ? position_unit_type::from((height - text_height) / 2) :
                                                                position_unit_type{});

            canvas.draw_text(m_description, position_type{ text_left, text_top });
        }


    private:
        // types

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename canvas_type::dimension_unit_type;


        // variables

        string_type m_description;

        const font_type* m_p_font;

        const color_type* m_p_color;
    };


    template <typename Traits>
    train_number_description_header<Traits>::train_number_description_header(
        string_type       description,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension)
    : base_type{}, m_p_impl{ tetengo2::stdalt::make_unique<impl>(std::move(description), font, color) }
    {
        this->set_position(std::move(position));
        this->set_dimension(std::move(dimension));
    }

    template <typename Traits>
    train_number_description_header<Traits>::train_number_description_header(train_number_description_header&& another)
    : base_type{}, m_p_impl{ tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)) }
    {
        this->set_position(std::move(another.position()));
        this->set_dimension(std::move(another.dimension()));
    }

    template <typename Traits>
    train_number_description_header<Traits>::~train_number_description_header() noexcept
    {}

    template <typename Traits>
    train_number_description_header<Traits>& train_number_description_header<Traits>::
                                             operator=(train_number_description_header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void train_number_description_header<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas, *this);
    }


    template <typename Traits>
    class train_name_description_header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using string_type = typename traits_type::string_type;

        using canvas_type = typename traits_type::canvas_type;

        using font_type = typename canvas_type::font_type;

        using color_type = typename canvas_type::color_type;

        using position_type = typename canvas_type::position_type;

        using dimension_type = typename canvas_type::dimension_type;


        // constructors and destructor

        impl(string_type description, const font_type& font, const color_type& color)
        : m_description{ std::move(description) }, m_p_font{ &font }, m_p_color{ &color }
        {}

        impl(impl&& another)
        : m_description{ std::move(another.m_description) }, m_p_font{ another.m_p_font }, m_p_color{
              another.m_p_color
          }
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_description = std::move(another.m_description);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;

            return *this;
        }

        void draw_on_impl(canvas_type& canvas, const train_name_description_header& base) const
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);

            const auto& left = base.position().left();
            const auto& top = base.position().top();
            const auto& width = base.dimension().width();
            const auto& height = base.dimension().height();

            const auto  text_dimension = canvas.calc_vertical_text_dimension(m_description);
            const auto& text_width = text_dimension.width();
            const auto& text_height = text_dimension.height();
            const auto  text_left =
                left + (width > text_width ? position_unit_type::from((width - text_width) / 2) : position_unit_type{});
            const auto text_top = top + (height > text_height ? position_unit_type::from((height - text_height) / 2) :
                                                                position_unit_type{});

            canvas.draw_vertical_text(m_description, position_type{ text_left, text_top });
        }


    private:
        // types

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename canvas_type::dimension_unit_type;


        // variables

        string_type m_description;

        const font_type* m_p_font;

        const color_type* m_p_color;
    };


    template <typename Traits>
    train_name_description_header<Traits>::train_name_description_header(
        string_type       description,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension)
    : base_type{}, m_p_impl{ tetengo2::stdalt::make_unique<impl>(std::move(description), font, color) }
    {
        this->set_position(std::move(position));
        this->set_dimension(std::move(dimension));
    }

    template <typename Traits>
    train_name_description_header<Traits>::train_name_description_header(train_name_description_header&& another)
    : base_type{}, m_p_impl{ tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)) }
    {
        this->set_position(std::move(another.position()));
        this->set_dimension(std::move(another.dimension()));
    }

    template <typename Traits>
    train_name_description_header<Traits>::~train_name_description_header() noexcept
    {}

    template <typename Traits>
    train_name_description_header<Traits>& train_name_description_header<Traits>::
                                           operator=(train_name_description_header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void train_name_description_header<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas, *this);
    }


    template <typename Traits>
    class train_number_header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename canvas_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_type = typename canvas_type::dimension_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using model_type = typename train_number_header::model_type;


        // constructors and destructor

        impl(
            const direction_type /*direction*/,
            const model_type&           model,
            const message_catalog_type& message_catalog,
            canvas_type&                canvas,
            const dimension_type& /*canvas_dimension*/,
            const dimension_type&      margin,
            const position_unit_type&  top,
            const dimension_unit_type& operating_distance_width,
            const dimension_unit_type& station_name_width,
            const dimension_unit_type& train_number_height,
            const dimension_unit_type& train_name_height,
            train_number_header&       base)
        : m_p_operating_distance_header{}, m_p_train_number_description_header{}, m_p_train_name_description_header{},
          m_p_general_color{ &*model.timetable().font_color_set().general().timetable_color() }
        {
            canvas.set_font(*model.timetable().font_color_set().general().timetable_font());

            auto       operating_distance_label = message_catalog.get(TETENGO2_TEXT("Timetable:Operating Distance"));
            const auto operating_distance_label_dimension =
                canvas.calc_vertical_text_dimension(operating_distance_label);
            const auto adjusted_operating_distance_width =
                std::max(operating_distance_width, operating_distance_label_dimension.width());
            const auto adjusted_operating_distance_height = operating_distance_label_dimension.height();

            auto       train_number_description_label = message_catalog.get(TETENGO2_TEXT("Timetable:Train Number"));
            const auto train_number_label_dimension = canvas.calc_text_dimension(train_number_description_label);
            const auto adjusted_train_number_height =
                std::max(train_number_height, train_number_label_dimension.height());

            auto       train_name_description_label = message_catalog.get(TETENGO2_TEXT("Timetable:Train Name"));
            const auto train_name_label_dimension = canvas.calc_vertical_text_dimension(train_name_description_label);
            const auto adjusted_station_name_width = std::max(
                { station_name_width, train_number_label_dimension.width(), train_name_label_dimension.width() });
            const auto adjusted_train_name_height = std::max(train_name_height, train_name_label_dimension.height());

            position_type  operating_distance_position{};
            dimension_type operating_distance_dimension{};
            position_type  train_number_description_position{};
            dimension_type train_number_description_dimension{};
            position_type  train_name_description_position{};
            dimension_type train_name_description_dimension{};
            position_type  position{};
            dimension_type dimension{};
            calculate_positions_and_dimensions(
                margin,
                top,
                adjusted_operating_distance_width,
                adjusted_station_name_width,
                adjusted_operating_distance_height,
                adjusted_train_number_height,
                adjusted_train_name_height,
                operating_distance_position,
                operating_distance_dimension,
                train_number_description_position,
                train_number_description_dimension,
                train_name_description_position,
                train_name_description_dimension,
                position,
                dimension);
            base.set_position(std::move(position));
            base.set_dimension(std::move(dimension));

            m_p_operating_distance_header.reset(
                new operating_distance_header_type{ std::move(operating_distance_label),
                                                    *model.timetable().font_color_set().general().timetable_font(),
                                                    *model.timetable().font_color_set().general().timetable_color(),
                                                    std::move(operating_distance_position),
                                                    std::move(operating_distance_dimension) });

            m_p_train_number_description_header.reset(new train_number_description_header_type{
                std::move(train_number_description_label),
                *model.timetable().font_color_set().general().timetable_font(),
                *model.timetable().font_color_set().general().timetable_color(),
                std::move(train_number_description_position),
                std::move(train_number_description_dimension) });

            m_p_train_name_description_header.reset(
                new train_name_description_header_type{ std::move(train_name_description_label),
                                                        *model.timetable().font_color_set().general().timetable_font(),
                                                        *model.timetable().font_color_set().general().timetable_color(),
                                                        std::move(train_name_description_position),
                                                        std::move(train_name_description_dimension) });
        }

        impl(impl&& another)
        : m_p_operating_distance_header{ std::move(another.m_p_operating_distance_header) },
          m_p_train_number_description_header{ std::move(another.m_p_train_number_description_header) },
          m_p_train_name_description_header{ std::move(another.m_p_train_name_description_header) }, m_p_general_color{
              another.m_p_general_color
          }
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_general_color = another.m_p_general_color;

            return *this;
        }

        void draw_on_impl(canvas_type& canvas, const train_number_header& base) const
        {
            canvas.set_line_width(normal_line_width<dimension_unit_type>());
            canvas.set_line_style(canvas_type::line_style_type::solid);
            canvas.set_color(*m_p_general_color);

            const auto& left = base.position().left();
            const auto& top = base.position().top();
            const auto  right = left + position_unit_type::from(base.dimension().width());
            const auto  bottom = top + position_unit_type::from(base.dimension().height());

            canvas.draw_line(position_type{ left, top }, position_type{ right, top });
            canvas.draw_line(position_type{ left, top }, position_type{ left, bottom });
            canvas.draw_line(position_type{ right, top }, position_type{ right, bottom });

            assert(m_p_operating_distance_header);
            m_p_operating_distance_header->draw_on(canvas);

            assert(m_p_train_number_description_header);
            m_p_train_number_description_header->draw_on(canvas);

            assert(m_p_train_name_description_header);
            m_p_train_name_description_header->draw_on(canvas);
        }


    private:
        // types

        using operating_distance_header_type = operating_distance_header<traits_type>;

        using train_number_description_header_type = train_number_description_header<traits_type>;

        using train_name_description_header_type = train_name_description_header<traits_type>;

        using string_type = typename traits_type::string_type;

        using color_type = typename canvas_type::color_type;


        // static functions

        static void calculate_positions_and_dimensions(
            const dimension_type&      margin,
            const position_unit_type&  top,
            const dimension_unit_type& operating_distance_width,
            const dimension_unit_type& station_name_width,
            const dimension_unit_type& operating_distance_height,
            const dimension_unit_type& train_number_height,
            const dimension_unit_type& train_name_height,
            position_type&             operating_distance_position,
            dimension_type&            operating_distance_dimension,
            position_type&             train_number_description_position,
            dimension_type&            train_number_description_dimension,
            position_type&             train_name_description_position,
            dimension_type&            train_name_description_dimension,
            position_type&             position,
            dimension_type&            dimension)
        {
            auto       left_margin = position_unit_type::from(margin.width());
            const auto left_padding = position_unit_type{ 1 } / 2;
            const auto top_padding = position_unit_type{ 1 } / 2;

            const auto train_number_description_width =
                station_name_width + dimension_unit_type::from(left_padding) * 2;
            auto header_width = operating_distance_width + train_number_description_width;
            auto operating_distance_height_ = operating_distance_height + dimension_unit_type::from(top_padding) * 2;
            auto train_number_description_height = train_number_height + dimension_unit_type::from(top_padding) * 2;
            auto train_name_description_height = train_name_height + dimension_unit_type::from(top_padding) * 2;
            if (train_number_description_height + train_name_description_height < operating_distance_height_)
                train_name_description_height = operating_distance_height_ - train_number_description_height;
            auto header_height =
                std::max(operating_distance_height_, train_number_description_height + train_name_description_height);

            operating_distance_position = position_type{ left_margin, top };
            operating_distance_dimension =
                dimension_type{ operating_distance_width,
                                train_number_description_height + train_name_description_height };

            train_number_description_position =
                position_type{ left_margin + position_unit_type::from(operating_distance_width), top };
            train_number_description_dimension =
                dimension_type{ train_number_description_width, std::move(train_number_description_height) };

            train_name_description_position =
                position_type{ left_margin + position_unit_type::from(operating_distance_width),
                               top + position_unit_type::from(train_number_description_height) };
            train_name_description_dimension =
                dimension_type{ std::move(train_number_description_width), std::move(train_name_description_height) };

            position = position_type{ std::move(left_margin), top };
            dimension = dimension_type{ std::move(header_width), std::move(header_height) };
        }


        // variables

        std::unique_ptr<operating_distance_header_type> m_p_operating_distance_header;

        std::unique_ptr<train_number_description_header_type> m_p_train_number_description_header;

        std::unique_ptr<train_name_description_header_type> m_p_train_name_description_header;

        const color_type* m_p_general_color;
    };


    template <typename Traits>
    train_number_header<Traits>::train_number_header(
        const direction_type        direction,
        const model_type&           model,
        const message_catalog_type& message_catalog,
        canvas_type&                canvas,
        const dimension_type&       canvas_dimension,
        const dimension_type&       margin,
        const position_unit_type&   top,
        const dimension_unit_type&  operating_distance_width,
        const dimension_unit_type&  station_name_width,
        const dimension_unit_type&  train_number_height,
        const dimension_unit_type&  train_name_height)
    : base_type{}, m_p_impl{ tetengo2::stdalt::make_unique<impl>(
                       direction,
                       model,
                       message_catalog,
                       canvas,
                       canvas_dimension,
                       margin,
                       top,
                       operating_distance_width,
                       station_name_width,
                       train_number_height,
                       train_name_height,
                       *this) }
    {}

    template <typename Traits>
    train_number_header<Traits>::train_number_header(train_number_header&& another)
    : base_type{}, m_p_impl{ tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)) }
    {}

    template <typename Traits>
    train_number_header<Traits>::~train_number_header() noexcept
    {}

    template <typename Traits>
    train_number_header<Traits>& train_number_header<Traits>::operator=(train_number_header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void train_number_header<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas, *this);
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class operating_distance_header<typename application::traits_type_list_type::timetable_view_type>;

    template class train_number_description_header<typename application::traits_type_list_type::timetable_view_type>;

    template class train_name_description_header<typename application::traits_type_list_type::timetable_view_type>;

    template class train_number_header<typename application::traits_type_list_type::timetable_view_type>;
#endif

    template class operating_distance_header<typename test::traits_type_list_type::timetable_view_type>;

    template class train_number_description_header<typename test::traits_type_list_type::timetable_view_type>;

    template class train_name_description_header<typename test::traits_type_list_type::timetable_view_type>;

    template class train_number_header<typename test::traits_type_list_type::timetable_view_type>;


}}}
