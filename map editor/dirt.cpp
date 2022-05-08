#include "dirt.h"

dirt::dirt() :texdirt(TextureHolder::GetTexture("graphics/dirt.png"))
{
}

void dirt::SetVertexdirts()
{
    const int DIRT_SIZE = 8;
    const int DIRT_TYPES = 90;

    dirts.setPrimitiveType(Quads);
    dirts.resize(15 * 6 * 4);

    for (int r = 0; r < 15; ++r)
    {
        for (int c = 0; c < 6; ++c)
        {
            int index = r * 6 + c;

            int vertexIndex = index * 4;

            int texIndex = 0;
            int offset = texIndex * DIRT_SIZE;

            dirts[vertexIndex + 0].texCoords = Vector2f(offset , offset);
            dirts[vertexIndex + 1].texCoords = Vector2f(offset , offset);
            dirts[vertexIndex + 2].texCoords = Vector2f(offset , offset);
            dirts[vertexIndex + 3].texCoords = Vector2f(offset , offset);
        }
    }
}
