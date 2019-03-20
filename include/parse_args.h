#ifndef _PARSE_ARGS_H_
#define _PARSE_ARGS_H_
#pragma once

#include <cstddef>

struct argsResult
{
    size_t width = 0;
    size_t height = 0;
    const char* outputPath = "";
};

argsResult parseCmdlineArgs(int argc, char const *argv[]);

#endif //_PARSE_ARGS_H_