#ifndef _UTILS_H_
#define _UTILS_H_
#pragma once
#include <stdio.h>
#include <random>
#include <glm.hpp>

//Helper function to print progress bar in terminal/console
//src: https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf/36315819#36315819
#define PBSTR "############################################################"
#define PBWIDTH 32
inline void printProgressBar(double percentage)
{
	int val = (int)(percentage * 100);
	int lpad = (int)(percentage * PBWIDTH);
	int rpad = PBWIDTH - lpad;
	printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
	fflush(stdout);
}

//Generates floats in the [-1, 1] range
inline float randomNumberGen()
{
	return ((rand() / (RAND_MAX + 1.0f)) * 2.0f - 1.0f);
}

//Schlick's fresnel effect approximation
inline glm::vec3 fresnel_schlick(float theta, glm::vec3 const& R0)
{
	return (R0 + (1.0f - R0) * powf(1.0f - cosf(theta), 5.0f));
}
#endif //_UTILS_H_