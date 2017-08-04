// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef STATUS_H_
#define STATUS_H_

#include <cstdio>
#include <cstdlib>

namespace pik {

#ifdef PIK_ENABLE_ASSERT
#define PIK_ASSERT(condition)                                   \
  while (!(condition)) {                                        \
    printf("Pik assert failed at %s:%d\n", __FILE__, __LINE__); \
    abort();                                                    \
  }
#else
#define PIK_ASSERT(condition)
#endif

#define PIK_CHECK(condition)                                   \
  while (!(condition)) {                                       \
    printf("Pik check failed at %s:%d\n", __FILE__, __LINE__); \
    abort();                                                   \
  }

// Annotation for the location where an error condition is first noticed.
// Error codes are too unspecific to pinpoint the exact location, so we
// add a build flag that crashes and dumps stack at the actual error source.
#ifdef PIK_CRASH_ON_ERROR
inline bool PikFailure(const char* f, int l, const char* msg) {
  for (;;) {
    printf("Pik failure at %s:%d: %s", f, l, msg);
    abort();
  }
  return false;
}
#define PIK_NOTIFY_ERROR(message_string)                                \
  PikFailure(__FILE__, __LINE__, message_string);
#define PIK_FAILURE(message_string)                        \
  PikFailure(__FILE__, __LINE__, message_string);
#else
#define PIK_NOTIFY_ERROR(message_string)
#define PIK_FAILURE(message_string) false
#endif

}  // namespace pik

#endif  // STATUS_H_
