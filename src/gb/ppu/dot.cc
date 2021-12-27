#include "dot.h"

namespace gb {

Dot::Dot() : Index{ColorIndex::None}, Tone{Shade::Screen} {}

Dot::Dot(const ColorIndex index, const Shade tone) : Index{index}, Tone{tone} {}

}
