/* Copyright (C) CJ Affiliate
 *
 * You may use, distribute and modify this code under  the
 * terms of the  GNU General Public License version 2  or
 * later.
 *
 * You should have received a copy of the license with this
 * file. If not, you will find a copy in the "LICENSE" file
 * at https://github.com/cjdev/dual-control.
 */

#include <string>
#include <vector>
#include <memory>
#include <fstream>

#include "token.h"
#include "user.h"
#include "sys_fstream.h"

namespace
{
class user_token_supplier_impl : public user_token_supplier_ifc
{
private:
    fstreams fstreams_;
public:
    user_token_supplier_impl (fstreams &fstreams) :
        fstreams_ (fstreams) {}
    std::string token (user &user)
    {
        const std::string file_path (user.home_directory() + "/.dual_control");
        std::vector<char> line (7);

        fstreams::pstream stream (fstreams_.open_fstream (file_path));

        if (!stream->good()) {
            return "";
        }

        stream->getline (line.data(), line.size());
        return std::string (line.data());
    }
};
}
user_token_supplier user_token_supplier::create (fstreams &fstreams)
{
    return user_token_supplier (user_token_supplier::delegate
                                (new user_token_supplier_impl (fstreams)));
}

