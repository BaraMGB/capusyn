/* Copyright 2013-2019 Capusyn Project
 *
 * capusyn is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * capusyn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with capusyn.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "JuceHeader.h"
#include <set>

namespace capusyn {
  class Processor;
} // namespace capusyn

class ProcessorTest : public UnitTest {
  public:
    ProcessorTest(String name) : UnitTest(name, "Processor") { }
    void runInputBoundsTest(capusyn::Processor* processor);
    void runInputBoundsTest(capusyn::Processor* processor, std::set<int> leave_inputs, std::set<int> ignore_outputs);
    void processAndCheckFinite(capusyn::Processor* processor, const std::set<int>& ignore_outputs);
};

