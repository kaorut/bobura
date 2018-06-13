/*! \file
    \brief String encoding conversion

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <string>

#include <setup/encode.h>

#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/ascii.h>
#include <tetengo2/text/encoding/encoding.h>
#include <tetengo2/text/encoding/locale.h>

#include <tetengo2.detail.base.config.cpp>
#include <tetengo2.detail.base.encoding.cpp>
#include <tetengo2.detail.base.impl_set.cpp>
#include <tetengo2.detail.windows.config.cpp>
#include <tetengo2.detail.windows.encoding.cpp>
#include <tetengo2.detail.windows.impl_set.cpp>
#include <tetengo2.detail.windows.windows_version.cpp>
#include <tetengo2.text.encoding.ascii.cpp>
#include <tetengo2.text.encoding.encoding.cpp>
#include <tetengo2.text.encoding.locale.cpp>


namespace setup {
    namespace {
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
