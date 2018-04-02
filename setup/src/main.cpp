/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cstdint> // IWYU pragma: keep
#include <exception> // IWYU pragma: keep
#include <locale> // IWYU pragma: keep
#include <stdexcept> // IWYU pragma: keep
#include <string>
#include <vector> // IWYU pragma: keep

#include <boost/filesystem.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#// prevent sort by ClangFormat
#include <CommCtrl.h>

#include <setup/encode.h>


namespace {
    const std::wstring& application_name()
    {
        static const std::wstring singleton{ L"Bobura" };
        return singleton;
    }

    const std::string& application_name_narrow()
    {
        static const std::string singleton{ "Bobura" };
        return singleton;
    }

    const std::wstring& message_box_title()
    {
        static const std::wstring singleton{ application_name() + L" Setup" };
        return singleton;
    }

    const std::wstring& msi_prefix()
    {
        static const std::wstring singleton{ L"bobura." };
        return singleton;
    }

    const std::wstring& msi_suffix()
    {
        static const std::wstring singleton{ L".msi" };
        return singleton;
    }

    std::string locale_info(const ::LCID id, const ::LCTYPE type)
    {
        const auto length = ::GetLocaleInfoA(id, type, nullptr, 0);
        if (length == 0)
            throw std::runtime_error("Can't get locale info.");

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

    std::wstring detect_language()
    {
        if (ui_locale_name().find("Japanese_") == 0)
            return L"ja";
        else
            return {};
    }

    std::wstring detect_platform()
    {
        ::SYSTEM_INFO info{};
        ::GetNativeSystemInfo(&info);
        if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
            return L"x64";
        else if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
            return L"Win32";
        else
            return {};
    }

    boost::filesystem::path msi_path(const boost::filesystem::path& base_path_, const std::wstring& platform)
    {
        return base_path_ / boost::filesystem::path(msi_prefix() + platform + msi_suffix());
    }

    std::wstring build_parameters(
        const std::wstring&            language,
        const std::wstring&            platform,
        const boost::filesystem::path& base_path_)
    {
        std::wstring parameters{};

        parameters += L"/i ";
        parameters += std::wstring{ L"\"" } + msi_path(base_path_, platform).c_str() + L"\" ";
        if (!language.empty())
            parameters += L"TRANSFORMS=\":" + language + L".mst\"";

        return parameters;
    }

    boost::filesystem::path base_path()
    {
        std::vector<wchar_t> path_buffer(MAX_PATH, 0);
        const ::DWORD        path_length = ::GetModuleFileNameW(nullptr, path_buffer.data(), path_buffer.size());
        if (path_length == 0)
            throw std::runtime_error("Cannot get the path where the installer exists.");

        boost::filesystem::path path(path_buffer.begin(), path_buffer.begin() + path_length);

        return path.parent_path();
    }

    void launch_msi(const std::wstring& language, const std::wstring& platform, const int window_state)
    {
        if (platform.empty())
        {
            throw std::runtime_error(
                std::string{ "Cannot install " } + application_name_narrow() + " to this platform.");
        }

        const boost::filesystem::path base_path_ = base_path();

        const std::wstring parameters = build_parameters(language, platform, base_path_);

        const ::HINSTANCE instance_handle =
            ::ShellExecuteW(nullptr, nullptr, L"msiexec", parameters.c_str(), base_path_.c_str(), window_state);
        if (reinterpret_cast<std::intptr_t>(instance_handle) <= 32)
            throw std::runtime_error("Cannot launch the msi file.");
    }

    void show_error_message(const ::HINSTANCE instance_handle, const std::string& message = {}) noexcept
    {
        try
        {
            ::TaskDialog(
                nullptr,
                instance_handle,
                message_box_title().c_str(),
                setup::encode(message).c_str(),
                nullptr,
                TDCBF_CLOSE_BUTTON,
                nullptr,
                nullptr);
        }
        catch (...)
        {
        }
    }
}


/*!
    \brief The entry point of the application.

    \param hInstance     A handle to the instance.
    \param hPrevInstance Not used.
    \param lpCmdLine     Not used.
    \param nCmdShow      A window state.

    \return The exit status code.
*/
int WINAPI wWinMain(
    const ::HINSTANCE                  hInstance,
    [[maybe_unused]] const ::HINSTANCE hPrevInstance,
    [[maybe_unused]] const ::LPWSTR    lpCmdLine,
    const int                          nCmdShow)
{
    try
    {
        std::locale::global(std::locale(""));

        const std::wstring language = detect_language();
        const std::wstring platform = detect_platform();

        launch_msi(language, platform, nCmdShow);

        return 0;
    }
    catch (const std::exception& e)
    {
        show_error_message(hInstance, e.what());
        return 1;
    }
    catch (...)
    {
        show_error_message(hInstance);
        return 1;
    }
}
