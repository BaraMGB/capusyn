/* SPDX-License-Identifier: GPL-3.0-or-later */

#include "JuceHeader.h"
#include "paths.h"

namespace {
  class JuceCompatibilityTest : public UnitTest {
    public:
      JuceCompatibilityTest() : UnitTest("JUCE compatibility", "Compatibility") { }

      void runTest() override {
        int svg_count = 0;
        for (int i = 0; i < BinaryData::namedResourceListSize; ++i) {
          if (!String(BinaryData::originalFilenames[i]).endsWithIgnoreCase(".svg"))
            continue;

          ++svg_count;
          beginTest(String("SVG outline: ") + BinaryData::originalFilenames[i]);
          int data_size = 0;
          const char* data = BinaryData::getNamedResource(BinaryData::namedResourceList[i], data_size);
          expect(data != nullptr && data_size > 0);
          if (data == nullptr || data_size <= 0)
            continue;

          auto drawable = Drawable::createFromImageData(data, static_cast<size_t>(data_size));
          expect(drawable != nullptr);
          if (drawable != nullptr)
            expect(!drawable->getOutlineAsPath().isEmpty());
        }

        beginTest("Embedded SVG coverage");
        expect(svg_count > 0);

        beginTest("Branding paths");
        expect(!Paths::capusynRing().isEmpty());
        expect(!Paths::capusynV().isEmpty());
        expect(!Paths::capusynWord().isEmpty());
        expect(!Paths::capusynWordRing().isEmpty());
      }
  };

  JuceCompatibilityTest juce_compatibility_test;
}
