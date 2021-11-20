// =================================================================
//
// File: utils.h
// Author: Pedro Perez
// Description: This file contains the implementation of the
//				functions used to take the time and perform the
//				speed up calculation; as well as functions for
//				initializing integer arrays.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

#define N 10

struct timeval startTime, stopTime;
int started = 0;

// =================================================================
// Records the initial execution time.
// =================================================================
void start_timer() {
	started = 1;
	gettimeofday(&startTime, NULL);
}

// =================================================================
// Calculates the number of microseconds that have elapsed since
// the initial time.
//
// @returns the time passed
// =================================================================
double stop_timer() {
	long seconds, useconds;
	double duration = -1;

	if (started) {
		gettimeofday(&stopTime, NULL);
		seconds  = stopTime.tv_sec  - startTime.tv_sec;
		useconds = stopTime.tv_usec - startTime.tv_usec;
		duration = (seconds * 1000.0) + (useconds / 1000.0);
		started = 0;
	}
	return duration;
}

#endif