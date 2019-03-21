#include <output_file.h>

#include <assert.h>
#include <fstream>
#include <algorithm>

void write_ppm(char const* path, std::vector<std::vector<glm::vec3>> const& data, int width, int height)
{
	std::ofstream outputFile(path);
	assert("Could not open output file" && outputFile.is_open());
	outputFile << "P3\n" << width << " " << height << "\n" << "255\n";
	for (int py = height - 1; py >= 0; py--)
	{
		for (int px = 0; px < width; px++)
		{
			glm::vec3 color = data[px][py];
			color *= 255.99f;
			glm::ivec3 ic = glm::ivec3(std::max(0, int(color.x)), std::max(0, int(color.y)), std::max(0, int(color.z)));
			outputFile << ic.r << " ";
			outputFile << ic.g << " ";
			outputFile << ic.b << " \n";
		}
	}

	outputFile << std::endl;

	//close file
	outputFile.close();
}