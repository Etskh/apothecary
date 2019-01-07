
#include "Guid.hpp"


Guid createGuid() {
    static Guid guid = 0xFF;
    return ++guid;
}
