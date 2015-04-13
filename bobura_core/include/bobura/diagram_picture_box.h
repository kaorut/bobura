/*! \file
    \brief The definition of bobura::diagram_picture_box.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMPICTUREBOX_H)
#define BOBURA_DIAGRAMPICTUREBOX_H

#include <memory>

#include <tetengo2.h>


namespace bobura
{
    /*!
        \brief The class template for the diagram picture box.

        \tparam PictureBox      A picture box type.
        \tparam AbstractWindow  An abstract window type.
        \tparam MouseCapture    A mouse capture type.
    */
    template <typename PictureBox, typename AbstractWindow, typename MouseCapture>
    class diagram_picture_box : public PictureBox
    {
    public:
        // types

        //! The base type.
        using base_type = PictureBox;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The mouse capture type.
        using mouse_capture_type = MouseCapture;
        
        //! The mouse button type.
        using mouse_button_type = typename mouse_capture_type::mouse_button_type;


        // constructors and destructor

        /*!
            \brief Creates a diagram picture box.

            \param parent A parent.
        */
        explicit diagram_picture_box(abstract_window_type& parent);

        /*!
            \brief Destroys the diagram picture box.
        */
        virtual ~diagram_picture_box()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Sets a mouse capture.

            \param mouse_button A mouse button.
        */
        void set_mouse_capture(const mouse_button_type mouse_button);

        /*!
            \brief Releases a mouse capture.

            \param mouse_button A mouse_button.

            \retval true  When the mouse is actually captured.
            \retval false Otherwise.
        */
        bool release_mouse_capture(const mouse_button_type mouse_button);

        /*!
            \brief Updates the scroll bars.

            \param view_dimension A view dimension.
            \param page_dimension A page dimension.
        */
        void update_scroll_bars(const dimension_type& view_dimension, const dimension_type& page_dimension);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}


#endif
