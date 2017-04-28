[![Build Status](https://travis-ci.org/cjdev/dual-control.svg?branch=master)](https://travis-ci.org/cjdev/dual-control)

# Dual Control
Dual Control is a PAM module that requires a user to input a generated token from another user before being granted sudo access. The module also requires that the user input the reason for his or her access request and, via `syslog`, captures all this information for future reference.

At **CJ Engineering**, we will be implementing Dual Control on our production boxes to ensure that a single engineer cannot gain write access without meeting the above-stated requirements.

Dual Control is an open source project licensed under the [GNU General Public License](https://github.com/cjdev/dual-control/blob/master/COPYING). As it stands, Dual Control is written only for machines running Linux. However, we graciously welcome contributions, particularly those related to portability to other operating systems.

## Status
This is in active development. The current version uses a permanent token. The final version will
use a time-based OTP.

## Install
- Obtain and install the RPM
  - build yourself using the code in /cjdev/dual-control-rpm
  - get it from a developer
- Edit the `/etc/pam.d/sudo`  (CentOS 7)
  - replace the existing auth lines with
```
auth        required      pam_env.so
auth        sufficient    pam_unix.so nullok try_first_pass
auth        requisite     pam_succeed_if.so uid >= 1000 quiet_success
auth        required      pam_deny.so
```

## Add a dual control token
- in the authorizer's account home, put the token characters in `.dual_control`

## Use
- log in with a test user that has `sudo` ability (not the vagrant account it is too
powerful)
- type `sudo bash`
- enter your password
- enter dual control token, authorizer's username + ':' + authorizer's token

