/*
 * Copyright (c) 2017, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <gtest/gtest.h>
#include "utility/oskar_get_num_procs.h"
#include "utility/oskar_thread.h"
#include "utility/oskar_timer.h"
#include <cstdlib>

#define ENABLE_PRINT 1

void print_from_thread(int loop, int id, const char* message)
{
    if (ENABLE_PRINT)
        printf("(Loop %d, Thread %2d): %s\n", loop, id, message);
}

void* thread_simple(void* arg)
{
    size_t thread_id = (size_t)arg;
    print_from_thread(0, (int)thread_id, "Hello");
    return 0;
}

struct ThreadArgs
{
    int thread_id;
    oskar_Barrier* barrier;
};
typedef struct ThreadArgs ThreadArgs;

void* thread_barriers(void* arg)
{
    ThreadArgs* args = (ThreadArgs*) arg;
    int thread_id = args->thread_id;
    for (int i = 0; i < 4; ++i)
    {
        print_from_thread(i, thread_id, "Hello");
        oskar_barrier_wait(args->barrier);
        print_from_thread(i, thread_id, "Goodbye");
        oskar_barrier_wait(args->barrier);
    }
    return 0;
}

TEST(thread, create_and_join)
{
    // Get the number of CPU cores.
    size_t num_threads = (size_t) oskar_get_num_procs();

    // Allocate thread array.
    oskar_Thread** threads = (oskar_Thread**)
            calloc(num_threads, sizeof(oskar_Thread*));

    // Start all the threads.
    for (size_t i = 0; i < num_threads; ++i)
        threads[i] = oskar_thread_create(thread_simple, (void*)i, 0);

    // Wait for all threads to finish.
    for (size_t i = 0; i < num_threads; ++i)
        oskar_thread_join(threads[i]);

    // Clean up.
    for (size_t i = 0; i < num_threads; ++i)
        oskar_thread_free(threads[i]);
    free(threads);
}

TEST(thread, barriers)
{
    // Set the number of threads.
    int num_threads = 8;

    // Create the shared barrier.
    oskar_Barrier* barrier = oskar_barrier_create(num_threads);

    // Allocate thread array and thread arguments for each thread.
    oskar_Thread** threads = (oskar_Thread**)
            calloc((size_t) num_threads, sizeof(oskar_Thread*));
    ThreadArgs* args = (ThreadArgs*)
            calloc((size_t) num_threads, sizeof(ThreadArgs));

    // Start all the threads.
    for (int i = 0; i < num_threads; ++i)
    {
        args[i].barrier = barrier;
        args[i].thread_id = (int) i;
        threads[i] = oskar_thread_create(thread_barriers, (void*)(&args[i]), 0);
    }

    // Wait for all threads to finish.
    for (int i = 0; i < num_threads; ++i)
        oskar_thread_join(threads[i]);

    // Clean up.
    for (int i = 0; i < num_threads; ++i)
        oskar_thread_free(threads[i]);
    oskar_barrier_free(barrier);
    free(args);
    free(threads);
}
