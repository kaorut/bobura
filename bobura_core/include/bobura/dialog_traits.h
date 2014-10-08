/*! \file
    \brief The definition of bobura::dialog_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_DIALOGTRAITS_H)
#define BOBURA_DIALOGTRAITS_H


namespace bobura
{
     /*!
        \brief The class template for the dialog traits.

        \tparam String                A string type.
        \tparam Position              A position type.
        \tparam Dimension             A dimension type.
        \tparam Dialog                A dialog type.
        \tparam AbstractWindow        An abstract window type.
        \tparam Label                 A label type.
        \tparam LinkLabel             A link label type.
        \tparam Image                 An image type.
        \tparam Button                A button type.
        \tparam TextBox               A text box type.
        \tparam ListBox               A list box type.
        \tparam PictureBox            A picture box type.
        \tparam TransparentBackground A transparent background type.
        \tparam MessageCatalog        A message catalog type.
    */
    template <
        typename String,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename AbstractWindow,
        typename Label,
        typename LinkLabel,
        typename Image,
        typename Button,
        typename TextBox,
        typename ListBox,
        typename PictureBox,
        typename TransparentBackground,
        typename MessageCatalog
    >
    class dialog_traits
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The dialog type.
        using dialog_type = Dialog;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The label type.
        using label_type = Label;

        //! The link label type.
        using link_label_type = LinkLabel;

        //! The image type.
        using image_type = Image;

        //! The button type.
        using button_type = Button;

        //! The text box type.
        using text_box_type = TextBox;

        //! The list box type.
        using list_box_type = ListBox;

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The transparent background type.
        using transparent_background_type = TransparentBackground;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;


    };


}


#endif
