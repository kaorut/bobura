/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <exception> // IWYU pragma: keep
#include <locale>
#include <memory>
#include <stdexcept> // IWYU pragma: keep
#include <string>
#include <vector> // IWYU pragma: keep

#include <boost/exception/all.hpp> // IWYU pragma: keep
#include <boost/program_options.hpp> // IWYU pragma: keep
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/impl_set.h>
#include <tetengo2/detail/windows/gui_impl_set.h>
#include <tetengo2/detail/windows/impl_set.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/application.h>
#include <bobura/settings.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_application;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using position_type = ui_type_list_type::position_type;

    using dimension_type = ui_type_list_type::dimension_type;

    using settings_type = bobura::settings<string_type, position_type, dimension_type>;

    using application_type = bobura::application<traits_type_list_type::application_type>;


    // functions

    std::string locale_info(const ::LCID id, const ::LCTYPE type)
    {
        const auto length = ::GetLocaleInfoA(id, type, nullptr, 0);
        if (length == 0)
            BOOST_THROW_EXCEPTION(std::runtime_error("Can't get locale info."));

        std::vector<char> info(length, '\0');
        ::GetLocaleInfoA(id, type, info.data(), length);

        return info.data();
    }

    std::string ui_locale_name()
    {
        const auto   language_id = ::GetUserDefaultLangID();
        const ::LCID locale_id = MAKELCID(language_id, SORT_DEFAULT);

        return locale_info(locale_id, LOCALE_SENGLANGUAGE) + "_" + locale_info(locale_id, LOCALE_SENGCOUNTRY);
    }

    void set_locale(const tetengo2::stdalt::filesystem::path& message_directory_path)
    {
        auto p_messages_facet = std::make_unique<tetengo2::message::messages>(
            message_directory_path, std::locale(ui_locale_name().c_str()));
        const std::locale global_locale{ std::locale(""), p_messages_facet.release() };

        std::locale::global(global_locale);
    }

    int run_application(settings_type& settings)
    {
        return application_type{ settings }.run();
    }
}


/*!
    \brief The entry point of the application.

    \param hInstance     Not used.
    \param hPrevInstance Not used.
    \param lpCmdLine     Not used.
    \param nCmdShow      Not used.

    \return The exit status code.
*/
int WINAPI wWinMain(
    TETENGO2_STDALT_MAYBE_UNUSED const ::HINSTANCE hInstance,
    TETENGO2_STDALT_MAYBE_UNUSED const ::HINSTANCE hPrevInstance,
    TETENGO2_STDALT_MAYBE_UNUSED const ::LPWSTR    lpCmdLine,
    TETENGO2_STDALT_MAYBE_UNUSED const int         nCmdShow)
{
    using alert_type = ui_type_list_type::alert_type;

    tetengo2::detail::set_detail_impl_set(tetengo2::detail::windows::impl_set::instance());
    tetengo2::detail::set_gui_detail_impl_set(tetengo2::detail::windows::gui_impl_set::instance());

    try
    {
        settings_type settings{ boost::program_options::split_winmain(::GetCommandLineW()),
                                string_type{ TETENGO2_TEXT("bobura") } };

        set_locale(settings.message_directory_path());

        return ::run_application(settings);
    }
    catch (const boost::exception& e)
    {
        alert_type{}(e);
        return 1;
    }
    catch (const std::exception& e)
    {
        alert_type{}(e);
        return 1;
    }
    catch (...)
    {
        alert_type{}();
        return 2;
    }
}
