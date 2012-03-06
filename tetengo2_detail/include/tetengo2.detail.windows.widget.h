/*! \file
    \brief The definition of tetengo2::detail::windows::widget.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_WIDGET_H)
#define TETENGO2_DETAIL_WINDOWS_WIDGET_H

#include <algorithm>
#include <cassert>
//#include <cstddef>
#include <exception>
//#include <memory>
#include <stdexcept>
#include <string>
#include <system_error>
#include <tuple>
//#include <type_traits>
//#include <utility>
#include <vector>

#include <boost/exception/all.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.cpp11.h"
#include "tetengo2.detail.windows.error_category.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        struct widget_deleter
        {
            void operator()(const ::HWND window_handle)
            const
            {
                if (::IsWindow(window_handle))
                    ::DestroyWindow(window_handle);
            }


        };


    }
#endif


    /*!
        \brief The class for a detail implementation of a widget.
    */
    class widget
    {
    public:
        // types

        //! The widget details type.
        typedef
            std::tuple<
                std::unique_ptr<
                    typename std::remove_pointer< ::HWND>::type,
                    detail::widget_deleter
                >,
                ::WNDPROC,
                ::HWND
            >
            widget_details_type;

        //! The widget details pointer type.
        typedef std::unique_ptr<widget_details_type> widget_details_ptr_type;


        // static functions

        /*!
            \brief Creates a window.

            \tparam Widget A widget type.

            \param parent A parent widget.
                          When uninitialized, the window has no parent.

            \return A unique pointer to a window.

            \throw std::system_error When a window cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_window(
            const boost::optional<Widget&>& parent = boost::none
        )
        {
            const ::HINSTANCE instance_handle = ::GetModuleHandle(NULL);
            if (!instance_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't get the instance handle!"
                    )
                );
            }

            if (
                !window_class_is_registered(
                    window_class_name(), instance_handle
                )
            )
            {
                register_window_class_for_window<Widget>(instance_handle);
            }

            typename std::tuple_element<0, widget_details_type>::type
            p_widget(
                ::CreateWindowExW(
                    WS_EX_ACCEPTFILES | WS_EX_APPWINDOW,
                    window_class_name().c_str(),
                    window_class_name().c_str(),
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent ?
                        const_cast< ::HWND>(
                            std::get<0>(*parent->details()).get()
                        ) :
                        HWND_DESKTOP,
                    NULL,
                    instance_handle,
                    NULL
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't create a window!"
                    )
                );
            }

            return make_unique<widget_details_type>(
                std::move(p_widget),
                &::DefWindowProcW,
                static_cast< ::HWND>(NULL)
            );
        }

        /*!
            \brief Creates a dialog.

            \tparam Widget A widget type.

            \param parent A parent widget.
                          When uninitialized, the dialog has no parent.

            \return A unique pointer to a dialog.

            \throw std::system_error When a dialog cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_dialog(
            const boost::optional<Widget&>& parent
        )
        {
            const ::HINSTANCE instance_handle = ::GetModuleHandle(NULL);
            if (!instance_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't get the instance handle!"
                    )
                );
            }

            if (
                !window_class_is_registered(
                    dialog_class_name(), instance_handle
                )
            )
            {
                register_window_class_for_dialog<Widget>(instance_handle);
            }

            typename std::tuple_element<0, widget_details_type>::type
            p_widget(
                ::CreateWindowExW(
                    WS_EX_CONTEXTHELP | WS_EX_DLGMODALFRAME,
                    dialog_class_name().c_str(),
                    dialog_class_name().c_str(),
                    WS_POPUPWINDOW | WS_CAPTION,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent ?
                        const_cast< ::HWND>(
                            std::get<0>(*parent->details()).get()
                        ) :
                        HWND_DESKTOP,
                    NULL,
                    instance_handle,
                    NULL
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't create a dialog!"
                    )
                );
            }

            delete_system_menus(p_widget.get());

            return make_unique<widget_details_type>(
                std::move(p_widget),
                &::DefWindowProcW,
                static_cast< ::HWND>(NULL)
            );
        }

        /*!
            \brief Creates a button.

            \tparam Widget A widget type.

            \param parent     A parent widget.
            \param is_default Set true to create a default button.
            \param is_cancel  Set true to create a cancel button.

            \return A unique pointer to a button.

            \throw std::invalid_argument When a default button already exists
                                         and is_default is true.
            \throw std::invalid_argument When a cancel button already exists
                                         and is_cancel is true.
            \throw std::system_error     When a button cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_button(
            const Widget& parent,
            const bool    is_default,
            const bool    is_cancel
        )
        {
            assert(!is_default || !is_cancel);

            const ::DWORD create_window_style =
                is_default ?
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON :
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON;
            ::HMENU id = NULL;
            if (is_default)
            {
                if (
                    ::GetDlgItem(
                        const_cast< ::HWND>(
                            std::get<0>(
                                *parent.root_ancestor().details()
                            ).get()
                        ),
                        IDOK
                    )
                )
                {
                    BOOST_THROW_EXCEPTION(
                        std::invalid_argument(
                            "Default button already exists."
                        )
                    );
                }
                id = reinterpret_cast< ::HMENU>(IDOK);
            }
            else if (is_cancel)
            {
                if (
                    ::GetDlgItem(
                        const_cast< ::HWND>(
                            std::get<0>(
                                *parent.root_ancestor().details()
                            ).get()
                        ),
                        IDCANCEL
                    )
                )
                {
                    BOOST_THROW_EXCEPTION(
                        std::invalid_argument("Cancel button already exists.")
                    );
                }
                id = reinterpret_cast< ::HMENU>(IDCANCEL);
            }

            typename std::tuple_element<0, widget_details_type>::type
            p_widget(
                ::CreateWindowExW(
                    0,
                    L"Button",
                    L"tetengo2_button",
                    create_window_style,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    const_cast< ::HWND>(std::get<0>(*parent.details()).get()),
                    id,
                    ::GetModuleHandle(NULL),
                    NULL
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't create a button!"
                    )
                );
            }

            const ::WNDPROC p_original_window_procedure =
                replace_window_procedure<Widget>(p_widget.get());

            return make_unique<widget_details_type>(
                std::move(p_widget),
                p_original_window_procedure,
                static_cast< ::HWND>(NULL)
            );
        }

        /*!
            \brief Creates an image.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to an image.

            \throw std::system_error When an image cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_image(const Widget& parent)
        {
            typename std::tuple_element<0, widget_details_type>::type
            p_widget(
                ::CreateWindowExW(
                    0,
                    L"Static",
                    L"tetengo2_image",
                    WS_CHILD | WS_VISIBLE,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    const_cast< ::HWND>(std::get<0>(*parent.details()).get()),
                    NULL,
                    ::GetModuleHandle(NULL),
                    NULL
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't create an image!"
                    )
                );
            }

            const ::WNDPROC p_original_window_procedure =
                replace_window_procedure<Widget>(p_widget.get());

            return make_unique<widget_details_type>(
                std::move(p_widget),
                p_original_window_procedure,
                static_cast< ::HWND>(NULL)
            );
        }

        /*!
            \brief Creates a label.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to a label.

            \throw std::system_error When a label cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_label(const Widget& parent)
        {
            typename std::tuple_element<0, widget_details_type>::type
            p_widget(
                ::CreateWindowExW(
                    0,
                    L"Static",
                    L"tetengo2_label",
                    WS_CHILD | WS_VISIBLE | SS_NOTIFY,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    const_cast< ::HWND>(std::get<0>(*parent.details()).get()),
                    NULL,
                    ::GetModuleHandle(NULL),
                    NULL
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't create a label!"
                    )
                );
            }

            const ::WNDPROC p_original_window_procedure =
                replace_window_procedure<Widget>(p_widget.get());

            return make_unique<widget_details_type>(
                std::move(p_widget),
                p_original_window_procedure,
                static_cast< ::HWND>(NULL)
            );
        }

        /*!
            \brief Creates a text box.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to a text box.

            \throw std::system_error When a text box cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_text_box(Widget& parent)
        {
            typename std::tuple_element<0, widget_details_type>::type
            p_widget(
                ::CreateWindowExW(
                    WS_EX_CLIENTEDGE,
                    L"Edit",
                    L"",
                    WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    const_cast< ::HWND>(std::get<0>(*parent.details()).get()),
                    NULL,
                    ::GetModuleHandle(NULL),
                    NULL
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't create a text box!"
                    )
                );
            }

            const ::WNDPROC p_original_window_procedure =
                replace_window_procedure<Widget>(p_widget.get());

            return make_unique<widget_details_type>(
                std::move(p_widget),
                p_original_window_procedure,
                static_cast< ::HWND>(NULL)
            );
        }

        /*!
            \brief Associates a widget to the native window system.

            \tparam Widget A widget type.

            \param widget A widget.

            \throw std::system_error When the widget cannot be associated.
        */
        template <typename Widget>
        static void associate_to_native_window_system(Widget& widget)
        {
            assert(
                !::GetPropW(
                    std::get<0>(*widget.details()).get(),
                    property_key_for_cpp_instance().c_str()
                )
            );
            const ::BOOL result =
                ::SetPropW(
                    std::get<0>(*widget.details()).get(),
                    property_key_for_cpp_instance().c_str(),
                    reinterpret_cast< ::HANDLE>(&widget)
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't set C++ instance."
                    )
                );
            }
        }

        /*!
            \brief Returns whether the widget has a parent.

            \tparam Widget A widget type.

            \param widget A widget.

            \retval true  When the widget has a parent.
            \retval false Otherwise.
        */
        template <typename Widget>
        static bool has_parent(const Widget& widget)
        {
            return
                ::GetParent(
                    const_cast< ::HWND>(std::get<0>(*widget.details()).get())
                );
        }

        /*!
            \brief Returns the parent.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The parent.

            \throw std::logic_error When the widget has no parent.
        */
        template <typename Widget>
        static Widget& parent(const Widget& widget)
        {
            Widget* const p_parent =
                p_widget_from<Widget>(
                    ::GetParent(
                        const_cast< ::HWND>(
                            std::get<0>(*widget.details()).get()
                        )
                    )
                );
            if (!p_parent)
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The widget has no parent.")
                );
            }

            return *p_parent;
        }

        /*!
            \brief Returns the root ancestor.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The root ancestor.

            \throw std::logic_error When the widget has no root ancestor.
        */
        template <typename Widget>
        static Widget& root_ancestor(const Widget& widget)
        {
            const ::HWND root_ancestor_handle =
                ::GetAncestor(
                    const_cast< ::HWND>(std::get<0>(*widget.details()).get()),
                    GA_ROOT
                );
            if (!root_ancestor_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The widget has no root ancestor.")
                );
            }

            Widget* const p_root_ancestor =
                p_widget_from<Widget>(root_ancestor_handle);
            assert(p_root_ancestor);
            return *p_root_ancestor;
        }

        /*!
            \brief Sets an enabled status.

            \tparam Widget A widget type.

            \param widget A widget.
            \param enabled An enabled status.
        */
        template <typename Widget>
        static void set_enabled(Widget& widget, const bool enabled)
        {
            ::EnableWindow(
                std::get<0>(*widget.details()).get(), enabled ? TRUE : FALSE
            );
        }

        /*!
            \brief Returns the enabled status.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The enabled status.
        */
        template <typename Widget>
        static bool enabled(const Widget& widget)
        {
            return
                ::IsWindowEnabled(
                    const_cast< ::HWND>(std::get<0>(*widget.details()).get())
                ) == TRUE;
        }

        /*!
            \brief Sets a visible status.

            \tparam Widget A widget type.

            \param widget A widget.
            \param visible A visible status.
        */
        template <typename Widget>
        static void set_visible(Widget& widget, const bool visible)
        {
            ::ShowWindow(
                std::get<0>(*widget.details()).get(), visible ?
                SW_SHOW : SW_HIDE
            );
            if (visible)
                ::UpdateWindow(std::get<0>(*widget.details()).get());
        }

        /*!
            \brief Returns the visible status.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The visible status.
        */
        template <typename Widget>
        static bool visible(const Widget& widget)
        {
            return
                ::IsWindowVisible(
                    const_cast< ::HWND>(std::get<0>(*widget.details()).get())
                ) == TRUE;
        }

        /*!
            \brief Sets a position.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.
            \tparam Position  A position type.

            \param widget   A widget.
            \param position A position.

            \throw std::system_error When the widget cannot be moved.
        */
        template <typename Dimension, typename Widget, typename Position>
        static void set_position(Widget& widget, const Position& position)
        {
            const Dimension dim = dimension<Dimension>(widget);
            const ::BOOL result = ::MoveWindow(
                std::get<0>(*widget.details()).get(),
                gui::to_pixels<int>(gui::position<Position>::left(position)),
                gui::to_pixels<int>(gui::position<Position>::top(position)),
                gui::to_pixels<int>(gui::dimension<Dimension>::width(dim)),
                gui::to_pixels<int>(gui::dimension<Dimension>::height(dim)),
                visible(widget) ? TRUE : FALSE
            );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't move the widget."
                    )
                );
            }
        }

        /*!
            \brief Returns the position.

            \tparam Position  A position type.
            \tparam Widget A widget type.

            \param widget A widget.

            \return The position.

            \throw std::system_error When the position cannot be obtained.
        */
        template <typename Position, typename Widget>
        static Position position(const Widget& widget)
        {
            ::RECT rectangle = {};
            if (
                ::GetWindowRect(
                    const_cast< ::HWND>(std::get<0>(*widget.details()).get()),
                    &rectangle
                ) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't get window rectangle."
                    )
                );
            }

            typedef gui::position<Position> position_traits_type;
            return position_traits_type::make(
                gui::to_unit<typename position_traits_type::left_type>(
                    rectangle.left
                ),
                gui::to_unit<typename position_traits_type::top_type>(
                    rectangle.top
                )
            );
        }

        /*!
            \brief Calculates a position suitable for a dialog.

            \tparam Position     A position type.
            \tparam Widget       A widget type.
            \tparam ParentWidget A parent widget type.

            \param widget A widget.
            \param parent A parent widget.

            \return A position.

            \throw std::system_error When a position cannot be calculated.
        */
        template <typename Position, typename Widget, typename ParentWidget>
        static Position dialog_position(Widget& widget, ParentWidget& parent)
        {
            ::POINT point = {};
            const ::LONG x_margin = ::GetSystemMetrics(SM_CYFIXEDFRAME) * 2;
            const ::LONG y_margin = ::GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
            if (
                ::ClientToScreen(
                    std::get<0>(*parent.details()).get(), &point
                ) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(
                            ERROR_FUNCTION_FAILED, win32_category()
                        ),
                        "Can't get parent window client area position."
                    )
                );
            }
            point.x += x_margin;
            point.y += y_margin;

            const ::HMONITOR monitor_handle =
                ::MonitorFromPoint(point, MONITOR_DEFAULTTONEAREST);
            ::MONITORINFO monitor_info = {};
            monitor_info.cbSize = sizeof(::MONITORINFO);
            if (::GetMonitorInfoW(monitor_handle, &monitor_info) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(
                            ERROR_FUNCTION_FAILED, win32_category()
                        ),
                        "Can't get monitor information."
                    )
                );
            }

            const typename Widget::dimension_type widget_dimension =
                widget.dimension();
            const ::LONG widget_width =
                gui::to_pixels< ::LONG>(widget_dimension.first);
            const ::LONG widget_height =
                gui::to_pixels< ::LONG>(widget_dimension.second);
            if (point.x + widget_width + x_margin > monitor_info.rcWork.right)
                point.x = monitor_info.rcWork.right - widget_width - x_margin;
            if (
                point.y + widget_height + y_margin >
                monitor_info.rcWork.bottom
            )
            {
                point.y =
                    monitor_info.rcWork.bottom - widget_height - y_margin;
            }
            if (point.x - x_margin < monitor_info.rcWork.left)
                point.x = monitor_info.rcWork.left + x_margin;
            if (point.y - y_margin < monitor_info.rcWork.top)
                point.y = monitor_info.rcWork.top + y_margin;

            typedef gui::position<Position> position_traits_type;
            return position_traits_type::make(
                gui::to_unit<typename position_traits_type::left_type>(
                    point.x
                ),
                gui::to_unit<typename position_traits_type::top_type>(
                    point.y
                )
            );
        }

        /*!
            \brief Sets a dimension.

            \tparam Position  A position type.
            \tparam Widget    A widget type.
            \tparam Dimension A dimension type.

            \param widget   A widget.
            \param dimension A dimension.

            \throw When the widget cannot be moved.
        */
        template <typename Position, typename Widget, typename Dimension>
        static void set_dimension(Widget& widget, const Dimension& dimension)
        {
            assert(
                gui::dimension<Dimension>::width(dimension) > 0 &&
                gui::dimension<Dimension>::height(dimension) > 0
            );

            const Position pos = position<Position>(widget);
            const ::BOOL result = ::MoveWindow(
                std::get<0>(*widget.details()).get(),
                gui::to_pixels<int>(gui::position<Position>::left(pos)),
                gui::to_pixels<int>(gui::position<Position>::top(pos)),
                gui::to_pixels<int>(
                    gui::dimension<Dimension>::width(dimension)
                ),
                gui::to_pixels<int>(
                    gui::dimension<Dimension>::height(dimension)
                ),
                visible(widget) ? TRUE : FALSE
            );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't move widget."
                    )
                );
            }
        }

        /*!
            \brief Returns the dimension.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.

            \param widget A widget.

            \return The dimension.

            \throw std::system_error When the dimension cannot be obtained.
        */
        template <typename Dimension, typename Widget>
        static Dimension dimension(const Widget& widget)
        {
            ::RECT rectangle = {};
            if (
                ::GetWindowRect(
                    const_cast< ::HWND>(std::get<0>(*widget.details()).get()),
                    &rectangle
                ) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't get window rectangle."
                    )
                );
            }

            assert(rectangle.right - rectangle.left >= 0);
            assert(rectangle.bottom - rectangle.top >= 0);
            typedef gui::dimension<Dimension> dimension_traits_type;
            return dimension_traits_type::make(
                gui::to_unit<typename dimension_traits_type::width_type>(
                    rectangle.right - rectangle.left
                ),
                gui::to_unit<typename dimension_traits_type::height_type>(
                    rectangle.bottom - rectangle.top
                )
            );
        }

        /*!
            \brief Sets a client dimension.

            \tparam Position  A position type.
            \tparam Widget    A widget type.
            \tparam Dimension A dimension type.

            \param widget           A widget.
            \param client_dimension A client dimension.

            \throw std::system_error When a client dimension cannot be set.
        */
        template <typename Position, typename Widget, typename Dimension>
        static void set_client_dimension(
            Widget&          widget,
            const Dimension& client_dimension
        )
        {
            assert(
                gui::dimension<Dimension>::width(client_dimension) > 0 &&
                gui::dimension<Dimension>::height(client_dimension) > 0
            );

            const Position pos = position<Position>(widget);
            const ::LONG_PTR window_style =
                ::GetWindowLongPtrW(
                    std::get<0>(*widget.details()).get(), GWL_STYLE
                );
            const ::LONG_PTR extended_window_style =
                ::GetWindowLongPtrW(
                    std::get<0>(*widget.details()).get(), GWL_EXSTYLE
                );
            const ::LONG left =
                gui::to_pixels< ::LONG>(gui::position<Position>::left(pos));
            const ::LONG top =
                gui::to_pixels< ::LONG>(gui::position<Position>::top(pos));
            const ::LONG width =
                gui::to_pixels< ::LONG>(
                    gui::dimension<Dimension>::width(client_dimension)
                );
            const ::LONG height =
                gui::to_pixels< ::LONG>(
                    gui::dimension<Dimension>::height(client_dimension)
                );
            ::RECT rectangle = { left, top, left + width, top + height };
            if (
                ::AdjustWindowRectEx(
                    &rectangle,
                    static_cast< ::DWORD>(window_style),
                    FALSE,
                    static_cast< ::DWORD>(extended_window_style)
                ) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't adjust window rectangle."
                    )
                );
            }

            assert(rectangle.right - rectangle.left > 0);
            assert(rectangle.bottom - rectangle.top > 0);
            const ::BOOL result = ::MoveWindow(
                std::get<0>(*widget.details()).get(),
                rectangle.left,
                rectangle.top,
                rectangle.right - rectangle.left,
                rectangle.bottom - rectangle.top,
                visible(widget) ? TRUE : FALSE
            );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't move window."
                    )
                );
            }
        }

        /*!
            \brief Returns the client dimension.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.

            \param widget A widget.

            \return The client dimension.

            \throw std::system_error When the client dimension cannot be
                                     obtained.
        */
        template <typename Dimension, typename Widget>
        static Dimension client_dimension(const Widget& widget)
        {
            ::RECT rectangle = {};
            if (
                ::GetClientRect(
                    const_cast< ::HWND>(std::get<0>(*widget.details()).get()),
                    &rectangle
                ) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't get client rectangle."
                    )
                );
            }

            assert(rectangle.right - rectangle.left > 0);
            assert(rectangle.bottom - rectangle.top > 0);
            typedef gui::dimension<Dimension> dimension_traits_type;
            return dimension_traits_type::make(
                gui::to_unit<typename dimension_traits_type::width_type>(
                    rectangle.right - rectangle.left
                ),
                gui::to_unit<typename dimension_traits_type::height_type>(
                    rectangle.bottom - rectangle.top
                )
            );
        }

        /*!
            \brief Sets a text.

            \tparam Widget  A widget type.
            \tparam String  A string type.
            \tparam Encoder An eocder type.

            \param widget  A widget.
            \param text    A text.
            \param encoder An encoder.

            \throw std::system_error When the text cannot be set.
        */
        template <typename Widget, typename String, typename Encoder>
        static void set_text(
            Widget&        widget,
            String&&       text,
            const Encoder& encoder
        )
        {
            const ::BOOL result = ::SetWindowTextW(
                std::get<0>(*widget.details()).get(),
                encoder.encode(std::forward<String>(text)).c_str()
            );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't set text!"
                    )
                );
            }
        }

        /*!
            \brief Retuns the text.

            \tparam String  A string type.
            \tparam Widget  A widget type.
            \tparam Encoder An eocder type.

            \param widget  A widget.
            \param encoder An encoder.

            \return The text.
        */
        template <typename String, typename Widget, typename Encoder>
        static String text(const Widget& widget, const Encoder& encoder)
        {
            const int length =
                ::GetWindowTextLengthW(
                    const_cast< ::HWND>(std::get<0>(*widget.details()).get())
                );
            if (length == 0) return String();

            std::vector<wchar_t> text(length + 1, L'\0');
            ::GetWindowTextW(
                const_cast< ::HWND>(std::get<0>(*widget.details()).get()),
                text.data(),
                length + 1
            );

            return encoder.decode(
                std::wstring(text.begin(), text.begin() + length)
            );
        }

        /*!
            \brief Sets a font.

            \tparam Widget A widget type.
            \tparam Font   A font type.

            \param widget A widget.
            \param font   A font.

            \throw std::system_error When the font cannot be set.
        */
        template <typename Widget, typename Font>
        static void set_font(Widget& widget, const Font& font)
        {
            const ::HFONT previous_font_handle =
                reinterpret_cast< ::HFONT>(
                    ::SendMessageW(
                        std::get<0>(*widget.details()).get(), WM_GETFONT, 0, 0
                    )
                );

            ::LOGFONTW log_font = {
                -static_cast< ::LONG>(font.size()),
                0,
                0,
                0,
                font.bold() ? FW_BOLD : FW_NORMAL,
                font.italic() ? TRUE : FALSE,
                font.underline() ? TRUE : FALSE,
                font.strikeout() ? TRUE : FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                L""
            };
            assert(font.family().size() < LF_FACESIZE);
            std::copy(
                font.family().begin(),
                font.family().end(),
                log_font.lfFaceName
            );
            log_font.lfFaceName[font.family().size()] = L'\0';
            const ::HFONT font_handle = ::CreateFontIndirectW(&log_font);
            if (!font_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(
                            ERROR_FUNCTION_FAILED, win32_category()
                        ),
                        "Can't create font."
                    )
                );
            }
            ::SendMessageW(
                std::get<0>(*widget.details()).get(),
                WM_SETFONT,
                reinterpret_cast< ::WPARAM>(font_handle),
                MAKELPARAM(TRUE, 0)
            );

            if (
                previous_font_handle &&
                ::DeleteObject(previous_font_handle) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(
                            ERROR_FUNCTION_FAILED, win32_category()
                        ),
                        "Can't delete previous font."
                    )
                );
            }
        }

        /*!
            \brief Retuns the font.

            \tparam Font   A font type.
            \tparam Widget A widget type.

            \param widget A widget.

            \return The font.

            \throw std::system_error When the font cannot be obtained.
        */
        template <typename Font, typename Widget>
        static Font font(const Widget& widget)
        {
            ::HFONT font_handle =
                reinterpret_cast< ::HFONT>(
                    ::SendMessageW(
                        const_cast< ::HWND>(
                            std::get<0>(*widget.details()).get()
                        ),
                        WM_GETFONT,
                        0,
                        0
                    )
                );
            if (!font_handle)
            {
                font_handle =
                    reinterpret_cast< ::HFONT>(::GetStockObject(SYSTEM_FONT));
            }

            ::LOGFONTW log_font;
            const int byte_count =
                ::GetObjectW(font_handle, sizeof(::LOGFONTW), &log_font);
            if (byte_count == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(
                            ERROR_FUNCTION_FAILED, win32_category()
                        ),
                        "Can't get log font."
                    )
                );
            }

            return Font(
                log_font.lfFaceName,
                log_font.lfHeight < 0 ?
                    -log_font.lfHeight : log_font.lfHeight,
                log_font.lfWeight >= FW_BOLD,
                log_font.lfItalic != FALSE,
                log_font.lfUnderline != FALSE,
                log_font.lfStrikeOut != FALSE
            );
        }

        /*!
            \brief Returns the children.

            \tparam Child A child type.
            \tparam Widget A widget type.

            \param widget A widget.

            \return The children.
        */
        template <typename Child, typename Widget>
        static std::vector<typename cpp11::reference_wrapper<Child>::type>
        children(Widget& widget)
        {
            std::vector<
                typename cpp11::reference_wrapper<Child>::type
            > children;

            ::EnumChildWindows(
                const_cast< ::HWND>(std::get<0>(*widget.details()).get()),
                enum_child_procedure<Child>,
                reinterpret_cast< ::LPARAM>(&children)
            );

            return children;
        }

        /*!
            \brief Repaints a widget.

            \tparam Widget A widget type.

            \param widget A widget.

            \throw std::system_error When the widget cannot be repainted.
        */
        template <typename Widget>
        static void repaint(Widget& widget)
        {
            if (
                ::InvalidateRect(
                    std::get<0>(*widget.details()).get(), NULL, TRUE
                ) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(
                            ERROR_FUNCTION_FAILED, win32_category()
                        ),
                        "Can't repaint a widget."
                    )
                );
            }
        }

        /*!
            \brief Uses a widget canvas.

            \tparam Widget   A widget type.
            \tparam Canvas   A canvas type.
            \tparam Result   A result type.
            \tparam Function A function type.

            \param widget   A widget.
            \param function A function.

            \return A result.
        */
        template <
            typename Canvas,
            typename Result,
            typename Widget,
            typename Function
        >
        static Result use_canvas(
            const Widget&  widget,
            const Function function
        )
        {
            const ::HWND window_handle =
                const_cast< ::HWND>(std::get<0>(*widget.details()).get());
            const ::HDC device_context_handle = ::GetDC(window_handle);
            BOOST_SCOPE_EXIT((window_handle)(device_context_handle))
            {
                ::ReleaseDC(window_handle, device_context_handle);
            } BOOST_SCOPE_EXIT_END;
            Canvas canvas(device_context_handle);

            return function(canvas);
        }

        /*!
            \brief Activates a widget.

            \tparam Widget A widget type.

            \param widget A widget.
        */
        template <typename Widget>
        static void activate(Widget& widget)
        {
            ::SetActiveWindow(std::get<0>(*widget.details()).get());
        }

        /*!
            \brief Assigns a menu bar on a widget.

            \tparam Widget   A widget type.
            \tparam MenuBase A menu base type.

            \param widget A widget.
            \param menu   A menu.
                          It may be uninitialized to remove a menu bar.

            \throw std::system_error When a menu bar cannot be set.
        */
        template <typename Widget, typename MenuBase>
        static void set_menu_bar(
            Widget&                                 widget,
            const boost::optional<const MenuBase&>& menu = boost::none
        )
        {
            const ::BOOL result =
                ::SetMenu(
                    std::get<0>(*widget.details()).get(),
                    menu ? &*menu->details()->second : NULL
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't set a menu bar."
                    )
                );
            }

            if (
                menu &&
                ::DrawMenuBar(std::get<0>(*widget.details()).get()) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't draw the menu bar."
                    )
                );
            }
        }

        /*!
            \brief Checks whether a widget accepts a focus.

            \tparam Widget A widget type.

            \param widget A widget.

            \retval true  When the widget accepts a focus.
            \retval false Otherwise.

            \throw std::system_error When the focusable status cannot be
                                     obtained.
        */
        template <typename Widget>
        static bool focusable(Widget& widget)
        {
            const ::LONG style =
                ::GetWindowLongW(
                    std::get<0>(*widget.details()).get(), GWL_STYLE
                );
            if (style == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't get focusable status."
                    )
                );
            }
            return (style & WS_TABSTOP) != 0;
        }

        /*!
            \brief Sets whether a control accepts a focus.

            \tparam Widget A widget type.

            \param widget    A widget.
            \param focusable True when the widget accepts a focus.

            \throw std::system_error When a focusable status cannot be set.
        */
        template <typename Widget>
        static void set_focusable(Widget& widget, const bool focusable)
        {
            ::LONG style =
                ::GetWindowLongW(
                    std::get<0>(*widget.details()).get(), GWL_STYLE
                );
            if (style == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't get focusable status."
                    )
                );
            }

            ::DWORD unsigned_style = style;
            if (focusable)
                unsigned_style |= WS_TABSTOP;
            else
                unsigned_style &= ~WS_TABSTOP;
            style = unsigned_style;

            if (
                ::SetWindowLongW(
                    std::get<0>(*widget.details()).get(), GWL_STYLE, style
                ) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't set focusable status."
                    )
                );
            }
        }

        /*!
            \brief Checks whether a widget is read-only.

            \tparam Widget A widget type.

            \param widget A widget.

            \retval true  When the widget is read-only.
            \retval false Otherwise.

            \throw std::system_error When the read-only status cannot be
                                     obtained.
        */
        template <typename Widget>
        static bool read_only(Widget& widget)
        {
            const ::LONG style =
                ::GetWindowLongW(
                    std::get<0>(*widget.details()).get(), GWL_STYLE
                );
            if (style == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't get read-only status."
                    )
                );
            }
            return (style & ES_READONLY) != 0;
        }

        /*!
            \brief Sets whether a widget is read-only.

            \tparam Widget A widget type.

            \param widget    A widget.
            \param read_only True when the widget is read-only.

            \throw std::system_error When the read-only status cannot be set.
        */
        template <typename Widget>
        static void set_read_only(Widget& widget, const bool read_only)
        {
            const ::LRESULT result =
                ::SendMessageW(
                    std::get<0>(*widget.details()).get(),
                    EM_SETREADONLY,
                    read_only ? TRUE : FALSE,
                    0
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't set read-only status."
                    )
                );
            }
        }

        /*!
            \brief Closes a widget.

            \tparam Widget A widget type.

            \param widget A widget.

            \throw std::system_error When the widget cannot be closed.
        */
        template <typename Widget>
        static void close(Widget& widget)
        {
            const ::BOOL result =
                ::PostMessageW(
                    std::get<0>(*widget.details()).get(), WM_CLOSE, 0, 0
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't close the widget."
                    )
                );
            }
        }

        /*!
            \brief Opens a target.

            \tparam Widget A widget type.
            \tparam String A string type.

            \param widget A widget.
            \param target A target.

            \throw std::system_error When the target cannot be opened.
        */
        template <typename Widget, typename String>
        static void open_target(Widget& widget, const String& target)
        {
            const ::HINSTANCE result =
                ::ShellExecuteW(
                    widget.has_parent() ?
                        std::get<0>(*widget.root_ancestor().details()).get() :
                        NULL,
                    L"open",
                    target.c_str(),
                    NULL,
                    NULL,
                    SW_SHOWNORMAL
                );
            if (reinterpret_cast< ::UINT_PTR>(result) <= 32)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(
                            reinterpret_cast< ::UINT_PTR>(result),
                            win32_category()
                        ),
                        "Can't open target."
                    )
                );
            }
        }

        /*!
            \brief Returns the window property key.

            This function is for an internal use.

            \return The window property key.
        */
        static const std::wstring& property_key_for_cpp_instance()
        {
            static const std::wstring singleton(L"C++ Instance");
            return singleton;
        }

        /*!
            \brief Returns a pointer to a widget by a widget handle.

            This function is for an internal use.

            \tparam Widget A widget type.

            \param widget_handle A widget handle.

            \return A pointer to a widget.
        */
        template <typename Widget>
        static Widget* p_widget_from(const ::HWND widget_handle)
        {
            return reinterpret_cast<Widget*>(
                ::GetPropW(
                    widget_handle, property_key_for_cpp_instance().c_str()
                )
            );
        }


    private:
        // static functions

        static const std::wstring& window_class_name()
        {
            static const std::wstring singleton = L"tetengo2_window";
            return singleton;
        }

        static const std::wstring& dialog_class_name()
        {
            static const std::wstring singleton = L"tetengo2_dialog";
            return singleton;
        }

        static bool window_class_is_registered(
            const std::wstring& window_class_name,
            const ::HINSTANCE   instance_handle
        )
        {
            ::WNDCLASSEXW window_class = {};
            const ::BOOL result = ::GetClassInfoExW(
                instance_handle, window_class_name.c_str(), &window_class
            );

            return result != 0;
        }

        template <typename Widget>
        static void register_window_class_for_window(
            const ::HINSTANCE instance_handle
        )
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure<Widget>;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = 0;
            window_class.hInstance = instance_handle;
            window_class.hIcon = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OIC_WINLOGO),
                    IMAGE_ICON,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hIconSm = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OIC_WINLOGO),
                    IMAGE_ICON,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hCursor = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OCR_NORMAL),
                    IMAGE_CURSOR,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hbrBackground = reinterpret_cast< ::HBRUSH>(
                ::GetSysColorBrush(COLOR_WINDOW)
            );
            window_class.lpszMenuName = NULL;
            window_class.lpszClassName = window_class_name().c_str();

            const ::ATOM atom = ::RegisterClassExW(&window_class);
            if (!atom)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't register a window class for a window!"
                    )
                );
            }
        }

        template <typename Widget>
        static void register_window_class_for_dialog(
            const ::HINSTANCE instance_handle
        )
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure<Widget>;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = DLGWINDOWEXTRA;
            window_class.hInstance = instance_handle;
            window_class.hIcon = NULL;
            window_class.hIconSm = NULL;
            window_class.hCursor = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OCR_NORMAL),
                    IMAGE_CURSOR,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hbrBackground = reinterpret_cast< ::HBRUSH>(
                ::GetSysColorBrush(COLOR_3DFACE)
            );
            window_class.lpszMenuName = NULL;
            window_class.lpszClassName = dialog_class_name().c_str();

            const ::ATOM atom = ::RegisterClassExW(&window_class);
            if (!atom)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't register a window class for a dialog!"
                    )
                );
            }
        }

        static void delete_system_menus(const ::HWND widget_handle)
        {
            const ::HMENU menu_handle = ::GetSystemMenu(widget_handle, FALSE);
            if (!menu_handle) return;

            if (
                ::DeleteMenu(menu_handle, SC_SIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_MAXIMIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_MINIMIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_RESTORE, MF_BYCOMMAND) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't delete system menu item."
                    )
                );
            }
        }

        template <typename Widget>
        static ::LRESULT CALLBACK window_procedure(
            const ::HWND   hWnd,
            const ::UINT   uMsg,
            const ::WPARAM wParam,
            const ::LPARAM lParam
        )
        TETENGO2_CPP11_NOEXCEPT
        {
            try
            {
                Widget* const p_widget = p_widget_from<Widget>(hWnd);
                if (p_widget)
                {
                    return window_procedure_impl(
                        *p_widget, uMsg, wParam, lParam
                    );
                }
                else
                {
                    return ::CallWindowProcW(
                        ::DefWindowProcW, hWnd, uMsg, wParam, lParam
                    );
                }
            }
            catch (const boost::exception& e)
            {
                (typename Widget::alert_type(hWnd))(e);
                return 0;
            }
            catch (const std::exception& e)
            {
                (typename Widget::alert_type(hWnd))(e);
                return 0;
            }
            catch (...)
            {
                (typename Widget::alert_type(hWnd))();
                return 0;
            }
        }

        template <typename Widget>
        static ::LRESULT window_procedure_impl(
            const Widget&   widget,
            const ::UINT    uMsg,
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            typedef
                typename Widget::message_handler_map_type::const_iterator
                map_iterator;
            const map_iterator found =
                widget.message_handler_map().find(uMsg);
            if (found != widget.message_handler_map().end())
            {
                BOOST_FOREACH (
                    const typename Widget::message_handler_type& handler,
                    found->second
                )
                {
                    const boost::optional< ::LRESULT> o_result =
                        handler(wParam, lParam);
                    if (o_result) return *o_result;
                }
            }

            return ::CallWindowProcW(
                std::get<1>(*widget.details()),
                const_cast< ::HWND>(std::get<0>(*widget.details()).get()),
                uMsg,
                wParam,
                lParam
            );
        }

        template <typename Widget>
        static ::WNDPROC replace_window_procedure(const ::HWND handle)
        {
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(push)
#    pragma warning(disable: 4244)
#endif
            const ::WNDPROC proc = window_procedure<Widget>;
            const ::LONG_PTR result =
                ::SetWindowLongPtrW(
                    handle,
                    GWLP_WNDPROC,
                    reinterpret_cast< ::LONG_PTR>(proc)
                );
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(pop)
#endif
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't replace window procedure."
                    )
                );
            }

            return reinterpret_cast< ::WNDPROC>(result);
        }

        template <typename Child>
        static ::BOOL CALLBACK enum_child_procedure(
            const ::HWND   window_handle,
            const ::LPARAM parameter
        )
        {
            std::vector<typename cpp11::reference_wrapper<Child>::type>* const
            p_children =
                reinterpret_cast<
                    std::vector<
                        typename cpp11::reference_wrapper<Child>::type
                    >*
                >(parameter);

            p_children->push_back(
                cpp11::ref(*p_widget_from<Child>(window_handle))
            );

            return TRUE;
        }


   };


}}}


#endif
