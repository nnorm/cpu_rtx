#include <parse_args.h>
#include <cstdio>
#include <cassert>
#include <sstream>

argsResult parseCmdlineArgs(int argc, char const *argv[])
{
    if(argc < 3)
    {
        std::printf("Invalid usage! \n");
        std::printf("\tUsage: cpu_rtx.ex WIDTH HEIHGT [output file path]\n");
        assert(false);
    }
    //else
    {
        argsResult res;
        std::stringstream sstrW(argv[1]), sstrH(argv[2]);
        sstrW >> res.width;
        sstrH >> res.height;
        if(argc > 3)
            res.outputPath = argv[3];
        else
            res.outputPath = "output.ppm";
        return res;
    }
}