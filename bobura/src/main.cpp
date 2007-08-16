/*! \file
	\brief The definition of the main function.

	Copyright (C) 2007 kaoru

	$Id$
*/

#include <exception>

#include <boost/program_options.hpp>

#define OEMRESOURCE
#include <windows.h>

#include "bobura.configuration.h"


namespace
{
	/*!
		Creates the application and runs it.

		\param parsed_options The parsed command line options.

		\return The exit status code.
	*/
	int run_application(
		const boost::program_options::wparsed_options& parsed_options
	)
	{
		boost::program_options::variables_map option_values;
		boost::program_options::store(parsed_options, option_values);
		boost::program_options::notify(option_values);

		return bobura::configuration(option_values).create_bobura()->run();
	}
}

/*!
	The entry point of the application.

	\param lpCmdLine The command line arguments.

	\return The exit status code.
*/
int WINAPI wWinMain(
	const ::HINSTANCE /* hInstance */,     //!< Not used.
	const ::HINSTANCE /* hPrevInstance */, //!< Not used.
	const ::LPWSTR    lpCmdLine,
	const int         /* nCmdShow */       //!< Not used.
)
throw ()
{
	try
	{
		return ::run_application(
			boost::program_options::wcommand_line_parser(
				boost::program_options::split_winmain(lpCmdLine)
			).options(bobura::configuration::options()).run()
		);
	}
	catch (const std::exception& e)
	{
		bobura::configuration::gui_factory_type::show_fatal_error(NULL, e);
		return 1;
	}
	catch (...)
	{
		bobura::configuration::gui_factory_type::show_fatal_error(NULL);
		return 2;
	}
}
