/*! \file
    \brief The definition of bobura::train_kind_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <cassert>
//#include <memory>
//#include <stdexcept>
//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>
//#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"
#include "bobura.type_list.h"

#include "bobura.train_kind_dialog.h"


namespace bobura
{
    namespace
    {
        template <
            typename Dialog,
            typename MessageCatalog,
            typename IntSize,
            typename TrainKind,
            typename Font,
            typename Color
        >
        class train_kind_dialog<Dialog, MessageCatalog, IntSize, TrainKind, Font, Color>::impl :
            private boost::noncopyable
        {
        public:
            // types

            typedef Dialog base_type;

            typedef typename base_type::base_type abstract_window_type;

            typedef typename base_type::string_type string_type;

            typedef typename base_type::background_type background_type;

            typedef MessageCatalog message_catalog_type;

            typedef IntSize int_size_type;

            typedef TrainKind train_kind_type;

            typedef Font font_type;

            typedef Color color_type;

            typedef
                typename train_kind_dialog<
                    Dialog, MessageCatalog, IntSize, TrainKind, Font, Color
                >::info_set_type info_set_type;


            // constructors and destructor

            impl(
                base_type&                  base,
                abstract_window_type&       parent,
                const message_catalog_type& message_catalog,
                const font_type&            font,
                const color_type&           background_color
            )
            :
            m_base(base),
            m_message_catalog(message_catalog),
            m_info_sets(),
            m_p_train_kind_label(),
            m_p_train_kind_list_box(),
            m_p_add_button(),
            m_p_delete_button(),
            m_p_up_button(),
            m_p_down_button(),
            m_p_name_label(),
            m_p_name_text_box(),
            m_p_abbreviation_label(),
            m_p_abbreviation_text_box(),
            m_p_color_button(),
            m_p_weight_label(),
            m_p_weight_dropdown_box(),
            m_p_line_style_label(),
            m_p_line_style_dropdown_box(),
            m_p_sample_picture_box(),
            m_p_apply_button(),
            m_p_ok_button(),
            m_p_cancel_button()
            {
                initialize_dialog(parent, font, background_color);
            }


            // functions

            const std::vector<info_set_type> info_sets()
            const
            {
                return m_info_sets;
            }

            void set_info_sets(std::vector<info_set_type> info_sets)
            {
                m_info_sets = std::move(info_sets);
            }

            void do_modal_impl()
            {
                sync_list_box_with_info_sets();
                if (m_p_train_kind_list_box->item_count() > 0)
                    m_p_train_kind_list_box->select_item(0);
                update();
            }



        private:
            // types

            typedef typename boost::mpl::at<ui_type_list, type::ui::label>::type label_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::list_box>::type list_box_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::text_box>::type text_box_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::dropdown_box>::type dropdown_box_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::button>::type button_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::picture_box>::type picture_box_type;

            typedef
                typename boost::mpl::at<ui_type_list, type::ui::transparent_background>::type
                transparent_background_type;

            typedef
                typename message::train_kind_dialog::type_list<
                    info_set_type,
                    int_size_type,
                    base_type,
                    list_box_type,
                    typename boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type,
                    typename boost::mpl::at<common_dialog_type_list, type::common_dialog::color>::type,
                    message_catalog_type
                >::type
                train_kind_dialog_message_type_list_type;

            typedef typename base_type::dimension_type dimension_type;

            typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

            typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

            typedef typename base_type::position_type position_type;

            typedef typename tetengo2::gui::position<position_type>::left_type left_type;

            typedef typename tetengo2::gui::position<position_type>::top_type top_type;

            typedef typename train_kind_type::weight_type weight_type;

            typedef typename train_kind_type::line_style_type line_style_type;


            // static functions

            static int_size_type to_weight_dropdown_box_index(const typename weight_type::enum_t weight)
            {
                switch (weight)
                {
                case weight_type::normal:
                    return 0;
                case weight_type::bold:
                    return 1;
                default:
                    assert(false);
                    BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid weight."));
                }
            }

            static int_size_type to_line_style_dropdown_box_index(const typename line_style_type::enum_t line_style)
            {
                switch (line_style)
                {
                case line_style_type::solid:
                    return 0;
                case line_style_type::dashed:
                    return 1;
                case line_style_type::dotted:
                    return 2;
                case line_style_type::dot_dashed:
                    return 3;
                default:
                    assert(false);
                    BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid line style."));
                }
            }


            // variables

            base_type& m_base;

            const message_catalog_type& m_message_catalog;

            std::vector<info_set_type> m_info_sets;

            std::unique_ptr<label_type> m_p_train_kind_label;

            std::unique_ptr<list_box_type> m_p_train_kind_list_box;

            std::unique_ptr<button_type> m_p_add_button;

            std::unique_ptr<button_type> m_p_delete_button;

            std::unique_ptr<button_type> m_p_up_button;

            std::unique_ptr<button_type> m_p_down_button;

            std::unique_ptr<label_type> m_p_name_label;

            std::unique_ptr<text_box_type> m_p_name_text_box;

            std::unique_ptr<label_type> m_p_abbreviation_label;

            std::unique_ptr<text_box_type> m_p_abbreviation_text_box;

            std::unique_ptr<button_type> m_p_color_button;

            std::unique_ptr<label_type> m_p_weight_label;

            std::unique_ptr<dropdown_box_type> m_p_weight_dropdown_box;

            std::unique_ptr<label_type> m_p_line_style_label;

            std::unique_ptr<dropdown_box_type> m_p_line_style_dropdown_box;

            std::unique_ptr<label_type> m_p_sample_label;

            std::unique_ptr<picture_box_type> m_p_sample_picture_box;

            std::unique_ptr<button_type> m_p_apply_button;

            std::unique_ptr<button_type> m_p_ok_button;

            std::unique_ptr<button_type> m_p_cancel_button;


            // functions

            void initialize_dialog(
                const abstract_window_type& parent,
                const font_type&            font,
                const color_type&           background_color
            )
            {
                m_base.set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Train Kinds")));

                m_p_train_kind_label = create_train_kind_label();
                m_p_train_kind_list_box = create_train_kind_list_box();
                m_p_add_button = create_add_button();
                m_p_delete_button = create_delete_button();
                m_p_up_button = create_up_button();
                m_p_down_button = create_down_button();
                m_p_name_label = create_name_label();
                m_p_name_text_box = create_name_text_box();
                m_p_abbreviation_label = create_abbreviation_label();
                m_p_abbreviation_text_box = create_abbreviation_text_box();
                m_p_color_button = create_color_button();
                m_p_weight_label = create_weight_label();
                m_p_weight_dropdown_box = create_weight_dropdown_box();
                m_p_line_style_label = create_line_style_label();
                m_p_line_style_dropdown_box = create_line_style_dropdown_box();
                m_p_sample_label = create_sample_label();
                m_p_sample_picture_box = create_sample_picture_box(font, background_color);
                m_p_apply_button = create_apply_button();
                m_p_ok_button = create_ok_button();
                m_p_cancel_button = create_cancel_button();

                locate_controls();
            }

            std::unique_ptr<label_type> create_train_kind_label()
            {
                std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(m_base);

                p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Train &Kinds:")));
                std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
                p_label->set_background(std::move(p_background));

                return std::move(p_label);
            }

            std::unique_ptr<list_box_type> create_train_kind_list_box()
            {
                std::unique_ptr<list_box_type> p_list_box =
                    tetengo2::make_unique<list_box_type>(m_base, list_box_type::scroll_bar_style_type::vertical);

                p_list_box->list_box_observer_set().selection_changed().connect(
                    typename boost::mpl::at<
                        train_kind_dialog_message_type_list_type,
                        message::train_kind_dialog::type::train_kind_list_box_selection_changed
                    >::type(*p_list_box, TETENGO2_CPP11_BIND(&impl::update, this))
                );

                return std::move(p_list_box);
            }

            std::unique_ptr<button_type> create_add_button()
            {
                std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(m_base);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Add")));
                //p_button->mouse_observer_set().clicked().connect(
                //    typename boost::mpl::at<
                //        train_kind_dialog_message_type_list_type,
                //        message::train_kind_dialog::type::ok_button_mouse_clicked
                //    >::type(m_base)
                //);

                return std::move(p_button);
            }

            std::unique_ptr<button_type> create_delete_button()
            {
                std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(m_base);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:D&elete")));
                //p_button->mouse_observer_set().clicked().connect(
                //    typename boost::mpl::at<
                //        train_kind_dialog_message_type_list_type,
                //        message::train_kind_dialog::type::ok_button_mouse_clicked
                //    >::type(m_base)
                //);

                return std::move(p_button);
            }

            std::unique_ptr<button_type> create_up_button()
            {
                std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(m_base);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Up")));
                //p_button->mouse_observer_set().clicked().connect(
                //    typename boost::mpl::at<
                //        train_kind_dialog_message_type_list_type,
                //        message::train_kind_dialog::type::ok_button_mouse_clicked
                //    >::type(m_base)
                //);

                return std::move(p_button);
            }

            std::unique_ptr<button_type> create_down_button()
            {
                std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(m_base);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Down")));
                //p_button->mouse_observer_set().clicked().connect(
                //    typename boost::mpl::at<
                //        train_kind_dialog_message_type_list_type,
                //        message::train_kind_dialog::type::ok_button_mouse_clicked
                //    >::type(m_base)
                //);

                return std::move(p_button);
            }

            std::unique_ptr<label_type> create_name_label()
            {
                std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(m_base);

                p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:&Name:")));
                std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
                p_label->set_background(std::move(p_background));

                return std::move(p_label);
            }

            std::unique_ptr<text_box_type> create_name_text_box()
            {
                std::unique_ptr<text_box_type> p_text_box =
                    tetengo2::make_unique<text_box_type>(m_base, list_box_type::scroll_bar_style_type::none);

                return std::move(p_text_box);
            }

            std::unique_ptr<label_type> create_abbreviation_label()
            {
                std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(m_base);

                p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:A&bbreviation:")));
                std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
                p_label->set_background(std::move(p_background));

                return std::move(p_label);
            }

            std::unique_ptr<text_box_type> create_abbreviation_text_box()
            {
                std::unique_ptr<text_box_type> p_text_box =
                    tetengo2::make_unique<text_box_type>(m_base, list_box_type::scroll_bar_style_type::none);

                return std::move(p_text_box);
            }

            std::unique_ptr<button_type> create_color_button()
            {
                std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(m_base);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Line &Color...")));
                //p_button->mouse_observer_set().clicked().connect(
                //    typename boost::mpl::at<
                //        train_kind_dialog_message_type_list_type,
                //        message::train_kind_dialog::type::ok_button_mouse_clicked
                //    >::type(m_base)
                //);

                return std::move(p_button);
            }

            std::unique_ptr<label_type> create_weight_label()
            {
                std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(m_base);

                p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Line &Weight:")));
                std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
                p_label->set_background(std::move(p_background));

                return std::move(p_label);
            }

            std::unique_ptr<dropdown_box_type> create_weight_dropdown_box()
            {
                std::unique_ptr<dropdown_box_type> p_dropdown_box = tetengo2::make_unique<dropdown_box_type>(m_base);

                p_dropdown_box->insert_item(
                    p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Normal"))
                );
                p_dropdown_box->insert_item(
                    p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Bold"))
                );
                p_dropdown_box->select_item(0);

                return std::move(p_dropdown_box);
            }

            std::unique_ptr<label_type> create_line_style_label()
            {
                std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(m_base);

                p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Line &Style:")));
                std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
                p_label->set_background(std::move(p_background));

                return std::move(p_label);
            }

            std::unique_ptr<dropdown_box_type> create_line_style_dropdown_box()
            {
                std::unique_ptr<dropdown_box_type> p_dropdown_box = tetengo2::make_unique<dropdown_box_type>(m_base);

                p_dropdown_box->insert_item(
                    p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Solid"))
                );
                p_dropdown_box->insert_item(
                    p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Dashed"))
                );
                p_dropdown_box->insert_item(
                    p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Dotted"))
                );
                p_dropdown_box->insert_item(
                    p_dropdown_box->item_count(), m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Dot-Dashed"))
                );
                p_dropdown_box->select_item(0);

                return std::move(p_dropdown_box);
            }

            std::unique_ptr<label_type> create_sample_label()
            {
                std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(m_base);

                p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:Sa&mple:")));
                std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
                p_label->set_background(std::move(p_background));

                return std::move(p_label);
            }

            std::unique_ptr<picture_box_type> create_sample_picture_box(
                const font_type&  font,
                const color_type& background_color
            )
            {
                std::unique_ptr<picture_box_type> p_picture_box =
                    tetengo2::make_unique<picture_box_type>(m_base, list_box_type::scroll_bar_style_type::none);

                p_picture_box->set_dimension(dimension_type(width_type(20), height_type(4)));
                p_picture_box->fast_paint_observer_set().paint().connect(
                    typename boost::mpl::at<
                        train_kind_dialog_message_type_list_type,
                        message::train_kind_dialog::type::sample_picture_box_paint
                    >::type(m_info_sets, boost::none, font, background_color, p_picture_box->client_dimension())
                );

                return std::move(p_picture_box);
            }

            std::unique_ptr<button_type> create_apply_button()
            {
                std::unique_ptr<button_type> p_button = tetengo2::make_unique<button_type>(m_base);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:TrainKind:A&pply")));
                p_button->mouse_observer_set().clicked().connect(
                    typename boost::mpl::at<
                        train_kind_dialog_message_type_list_type,
                        message::train_kind_dialog::type::apply_button_mouse_clicked
                    >::type(m_base, TETENGO2_CPP11_BIND(&impl::apply, this))
                );

                return std::move(p_button);
            }

            std::unique_ptr<button_type> create_ok_button()
            {
                std::unique_ptr<button_type> p_button =
                    tetengo2::make_unique<button_type>(m_base, button_type::style_type::default_);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:OK")));
                p_button->mouse_observer_set().clicked().connect(
                    typename boost::mpl::at<
                        train_kind_dialog_message_type_list_type,
                        message::train_kind_dialog::type::ok_button_mouse_clicked
                    >::type(m_base)
                );

                return std::move(p_button);
            }

            std::unique_ptr<button_type> create_cancel_button()
            {
                std::unique_ptr<button_type> p_button =
                    tetengo2::make_unique<button_type>(m_base, button_type::style_type::cancel);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:Cancel")));
                p_button->mouse_observer_set().clicked().connect(
                    typename boost::mpl::at<
                        train_kind_dialog_message_type_list_type,
                        message::train_kind_dialog::type::cancel_button_mouse_clicked
                    >::type(m_base)
                );

                return std::move(p_button);
            }

            void locate_controls()
            {
                m_base.set_client_dimension(dimension_type(width_type(46), height_type(29)));

                const left_type train_kind_label_left(2);

                m_p_train_kind_label->fit_to_content();
                m_p_train_kind_label->set_position(position_type(train_kind_label_left, top_type(1)));

                const width_type list_box_width(20);
                const height_type list_box_height(19);
                m_p_train_kind_list_box->set_dimension(dimension_type(list_box_width, list_box_height));
                m_p_train_kind_list_box->set_position(
                    position_type(
                        train_kind_label_left,
                        tetengo2::gui::position<position_type>::top(m_p_train_kind_label->position()) +
                            top_type::from(
                                tetengo2::gui::dimension<dimension_type>::height(m_p_train_kind_label->dimension())
                            )
                    )
                );

                const width_type list_box_button_width(typename width_type::value_type(9, 2));
                left_type list_box_button_left(
                    train_kind_label_left + left_type::from(list_box_width) - left_type::from(list_box_button_width)
                );
                const top_type list_box_button_top(
                    tetengo2::gui::position<position_type>::top(m_p_train_kind_list_box->position()) +
                        top_type::from(list_box_height)
                );
                m_p_down_button->set_dimension(dimension_type(list_box_button_width, height_type(2)));
                m_p_down_button->set_position(position_type(list_box_button_left, list_box_button_top));

                list_box_button_left -=
                    left_type::from(list_box_button_width) + left_type(typename left_type::value_type(1, 4));
                m_p_up_button->set_dimension(dimension_type(list_box_button_width, height_type(2)));
                m_p_up_button->set_position(position_type(list_box_button_left, list_box_button_top));

                list_box_button_left -=
                    left_type::from(list_box_button_width) + left_type(typename left_type::value_type(1, 2));
                m_p_delete_button->set_dimension(dimension_type(list_box_button_width, height_type(2)));
                m_p_delete_button->set_position(position_type(list_box_button_left, list_box_button_top));

                list_box_button_left -=
                    left_type::from(list_box_button_width) + left_type(typename left_type::value_type(1, 4));
                m_p_add_button->set_dimension(dimension_type(list_box_button_width, height_type(2)));
                m_p_add_button->set_position(position_type(list_box_button_left, list_box_button_top));

                const left_type name_label_left(24);
                m_p_name_label->fit_to_content();
                m_p_name_label->set_position(position_type(name_label_left, top_type(1)));

                const left_type name_text_box_left(32);
                m_p_name_text_box->set_dimension(dimension_type(width_type(12), height_type(2)));
                m_p_name_text_box->set_position(position_type(name_text_box_left, top_type(1)));

                m_p_abbreviation_label->fit_to_content();
                m_p_abbreviation_label->set_position(position_type(name_label_left, top_type(4)));

                m_p_abbreviation_text_box->set_dimension(dimension_type(width_type(12), height_type(2)));
                m_p_abbreviation_text_box->set_position(position_type(name_text_box_left, top_type(4)));

                m_p_color_button->set_dimension(dimension_type(width_type(8), height_type(2)));
                m_p_color_button->set_position(position_type(name_text_box_left, top_type(7)));

                m_p_weight_label->fit_to_content();
                m_p_weight_label->set_position(position_type(name_label_left, top_type(10)));

                m_p_weight_dropdown_box->set_dimension(dimension_type(width_type(12), height_type(2)));
                m_p_weight_dropdown_box->set_position(position_type(name_text_box_left, top_type(10)));

                m_p_line_style_label->fit_to_content();
                m_p_line_style_label->set_position(position_type(name_label_left, top_type(13)));

                m_p_line_style_dropdown_box->set_dimension(dimension_type(width_type(12), height_type(2)));
                m_p_line_style_dropdown_box->set_position(position_type(name_text_box_left, top_type(13)));

                m_p_sample_label->fit_to_content();
                m_p_sample_label->set_position(position_type(name_label_left, top_type(16)));

                m_p_sample_picture_box->set_position(
                    position_type(
                        name_label_left,
                        tetengo2::gui::position<position_type>::top(m_p_sample_label->position()) +
                            top_type::from(
                                tetengo2::gui::dimension<dimension_type>::height(m_p_sample_label->dimension())
                            )
                    )
                );

                m_p_apply_button->set_dimension(dimension_type(width_type(8), height_type(2)));
                m_p_apply_button->set_position(position_type(left_type(36), top_type(22)));

                m_p_ok_button->set_dimension(dimension_type(width_type(8), height_type(2)));
                m_p_ok_button->set_position(position_type(left_type(27), top_type(26)));

                m_p_cancel_button->set_dimension(dimension_type(width_type(8), height_type(2)));
                m_p_cancel_button->set_position(position_type(left_type(36), top_type(26)));
            }

            void sync_list_box_with_info_sets()
            {
                m_p_train_kind_list_box->clear();
                for (
                    typename std::vector<info_set_type>::const_iterator i = m_info_sets.begin();
                    i != m_info_sets.end();
                    ++i
                )
                {
                    m_p_train_kind_list_box->insert_item(
                        m_p_train_kind_list_box->item_count(),
                        i->train_kind().name()
                    );
                }
            }

            void update()
            {
                const boost::optional<int_size_type>& selected_index = m_p_train_kind_list_box->selected_item_index();

                m_p_name_label->set_enabled(selected_index);
                m_p_name_text_box->set_enabled(selected_index);
                m_p_abbreviation_label->set_enabled(selected_index);
                m_p_abbreviation_text_box->set_enabled(selected_index);
                m_p_color_button->set_enabled(selected_index);
                m_p_weight_label->set_enabled(selected_index);
                m_p_weight_dropdown_box->set_enabled(selected_index);
                m_p_line_style_label->set_enabled(selected_index);
                m_p_line_style_dropdown_box->set_enabled(selected_index);
                m_p_apply_button->set_enabled(selected_index);

                if (selected_index)
                {
                    assert(m_info_sets.size() == m_p_train_kind_list_box->item_count());
                    const train_kind_type& train_kind = m_info_sets[*selected_index].train_kind();

                    m_p_name_text_box->set_text(train_kind.name());
                    m_p_abbreviation_text_box->set_text(train_kind.abbreviation());
                    m_p_weight_dropdown_box->select_item(to_weight_dropdown_box_index(train_kind.weight()));
                    m_p_line_style_dropdown_box->select_item(
                        to_line_style_dropdown_box_index(train_kind.line_style())
                    );
                }
                else
                {
                    m_p_name_text_box->set_text(string_type());
                    m_p_abbreviation_text_box->set_text(string_type());
                    m_p_weight_dropdown_box->select_item(0);
                    m_p_line_style_dropdown_box->select_item(0);
                }

                m_p_sample_picture_box->repaint();
            }

            void apply()
            {

            }


        };


    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename TrainKind,
        typename Font,
        typename Color
    >
    train_kind_dialog<Dialog, MessageCatalog, IntSize, TrainKind, Font, Color>::train_kind_dialog(
        abstract_window_type&       parent,
        const message_catalog_type& message_catalog,
        const font_type&            font,
        const color_type&           background_color
    )
    :
    base_type(parent),
    m_p_impl(tetengo2::make_unique<impl>(*this, parent, message_catalog, font, background_color))
    {}

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename TrainKind,
        typename Font,
        typename Color
    >
    train_kind_dialog<Dialog, MessageCatalog, IntSize, TrainKind, Font, Color>::~train_kind_dialog()
    TETENGO2_CPP11_NOEXCEPT
    {}
    
    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename TrainKind,
        typename Font,
        typename Color
    >
    const std::vector<
        typename train_kind_dialog<Dialog, MessageCatalog, IntSize, TrainKind, Font, Color>::info_set_type
    >
    train_kind_dialog<Dialog, MessageCatalog, IntSize, TrainKind, Font, Color>::info_sets()
    const
    {
        return m_p_impl->info_sets();
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename TrainKind,
        typename Font,
        typename Color
    >
    void train_kind_dialog<Dialog, MessageCatalog, IntSize, TrainKind, Font, Color>::set_info_sets(
        std::vector<info_set_type> info_sets
    )
    {
        m_p_impl->set_info_sets(std::move(info_sets));
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename TrainKind,
        typename Font,
        typename Color
    >
    void train_kind_dialog<Dialog, MessageCatalog, IntSize, TrainKind, Font, Color>::do_modal_impl()
    {
        m_p_impl->do_modal_impl();
    }

    typedef
        bobura::model::train_kind<
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<ui_type_list, type::ui::color>::type
        >
        train_kind_type;
    template class train_kind_dialog<
        typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
        typename boost::mpl::at<common_type_list, type::size>::type,
        train_kind_type,
        typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
        typename boost::mpl::at<ui_type_list, type::ui::color>::type
    >;


}
