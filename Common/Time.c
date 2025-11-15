#include "BasicTypes.h"
#include <string.h>
#include <time.h>


Time currentTime() {
  Time now;
  time(&now);
  return now;
}

string currentTimeInString() {
    Time now;
    time(&now);
    string result = _strdup(ctime(&now));  // problem here
    return result;
}
