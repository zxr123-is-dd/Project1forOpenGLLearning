#include "Texture.h"

bool Texture::mIsSetTextureAttribute = false;

Texture::Texture(const std::string& image, const unsigned int type)
	: mID(0) {
	int channel;
	if (type == 3) {
		channel = GL_RGB;
	} else if (type == 4) {
		channel = GL_RGBA;
	} else {
		std::cout << "Can's handle this texture!" << std::endl;
		exit(0);
	}
	if (!mIsSetTextureAttribute) {
		stbi_set_flip_vertically_on_load(true);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		mIsSetTextureAttribute = true;
		std::cout << "Set texture attribute successfully" << std::endl;
	}

	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID); // The texture has already bind to the state machine

	unsigned char* data = stbi_load(image.c_str(), &mWidth, &mHeight, &mNrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, channel, mWidth, mHeight, 0, channel, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Load texture " << image << " successfully" << std::endl;
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Texture::~Texture() {
}

void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, mID);
}

void Texture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::ID() const {
	return mID;
}
