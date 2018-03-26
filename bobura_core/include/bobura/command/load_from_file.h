/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_LOADFROMFILE_H)
#define BOBURA_COMMAND_LOADFROMFILE_H

#include <memory>

#include <boost/filesystem.hpp>

#include <bobura/command/command_base.h>
#include <bobura/load_save/load_from_file.h>


namespace bobura::command {
    /*!
        \brief The class template for a load-from-file command.

        \tparam Traits         A traits type.
        \tparam LoadSaveTraits A loading and saving processing traits type.
    */
    template <typename Traits, typename LoadSaveTraits>
    class load_from_file : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The loading and saving processing traits type.
        using load_save_traits_type = LoadSaveTraits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The abstract window type.
        using abstract_window_type = typename base_type::abstract_window_type;

        //! The model type.
        using model_type = typename base_type::model_type;

        //! The file loading type.
        using load_from_file_type = load_save::load_from_file<load_save_traits_type>;

        //! The parameter type.
        class parameter_type : public parameter_base
        {
        public:
            /*!
                \brief Creates a parameter.

                \param path A path.
            */
            explicit parameter_type(boost::filesystem::path path);

            /*!
                \brief Destroys the parameter.
            */
            virtual ~parameter_type() noexcept;

            /*!
                \brief Returns the path.

                \return The path.
            */
            const boost::filesystem::path& path() const;

        private:
            boost::filesystem::path m_path;
        };


        // constructors and destructor

        /*!
            \brief Creates a load-from-file command.

            \param load_from_file A file loading.
        */
        explicit load_from_file(const load_from_file_type& load_from_file);

        /*!
            \brief Destroys the load-from-file command.
        */
        virtual ~load_from_file() noexcept;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool enabled_impl(const model_type& model) const override;

        virtual void execute_impl(model_type& model, abstract_window_type& parent) const override;

        virtual void
        execute_impl(model_type& model, abstract_window_type& parent, const parameter_base& parameter) const override;
    };
}


#endif
