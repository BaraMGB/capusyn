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

#include "fonts.h"

namespace {
Font createLegacyEmbeddedFont(const void* data, int size) {
  auto typeface = Typeface::createSystemTypefaceFor(data, static_cast<size_t>(size));
  return Font(FontOptions(typeface).withMetricsKind(TypefaceMetricsKind::legacy));
}
}

Fonts::Fonts() :
    proportional_regular_(createLegacyEmbeddedFont(BinaryData::LatoRegular_ttf,
                                                   BinaryData::LatoRegular_ttfSize)),
    proportional_light_(createLegacyEmbeddedFont(BinaryData::LatoLight_ttf,
                                                 BinaryData::LatoLight_ttfSize)),
    proportional_title_(createLegacyEmbeddedFont(BinaryData::MontserratLight_otf,
                                                 BinaryData::MontserratLight_otfSize)),
    proportional_title_regular_(createLegacyEmbeddedFont(BinaryData::MontserratRegular_ttf,
                                                         BinaryData::MontserratRegular_ttfSize)),
    monospace_(createLegacyEmbeddedFont(BinaryData::DroidSansMono_ttf,
                                        BinaryData::DroidSansMono_ttfSize)) {

}
