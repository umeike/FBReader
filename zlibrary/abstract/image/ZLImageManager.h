/*
 * Copyright (C) 2005 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __ZLIMAGEMANAGER_H__
#define __ZLIMAGEMANAGER_H__

#include <abstract/shared_ptr.h>

class ZLString;
class ZLImage;
class ZLMultiImage;

class ZLImageData {

protected:
	ZLImageData() {}
	
public:
	virtual ~ZLImageData() {}

	virtual unsigned int width() const = 0;
	virtual unsigned int height() const = 0;

	virtual void init(unsigned int width, unsigned int height) = 0;
	virtual void setPosition(unsigned int x, unsigned int y) = 0;
	virtual void moveX(int delta) = 0;
	virtual void moveY(int delta) = 0;
	virtual void setPixel(unsigned char r, unsigned char g, unsigned char b) = 0;
	void setGrayPixel(unsigned char c);

	virtual void copyFrom(const ZLImageData &source, unsigned int sourceX, unsigned int sourceY, unsigned int targetX, unsigned int targetY) = 0;
};

class ZLImageManager {

public:
	static const ZLImageManager &instance();
	static void deleteInstance();

protected:
	static ZLImageManager *ourInstance;
	
public:
	shared_ptr<ZLImageData> imageData(const ZLImage &image) const;

protected:
	ZLImageManager() {}
	virtual ~ZLImageManager() {}

	virtual shared_ptr<ZLImageData> createData() const = 0;
	virtual void convertImageDirect(const ZLString &stringData, ZLImageData &imageData) const = 0;

private:
	void convertMultiImage(const ZLMultiImage &multiImage, ZLImageData &imageData) const;
	void convertFromPalmImageFormat(const ZLString &imageString, ZLImageData &imageData) const;
};

inline void ZLImageData::setGrayPixel(unsigned char c) { setPixel(c, c, c); }

inline const ZLImageManager &ZLImageManager::instance() { return *ourInstance; }
inline void ZLImageManager::deleteInstance() { delete ourInstance; }

#endif /* __IMAGEMANAGER_H__ */
