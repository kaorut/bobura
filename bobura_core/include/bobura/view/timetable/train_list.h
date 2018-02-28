/*! \file
    \brief The definition of bobura::view::timetable::train_list.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_TIMETABLE_TRAINLIST_H)
#define BOBURA_VIEW_TIMETABLE_TRAINLIST_H

#include <memory>

#include <bobura/timetable_model.h>
#include <bobura/view/timetable/item.h>
#include <bobura/view/timetable/utility.h>


namespace bobura { namespace view { namespace timetable {
    /*!
        \brief The class template for a train list in the timetable view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class train_list : public item<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The difference type.
        using difference_type = typename traits_type::difference_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

        //! The speed type.
        using speed_type = typename traits_type::speed_type;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;


        // constructors and destructor

        /*!
            \brief Creates a train list.

            \param direction        A direction.
            \param model            A model.
            \param message_catalog  A message catalog.
            \param canvas           A canvas.
            \param canvas_dimension A canvas dimension.
        */
        train_list(
            direction_type              direction,
            const model_type&           model,
            const message_catalog_type& message_catalog,
            canvas_type&                canvas,
            const dimension_type&       canvas_dimension);

        /*!
            \brief Moves a train list.

            \param another Another train list
        */
        train_list(train_list&& another);

        /*!
            \brief Destroys the train list.
        */
        virtual ~train_list() noexcept;


        // functions

        /*!
            \brief Assigns a train list.

            \param another Another train list.

            \return This train list.
        */
        train_list& operator=(train_list&& another);


    private:
        // types

        using base_type = item<traits_type>;

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas) const override;
    };


}}}


#endif
