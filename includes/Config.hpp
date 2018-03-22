#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <string>

namespace Config{
    enum type{EUC_2D,GEO,ATT};

    const unsigned GENERATION_LIMIT{10};
    const unsigned N_BEST{3};

    extern type TYPE;

    //argumentos do algoritmo
    extern unsigned ID;
    extern std::string NAME;
    extern std::string LIB_PATH;
    extern unsigned NEW_POP_TYPE;
    extern double LK_PERCENTAGE;
    extern unsigned POP_SIZE;
}


#endif