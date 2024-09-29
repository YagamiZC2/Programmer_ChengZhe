
#include "main.h"




unsigned int LoadTexture(const char *FileName, GLint param)
{

	nn::Result result;
	nn::fs::FileHandle file;
	size_t readSize;

	result = nn::fs::OpenFile(&file, FileName, nn::fs::OpenMode_Read);
	if (nn::fs::ResultPathNotFound::Includes(result))
	{
		NN_ASSERT(false, "OpenFile:", FileName);
	}

	int64_t fileSize;
	result = nn::fs::GetFileSize(&fileSize, file);
	if (result.IsFailure())
	{
		NN_ASSERT(false, "GetFileSize:", FileName);
	}

	unsigned int	texture;
	unsigned char	header[18];
	unsigned char	*image;
	unsigned int	width, height;
	unsigned char	depth;
	unsigned int	bpp;
	unsigned int	format;


	// �w�b�_�ǂݍ���
	nn::fs::ReadFile(&readSize, file, 0, header, sizeof(header));

	// �摜�T�C�Y�擾
	width = header[13] * 256 + header[12];
	height = header[15] * 256 + header[14];
	depth = header[16];

	if (depth == 32)
	{
		bpp = 4;
		format = GL_RGBA;
	}
	else if (depth == 24)
	{
		bpp = 3;
		format = GL_RGB;
	}
	else
	{
		bpp = 0;
		NN_ASSERT( false, "LoadTexture:", FileName );
	}

	// �������m��
	image = (unsigned char*)new unsigned char[width * height * bpp];

	// RLE
	if (header[2] == 10)
	{
		unsigned char	buf[1000];				// �t�@�C���ǂݍ��݃o�b�t�@
		unsigned char	PacketHeader;			// Packet Type (1bit) & Pixel Count (7bits)
		unsigned char	PixelCount;				// �p�P�b�g���̃s�N�Z����
		unsigned		i, j;

		unsigned char* buffer = new unsigned char[fileSize - 18];
		nn::fs::ReadFile(&readSize, file, sizeof(header), buffer, fileSize - 18);
		unsigned char* read = buffer;

		unsigned CurrentPixel = 0;
		while (CurrentPixel < width * height - 1) {
			PacketHeader = *read++;
			PixelCount = (unsigned char)((PacketHeader & 127) + 1);
			if (PacketHeader & 128)
			{	// RLE
				for (i = 0; i < bpp; ++i)
					buf[i] = *read++;
				for (i = CurrentPixel; i < CurrentPixel + PixelCount; i++)
				{
					for (j = 0; j < bpp; j++)
					{
						image[i * bpp + j] = buf[j];
					}
				}
			}
			else
			{	// RAW
				for (i = 0; i < bpp * PixelCount; ++i)
					buf[i] = *read++;
				for (i = CurrentPixel; i < CurrentPixel + PixelCount; i++)
				{
					for (j = 0; j < bpp; j++)
					{
						image[i * bpp + j] = buf[(i - CurrentPixel) * bpp + j];
					}
				}
			}
			CurrentPixel += PixelCount;
		}
		delete[] buffer;
	}
	else
	{
		// �����k�摜�ǂݍ���
		nn::fs::ReadFile(&readSize, file, sizeof(header), image, width * height * bpp);
	}

	// R<->B
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			unsigned char c;
			c = image[(y * width + x) * bpp + 0];
			image[(y * width + x) * bpp + 0] = image[(y * width + x) * bpp + 2];
			image[(y * width + x) * bpp + 2] = c;
		}
	}

	nn::fs::CloseFile(file);


	// �e�N�X�`������
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);

	// �~�b�v�}�b�v
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, 0);

	delete image;

	return texture;
}



void UnloadTexture(unsigned int Texture)
{

	glDeleteTextures(1, &Texture);

}





void SetTexture(unsigned int Texture)
{
	if (Texture == 0)
	{
		glUniform1i(glGetUniformLocation(GetShaderProgramId(), "uTextureEnable"), 0);
	}
	else
	{
		glUniform1i(glGetUniformLocation(GetShaderProgramId(), "uTextureEnable"), 1);
		glBindTexture(GL_TEXTURE_2D, Texture);
	}
}


