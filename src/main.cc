// Copyright 2006 Google Inc. All Rights Reserved.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//      http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// sat.cc : a stress test for stressful testing

#include "sattypes.h"
#include "sat.h"

/*Updated by Eric in 2019*/

int main(int argc, char **argv) {
  Sat *sat = SatFactory();
  if (sat == NULL) {
    logprintf(0, "Process Error: failed to allocate Sat object\n");
    return 255;
  }

  if (!sat->ParseArgs(argc, argv)) {
    logprintf(0, "Process Error: Sat::ParseArgs() failed\n");
    sat->bad_status();
  } else if (!sat->Initialize()) {
    logprintf(0, "Process Error: Sat::Initialize() failed\n");
    sat->bad_status();
  } else if (!sat->Run()) {
    logprintf(0, "Process Error: Sat::Run() failed\n");
    sat->bad_status();
  }
  sat->PrintResults();
  if (!sat->Cleanup()) {
    logprintf(0, "Process Error: Sat::Cleanup() failed\n");
    sat->bad_status();
  }

  int retval;
  if (sat->status() != 0) {
    logprintf(0, "Process Error: Fatal issue encountered. See above logs for "
              "details.\n");
    retval = 1;
  } else if (sat->errors() != 0) {
    retval = 1;
  } else {
    retval = 0;
  }

  delete sat;
  return retval;
}
