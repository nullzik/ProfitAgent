#pragma once

#include "domain/warehouse/Product.h"

namespace application {

// Конвертирует quantity из unitFrom в unitTo (кг↔г для массы).
inline double convertToProductUnit(double quantity, domain::Unit unitFrom, domain::Unit unitTo) {
    if (unitFrom == unitTo) return quantity;
    if (unitFrom == domain::Unit::Kilogram && unitTo == domain::Unit::Gram) return quantity * 1000.0;
    if (unitFrom == domain::Unit::Gram && unitTo == domain::Unit::Kilogram) return quantity / 1000.0;
    return quantity;  // Liter или несовместимые — без конвертации
}

} // namespace application
