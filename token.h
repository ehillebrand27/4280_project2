
#include <string>

enum tokenID {t1_tk, t2_tk, t3_tk, EOFTk};

struct token {
    tokenID id;
    std::string instance;
    int line;
};