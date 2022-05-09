#include <iostream>

#include "engine.h"
int main(int argc, char** argv) {
    int ret = 0;
    engine eng;
    if (eng.Init()) {
        eng.Run();
        eng.EngineCleanup();
    }
    else {
        ret = 1;
    }
    return ret;
}
