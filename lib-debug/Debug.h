#define ShowMessages 1  // Set to 1 to enable debug messages, 0 to disable

#include <iostream>

#if ShowMessages
#define MSG(X) std::cout << X << std::endl;
#else
#define MSG(X)
#endif