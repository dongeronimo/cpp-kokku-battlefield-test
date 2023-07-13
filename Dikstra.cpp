#include "Dikstra.h"

bool IsInsideMatrix(int line, int col, int lines, int cols)
{
	return (line >= 0 && col >= 0 && line < lines && col < cols);
}
