// COMP710 GP Framework 2022 
#ifndef __TEXTURE_H  
#define __TEXTURE_H 

struct SDL_Surface;
class Texture
{
	// Member methods: 
public:
	Texture();
	~Texture();
	bool Initialise(const char* pcFilename);
	void SetActive();
	int GetWidth() const; 
	int GetHeight() const;
	void LoadTextTexture(const char* text, const char* fontname, int pointsize);
	void DebugDraw();
protected:
	void LoadSurfaceIntoTexture(SDL_Surface* pSurface);
private:
	Texture(const Texture& texture);
	Texture& operator=(const Texture& texture);
	// Member data: 
public:

protected:
	unsigned int m_uiTextureId; 
	int m_iWidth;
	int m_iHeight;

private:

};

#endif //   TEXTURE_H 
