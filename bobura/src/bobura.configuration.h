/*! \file
	\brief The definition of bobura::configuration.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(BOBURA_CONFIGURATION_H)
#define BOBURA_CONFIGURATION_H

#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>

#include <tetengo2.gui.win32.gui_factory.h>

#include "bobura.bobura.h"


namespace bobura
{
	/*!
		\brief The class for the configuration of bobura.

		$Id$
	*/
	class configuration : private boost::noncopyable
	{
	public:
		// types

		typedef tetengo2::gui::win32::gui_factory gui_factory_type;

		typedef bobura<gui_factory_type> bobura_type;


		// static functions

		static const boost::program_options::options_description& options()
		{
			static const boost::program_options::options_description&
			singleton = make_options();

			return singleton;
		}


		// constructors and destructor

		configuration(
			const boost::program_options::variables_map& option_values
		)
		:
		m_option_values(option_values)
		{}

		~configuration()
		{}


		// functions

		std::auto_ptr<bobura_type> create_bobura()
		const
		{
			return std::auto_ptr<bobura_type>(
				new bobura_type(
					std::auto_ptr<const gui_factory_type>(
						new gui_factory_type()
					)
				)
			);
		}


	private:
		// variables

		const boost::program_options::variables_map m_option_values;


		// functions

		static const boost::program_options::options_description
		make_options()
		{
			boost::program_options::options_description options(
				"bobura"
			);
			
			options.add_options()
			("help,h", "help")
			(
				"geometry,g",
				boost::program_options::value<int>()->default_value(640),
				"geometry"
			)
			;

			return options;
		}



	};
}

#endif
