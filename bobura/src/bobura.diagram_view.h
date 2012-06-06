/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMVIEW_H)
#define BOBURA_DIAGRAMVIEW_H

//#include <utility>

#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/rational.hpp>

#include <tetengo2.gui.measure.h>


namespace bobura
{
   /*!
        \brief The class template for a diagram view.

        \tparam Model           A model type.
        \tparam Canvas          A canvas type.
        \tparam SolidBackground A solid background type.
    */
    template <typename Model, typename Canvas, typename SolidBackground>
    class diagram_view : private boost::noncopyable
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The size type.
        typedef typename canvas_type::size_type size_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The dimension type.
        typedef typename canvas_type::dimension_type dimension_type;

        //! The string type.
        typedef typename canvas_type::string_type string_type;

        //! The solid background type.
        typedef SolidBackground solid_background_type;


        // constructors and destructor

        /*!
            \brief Creates a diagram view.

            \param model A model.
        */
        explicit diagram_view(const model_type& model)
        :
        m_model(model),
        m_station_header_width(8),
        m_time_header_height(3),
        m_station_positions()
        {}


        // functions

        /*!
            \brief Draws the view.

            \param canvas              A canvas.
            \param canvas_dimension    A canvas dimension.
            \param scroll_bar_position A scroll bar position.
        */
        void draw_to(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        const
        {
            clear_background(canvas, canvas_dimension);

            draw_header(canvas);
            draw_time_lines(
                canvas, canvas_dimension, tetengo2::gui::position<position_type>::left(scroll_bar_position)
            );
            draw_frames(canvas, canvas_dimension);
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        dimension_type dimension()
        const
        {
            return dimension_type(width_type(20 * 24), height_type(48));
        }

        /*!
            \brief Returns the page size.

            \param canvas_dimension A canvas dimension.

            \return The page size.
        */
        dimension_type page_size(const dimension_type& canvas_dimension)
        const
        {
            const width_type canvas_width = tetengo2::gui::dimension<dimension_type>::width(canvas_dimension);
            const width_type page_width =
                canvas_width > m_station_header_width ? canvas_width - m_station_header_width : width_type(0);

            const height_type canvas_height = tetengo2::gui::dimension<dimension_type>::height(canvas_dimension);
            const height_type page_height =
                canvas_height > m_time_header_height ? canvas_height - m_time_header_height : height_type(0);

            return dimension_type(std::move(page_width), std::move(page_height));
        }

        /*!
            \brief Updates the station positions.
        */
        void update_station_positions()
        {
            station_intervals_type intervals = m_model.timetable().station_intervals();
            
            std::vector<height_type> positions;
            positions.reserve(intervals.size());
            std::transform(intervals.begin(), intervals.end(), std::back_inserter(positions), to_station_position);

            m_station_positions = std::move(positions);
        }


    private:
        // types

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename solid_background_type::color_type color_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename model_type::timetable_type::station_interval_type station_interval_type;

        typedef typename model_type::timetable_type::station_intervals_type station_intervals_type;


        // static functions

        template <typename To, typename From>
        static To to_rational(const From& from)
        {
            return To(typename To::value_type(from.value().numerator(), from.value().denominator()));
        }

        static height_type to_station_position(const station_interval_type& interval)
        {
            return height_type(interval);
        }


        // variables

        const model_type& m_model;

        width_type m_station_header_width;

        height_type m_time_header_height;

        std::vector<height_type> m_station_positions;


        // functions

        void clear_background(canvas_type& canvas, const dimension_type& canvas_dimension)
        const
        {
            canvas.set_background(tetengo2::make_unique<const solid_background_type>(color_type(255, 255, 255)));
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), canvas_dimension);
        }

        void draw_header(canvas_type& canvas)
        const
        {
            canvas.set_color(color_type(0x00, 0x00, 0x00, 0xFF));

            canvas.draw_text(m_model.timetable().title(), position_type(left_type(0), top_type(0)));
        }

        void draw_time_lines(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const left_type&      horizontal_scroll_bar_position
        )
        const
        {
            const left_type canvas_right =
                to_rational<left_type>(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension));
            const top_type canvas_bottom =
                to_rational<top_type>(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension));

            canvas.set_color(color_type(0x80, 0x80, 0x80, 0xFF));

            typedef typename left_type::value_type::int_type left_int_type;
            const left_int_type int_scroll_position =
                boost::rational_cast<left_int_type>(horizontal_scroll_bar_position.value());
            const left_int_type int_left = int_scroll_position % 20;
            const left_int_type first_visible_hour = int_scroll_position / 20 + (int_left > 0 ? 1 : 0);
            left_int_type hour = first_visible_hour;
            for (
                left_type position = to_rational<left_type>(m_station_header_width) - left_type(int_left);
                position < canvas_right;
                position += left_type(20)
            )
            {
                if (position < to_rational<left_type>(m_station_header_width))
                    continue;

                canvas.draw_line(
                    position_type(position, top_type(1)),
                    position_type(position, canvas_bottom),
                    size_type(typename size_type::value_type(1, 12))
                );

                canvas.draw_text(boost::lexical_cast<string_type>(hour % 24), position_type(position, top_type(1)));
                ++hour;
            }

        }

        void draw_frames(canvas_type& canvas, const dimension_type& canvas_dimension)
        const
        {
            const left_type canvas_right =
                to_rational<left_type>(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension));
            const top_type canvas_bottom =
                to_rational<top_type>(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension));

            canvas.set_color(color_type(0x80, 0x80, 0x80, 0xFF));

            canvas.draw_line(
                position_type(left_type(0), to_rational<top_type>(m_time_header_height)),
                position_type(canvas_right, to_rational<top_type>(m_time_header_height)),
                size_type(typename size_type::value_type(1, 6))
            );
            canvas.draw_line(
                position_type(to_rational<left_type>(m_station_header_width), top_type(0)),
                position_type(to_rational<left_type>(m_station_header_width), canvas_bottom),
                size_type(typename size_type::value_type(1, 8))
            );
        }


    };


}

#endif
