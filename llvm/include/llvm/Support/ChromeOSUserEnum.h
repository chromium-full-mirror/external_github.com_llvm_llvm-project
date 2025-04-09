#ifndef LLVM_SUPPORT_CHROMEOSUSERENUM_H
#define LLVM_SUPPORT_CHROMEOSUSERENUM_H

#include "llvm/ADT/StringRef.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

// N.B., To minimize the chance of merge conflicts in cmake files, this is
// header-only. The 'inline's below are written for linkage, not performance.
namespace chromeos_user_enum {
const char ACK_ENV_VAR[] = "CROSTC_IS_AWARE_OF_THIS_USECASE";

inline bool isExecutingInPortableEnv() {
  // TODO: This may be too tricky?
  // This env var is set by shell scripts that invoke portable toolchain
  // binaries.
  return getenv("LD_ARGV0_REL") != nullptr;
}

inline bool shouldCheckForCmdlineFlag() {
  return isExecutingInPortableEnv() && getenv(ACK_ENV_VAR) == nullptr;
}

[[noreturn]] inline void complainAboutNoAckAndDie(llvm::StringRef flagToPass) {
  std::string s;
  s += "Hi!\n";
  s += "\n";
  s += "We (the CrOS toolchain team) are trying to identify\n";
  s += "users of this toolchain outside of ChromeOS.\n";
  s += "\n";
  s += "If your team/use-case isn't listed on b/396436337,\n";
  s += "please comment on that bug to notify us of your usage,\n";
  s += "and give us info on how to best contact you. If you\n";
  s += "can't access that bug, please instead email\n";
  s += "chromeos-toolchain@google.com with this information.\n";
  s += "\n";
  s += "After you've done this, you can fully bypass this\n";
  s += "message by setting the env var '";
  s += ACK_ENV_VAR;
  s += "=1'.\n";
  s += "\n";
  if (!flagToPass.empty()) {
    s += "Alternatively, you can pass the flag '";
    s += flagToPass.str();
    s += "' to\n";
    s += "this binary\n";
    s += "\n";
  }
  s += "Thanks for helping us determine who's using our tooling!\n";
  fprintf(stderr, s.c_str());
  exit(1);
}
} // namespace chromeos_user_enum

#endif // LLVM_SUPPORT_CHROMEOSUSERENUM_H
