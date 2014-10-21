/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <exception>
#include <locale>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/program_options.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/application.h>
#include <bobura/settings.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using string_type = boost::mpl::at<bobura::common_type_list, bobura::type::string>::type;

    using position_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::position>::type;

    using dimension_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dimension>::type;

    using config_traits_type = boost::mpl::at<bobura::traits_type_list, bobura::type::traits::config>::type;

    using settings_type = bobura::settings<string_type, position_type, dimension_type, config_traits_type>;

    using application_type = bobura::application<string_type, position_type, dimension_type, config_traits_type>;


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
        const auto language_id = ::GetUserDefaultLangID();
        const ::LCID locale_id = MAKELCID(language_id, SORT_DEFAULT);

        return locale_info(locale_id, LOCALE_SENGLANGUAGE) + "_" + locale_info(locale_id, LOCALE_SENGCOUNTRY);
    }

    void set_locale(const boost::filesystem::path& message_directory_path)
    {
        using messages_facet_type =
            tetengo2::message::messages<
                boost::mpl::at<bobura::common_type_list, bobura::type::input_stream_iterator>::type,
                string_type,
                boost::mpl::at<bobura::common_type_list, bobura::type::size>::type,
                boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog_encoder>::type,
                boost::mpl::at<bobura::locale_type_list, bobura::type::locale::locale_name_encoder>::type
            >;
        auto p_messages_facet =
            tetengo2::stdalt::make_unique<messages_facet_type>(
                message_directory_path, std::locale(ui_locale_name().c_str())
            );
        const std::locale global_locale{ std::locale(""), p_messages_facet.release() };

        std::locale::global(global_locale);
    }

    int run_application(settings_type& settings)
    {
        return application_type(settings).run();
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
    const ::HINSTANCE hInstance,
    const ::HINSTANCE hPrevInstance,
    const ::LPWSTR    lpCmdLine,
    const int         nCmdShow
)
TETENGO2_STDALT_NOEXCEPT
{
    boost::ignore_unused(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    using alert_type =
        tetengo2::gui::alert<
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::ui_encoder>::type,
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::exception_encoder>::type,
            boost::mpl::at<bobura::detail_type_list, bobura::type::detail::alert>::type
        >;

    try
    {
        settings_type settings{
            boost::program_options::split_winmain(::GetCommandLineW()), string_type{ TETENGO2_TEXT("bobura") }
        };

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
