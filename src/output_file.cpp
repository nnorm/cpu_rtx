#include <output_file.h>

#include <assert.h>
#include <fstream>
#include <algorithm>

void write_ppm_ascii(char const* path, std::vector<std::vector<glm::vec3>> const& data, int width, int height)
{
	std::ofstream outputFile(path);
	assert("Could not open output file" && outputFile.is_open());
	
	//write header
	outputFile << "P3 " << width << " " << height << " " << "255\n";

	//write file data in plain text
	for (int py = height - 1; py >= 0; py--)
	{
		for (int px = 0; px < width; px++)
		{
			glm::vec3 color = data[px][py];
			color.r = std::min(std::max(0.0f, color.r), 1.0f);
			color.g = std::min(std::max(0.0f, color.g), 1.0f);
			color.b = std::min(std::max(0.0f, color.b), 1.0f);
			color *= 255.99f;
			glm::ivec3 ic = glm::ivec3(int(color.x), int(color.y), int(color.z));
			outputFile << ic.r << " " << ic.g << " " << ic.b << " \n";
		}
	}

	outputFile << std::endl;

	//close file
	outputFile.close();
}

void write_ppm_binary(char const * path, std::vector<std::vector<glm::vec3>> const & data, int width, int height)
{
	std::ofstream outputFile(path, std::ofstream::binary);
	assert("Could not open output file" && outputFile.is_open());
	
	//write header
	outputFile << "P6 " << width << " " << height << " " << "255\n";

	//compute binary color data and write
	for (int py = height - 1; py >= 0; py--)
	{
		for (int px = 0; px < width; px++)
		{
			glm::vec3 color = data[px][py];
			color.r = std::min(std::max(0.0f, color.r), 1.0f);
			color.g = std::min(std::max(0.0f, color.g), 1.0f);
			color.b = std::min(std::max(0.0f, color.b), 1.0f);
			color *= 255.99f;
			glm::ivec3 ic = glm::ivec3(int(color.x), int(color.y), int(color.z));
			outputFile << (unsigned char)ic.r << (unsigned char)ic.g << (unsigned char)ic.b;
		}
	}
	
	//close file
	outputFile.close();
}
