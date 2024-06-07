namespace __lsan {

char kLSanDefaultSuppressions[] =
// ================ Leaks in third-party code ================

// False positives in libfontconfig. http://crbug.com/39050
"leak:libfontconfig\n"

// Leaks in Nvidia's libGL.
"leak:libGL.so\n"

"leak:libnssutil3\n"
"leak:libnspr4\n"
"leak:libnss3\n"
"leak:libplds4\n"
"leak:libnssckbi\n"

// XRandR has several one time leaks.
"leak:libxrandr\n"

// xrandr leak. http://crbug.com/119677
"leak:XRRFindDisplay\n"

// leak on session_manager. http://crbug.com/378805
"leak:/sbin/session_manager\n"

// leak on cryptohome. http://crbug.com/508281
"leak:/usr/sbin/cryptohome\n"

// leak on buffet. http://crbug.com/473700
//"leak:/usr/bin/buffet\n"
// End of suppressions.
;  // Please keep this semicolon.
}
