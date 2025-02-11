#include <iostream>
#include <fstream>
#include "vec3.h"


int main()
{
	int nx = 200;
	int ny = 100;

	// outputfile
	std::ofstream outputfile("image.ppm");

	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	outputfile << "P3\n" << nx << " " << ny << "\n255\n";
	
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;
			vec3 color(r, g, b);

			int ir = int(255.99 * color[0]);
			int ig = int(255.99 * color[1]);
			int ib = int(255.99 * color[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			outputfile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputfile.close();
}
