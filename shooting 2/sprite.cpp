#include "main.h"
#include "texture.h"
#include "sprite.h"

//aÅ@ìßñæìx
void DrawSpriteQuad(
	float x, float y, float w, float h,
	float r, float g, float b, float a,
	unsigned int texNo, float u, float v, float tw, float th)
{
	VERTEX_3D vertexQuad[4];

	vertexQuad[0].Position = MakeFloat3(x - w * 0.5f, y - h * 0.5f, 0.0f);
	vertexQuad[1].Position = MakeFloat3(x + w * 0.5f, y - h * 0.5f, 0.0f);
	vertexQuad[2].Position = MakeFloat3(x - w * 0.5f, y + h * 0.5f, 0.0f);
	vertexQuad[3].Position = MakeFloat3(x + w * 0.5f, y + h * 0.5f, 0.0f);

	vertexQuad[0].Color = MakeFloat4(r, g, b, a);
	vertexQuad[1].Color = MakeFloat4(r, g, b, a);
	vertexQuad[2].Color = MakeFloat4(r, g, b, a);
	vertexQuad[3].Color = MakeFloat4(r, g, b, a);

	vertexQuad[0].TexCoord = MakeFloat2(u, v);
	vertexQuad[1].TexCoord = MakeFloat2(u + tw, v);
	vertexQuad[2].TexCoord = MakeFloat2(u, v + th);
	vertexQuad[3].TexCoord = MakeFloat2(u + tw, v + th);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertexQuad[0].Position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertexQuad[0].Color);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertexQuad[0].TexCoord);

	SetTexture(texNo);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
