#include "Grid.h"

Grid::Grid()
    :texgrid(TextureHolder::GetTexture("graphics/Grid.png"))
{

}

void Grid::CreateGrid(IntRect area)
{
	const int GRID_SIZE = 32;
	const int GRID_TYPES = 2;

    int texIndex = 0;
    
	int cols = area.width / GRID_SIZE;
	int rows = area.height / GRID_SIZE;

	grid.setPrimitiveType(Quads);
	grid.resize(cols * rows *4.f);

    for (int r = 0; r < rows; ++r)
    {

        for (int c = 0; c < cols; ++c)
        {
            int index = r * cols + c;

            float x = c * GRID_SIZE;
            float y = r * GRID_SIZE;

            int vertexIndex = index * 4;

            grid[vertexIndex + 0].position = Vector2f(x, y);
            grid[vertexIndex + 1].position = Vector2f(x + GRID_SIZE, y);
            grid[vertexIndex + 2].position = Vector2f(x + GRID_SIZE, y + GRID_SIZE);
            grid[vertexIndex + 3].position = Vector2f(x, y + GRID_SIZE);

            if ((c + r) % 2 == 1)
            {
                texIndex = 1;
            }
            else
            {
                texIndex = 0;
            }

            float offset = texIndex * GRID_SIZE;
            grid[vertexIndex + 0].texCoords = Vector2f(offset, 0.f);
            grid[vertexIndex + 1].texCoords = Vector2f(offset, GRID_SIZE);
            grid[vertexIndex + 2].texCoords = Vector2f(offset + GRID_SIZE, GRID_SIZE);
            grid[vertexIndex + 3].texCoords = Vector2f(offset + GRID_SIZE, 0.f);
        }
    }
}

Texture& Grid::Gettexgrid()
{
    return texgrid;
}

VertexArray& Grid::Getgrid()
{
    return grid;
}


