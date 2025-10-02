# 42 Norm Violations Analysis

## Current Violations Found:

### 1. **sprite_loader.c** (424 lines)
- ❌ Functions exceed 25 lines significantly
- ❌ Functions have more than 5 variables (9-13 variables)
- ❌ Complex sprite generation code
- **Solution**: Simplify or use simple colored rectangles

### 2. **map_parser.c**
- ❌ `parse_map()` - too complex, needs splitting
- ❌ `get_next_line()` - may need verification

### 3. **game_render.c**
- ❌ `render_game()` - 10+ variables, 40+ lines
- ❌ Needs refactoring

### 4. **map_validator.c**
- ⚠️  `is_valid_path()` - borderline, needs checking

### 5. **game_init.c**
- ⚠️  Multiple functions need verification

## 42 Norm Rules:

1. **Maximum 25 lines per function** (excluding braces)
2. **Maximum 5 variables per function**
3. **Maximum 4 parameters per function**
4. **Maximum 80 characters per line**
5. **No forbidden functions** (sprintf, etc.)

## Forbidden Functions Used:

- ❌ `sprintf()` in game_render.c (line 37-38)
- ❌ `printf()` used extensively (allowed but ft_printf preferred)
- ✅ Standard functions (malloc, free, open, close, read, write) - OK
- ✅ Math library functions - OK
- ✅ MiniLibX functions - OK

## Action Plan:

1. Replace complex sprite generation with simple colored squares
2. Refactor long functions into smaller helper functions
3. Replace sprintf with ft_printf or manual string building
4. Split map_parser into smaller functions
5. Simplify render_game logic
6. Verify all functions comply with norm
