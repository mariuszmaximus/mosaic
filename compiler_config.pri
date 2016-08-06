linux-g++ {
    QMAKE_CXXFLAGS += "-Wall -Wextra -Werror"
    debug {
        QMAKE_CXXFLAGS += "-fsanitize=address -fno-omit-frame-pointer"
        QMAKE_CFLAGS += "-fsanitize=address -fno-omit-frame-pointer"
        QMAKE_LFLAGS += "-fsanitize=address"
    }
}
