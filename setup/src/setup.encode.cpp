/*! \file
    \brief String encoding conversion

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <string>

#include <tetengo2.h>

#include <setup/encode.h>


namespace setup
{
    namespace
    {
        using encoder_type =
            tetengo2::text::encoder<tetengo2::text::encoding::ascii, tetengo2::text::encoding::locale<std::wstring>>;

        const encoder_type& encoder()
        {
            static const encoder_type singleton{};
            return singleton;
        }

    }


    std::wstring encode(const std::string& string)
    {
        return encoder().encode(string);
    }


}
