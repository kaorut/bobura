/*! \file
    \brief The definition of bobura::load_save::traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_TRAITS_H)
#define BOBURA_LOADSAVE_TRAITS_H


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for the loading and saving processing traits.

        \tparam Size                 A size type.
        \tparam Difference           A difference type.
        \tparam String               A string type.
        \tparam ForwardIterator      A forward iterator type.
        \tparam OutputStream         An output stream type.
        \tparam OperatingDistance    An operating distance type.
        \tparam Speed                A speed type.
        \tparam Font                 A font type.
        \tparam AbstractWindow       An abstract window type.
        \tparam MessageBox           A message box type.
        \tparam FileOpenDialog       A file open dialog type.
        \tparam FileSaveDialog       A file save dialog type.
        \tparam OuDiaDiagramDialog   An OuDia diagram dialog type.
        \tparam MessageCatalog       A message catalog type.
        \tparam TimetableFileEncoder An timetable file encoder type.
        \tparam WinDiaFileEncoder    An WinDIA file encoder type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename AbstractWindow,
        typename MessageBox,
        typename FileOpenDialog,
        typename FileSaveDialog,
        typename OuDiaDiagramDialog,
        typename MessageCatalog,
        typename TimetableFileEncoder,
        typename WinDiaFileEncoder
    >
    class traits
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The output stream type.
        using output_stream_type = OutputStream;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The font type.
        using font_type = Font;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The message box type.
        using message_box_type = MessageBox;

        //! The file open dialog type.
        using file_open_dialog_type = FileOpenDialog;

        //! The file save dialog type.
        using file_save_dialog_type = FileSaveDialog;

        //! The OuDia diagram dialog type.
        using oudia_diagram_dialog_type = OuDiaDiagramDialog;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The timetable file encoder type.
        using timetable_file_encoder_type = TimetableFileEncoder;

        //! The WinDIA file encoder type.
        using windia_file_encoder_type = WinDiaFileEncoder;


    };


}}


#endif
