/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *  Copyright (C) 2013 Chuan Ji <jichuan89@gmail.com>                        *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *   http://www.apache.org/licenses/LICENSE-2.0                              *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "multithreading.hpp"
#include <cassert>
#include <unistd.h>
#include <thread>
#include <vector>

void ExecuteInParallel(const std::function<void (int, int)> &f,
                       int num_threads) {
  // 1. Set default value for num_threads if needed.
  assert(num_threads >= 0);
  if (num_threads <= 0) {
    num_threads = sysconf(_SC_NPROCESSORS_ONLN);
  }

  // 2. Spawn threads.
  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; ++i) {
    threads.push_back(std::thread(f, num_threads, i));
  }

  // 3. Wait for threads to exit.
  for (std::thread &thread : threads) {
    thread.join();
  }
}


