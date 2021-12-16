#pragma once

class Texture
{
	friend class FBO;
public:
	enum class Type
	{
		BMP = 0,
		PNG = 1,
		NORMAL_MAP = 2,
		SPECULAR,

		DEPTH,

		G_BUFFER_POSITION,
		G_BUFFER_NORMAL,
		G_BUFFER_ALBEDO
	};

	struct BitMapFile
	{
		BitMapFile();
		BitMapFile(const std::string& filePath);
		BitMapFile(const BitMapFile&) = delete;
		BitMapFile(BitMapFile&&) noexcept;
		~BitMapFile();

		BitMapFile& operator=(const BitMapFile&) = delete;
		BitMapFile& operator=(BitMapFile&&) noexcept;

		void loadFromFile(const std::string& filePath);

		int sizeX {};
		int sizeY {};
		int nrChannels {};
		unsigned char* data {};
	};

	static Texture createTextureFromFile(const std::string& textureFilePath, Texture::Type textureType);
	static Texture createDepthTexture();
#pragma region Textures for G-buffer
	static Texture createTextureForPositionBuffer();
	static Texture createTextureForNormalBuffer();
	static Texture createTextureForAlbedoBuffer();
#pragma endregion
	Texture(const Texture&) = delete;
	Texture(Texture&&) noexcept;
	~Texture();

	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) noexcept;

	void bindTexture(unsigned int unit) const;
	void unbindTexture() const;

	int getTextureWidth() const;
	int getTextureHeight() const;


private:
	GLuint texture {};
	BitMapFile bmp;

	Texture::Type textureType;

	Texture(Texture::Type type);
	Texture::BitMapFile* readBmpImage(const std::string& filePath);

	void initializeTexture();
};

