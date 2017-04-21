/* PAM native handler entrypoints. Keep these dumb so the logic can
 * be tested.
 */
#include <security/pam_modules.h>
#include <string>
#include <memory>
#include <vector>

#include "request.h"
#include "dual_control.h"

extern dual_control dc;

PAM_EXTERN int pam_sm_authenticate (pam_handle_t *pamh, int flags, int argc,
                                    const char **argv)
{
    return dc.authenticate (pam_request (pamh, flags, argc, argv));
}

PAM_EXTERN int pam_sm_setcred (pam_handle_t *pamh, int flags, int argc,
                               const char **argv)
{
    return dc.setcred (pam_request ( pamh, flags, argc, argv));
}

