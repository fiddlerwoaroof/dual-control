#include <string>
#include <vector>
#include <security/pam_modules.h>

#include "request.h"
#include "dual_control.h"
#include "conversation.h"
#include "validator.h"

int dual_control_ifc::authenticate (const pam_request &request)
{
    return PAM_SERVICE_ERR;
}

int dual_control_ifc::setcred ( const pam_request &request)
{
    return PAM_SERVICE_ERR;
}

class impl : public dual_control_ifc
{
private:
    conversations conversations_;
    validator validator_;
    logger logger_;
public:
    impl (const dual_control_configuration &configuration);
    int authenticate (const pam_request &request);
    int setcred (const pam_request &request);
};

impl::impl (const dual_control_configuration &configuration) :
    conversations_ (configuration.conversations),
    validator_ (configuration.validator),
    logger_ (configuration.logger) {}

int impl::setcred (const pam_request &request)
{
    return PAM_SUCCESS;
}

int impl::authenticate (const pam_request &request)
{

    conversation_result conversation = conversations_.initiate_conversation();
    std::string user_name = conversation.user_name();
    std::string token = conversation.token();

    int auth_result = validator_.validate (user_name,
                                           token) ? PAM_SUCCESS : PAM_AUTH_ERR;

    logger_.log (auth_result, user_name, token);
    return auth_result;
}

dual_control create_dual_control (const dual_control_configuration
                                  &configuration)
{
    return dual_control (std::shared_ptr<dual_control_ifc> (new impl (
                             configuration)));
}

