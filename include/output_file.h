#ifndef _OUTPUT_FILE_H_
#define _OUTPUT_FILE_H_
#pragma once
#include <glm.hpp>
#include <vector>

void write_ppm(char const* path, std::vector<std::vector<glm::vec3>> const& data, int width, int height);

#endif //_OUTPUT_FILE_H_