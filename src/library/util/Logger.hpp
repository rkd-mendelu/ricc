#pragma once

#if DEBUG_MODE
#define DEBUG(x)                                                    \
  do {                                                              \
    std::cerr << __FILENAME__ << ":" << __func__ << ":" << __LINE__ \
              << " :: " << x << std::endl;                          \
  } while (0)
#else
#define DEBUG(x) \
  do {           \
  } while (0)
#endif
