#pragma once

#include <iostream>
#include <glad/glad.h>
#include <string>

#include "stb_image.h"

class Texture {
	private:
		int mWidth;
		int mHeight;
		int mNrChannels;

		unsigned int mID;
		
		static bool mIsSetTextureAttribute;

	public:
		Texture(const std::string& image, const unsigned int type);
		~Texture();

		void Bind() const;
		void Unbind() const;
		unsigned int ID() const;
};
