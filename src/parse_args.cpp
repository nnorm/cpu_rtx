#include <parse_args.h>
#include <stdio.h>
#include <assert.h>
#include <sstream>

argsResult parseCmdlineArgs(int argc, char const *argv[])
{
    if(argc < 3)
    {
        printf("Invalid usage! \n");
        printf("\tUsage: cpu_rtx.ex WIDTH HEIHGT [output file path]\n");
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
        
#ifdef _DEBUG
		printf("\tWidth: %zu \n\tHeight: %zu \n\tOutput path: %s\n", res.width, res.height, res.outputPath);
#endif //_DEBUG

		return res;
    }
}