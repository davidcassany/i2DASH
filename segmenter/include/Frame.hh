/*
 *  AVCCFrame - Video frame for H264 AVCC format
 *  Copyright (C) 2013  Fundació i2CAT, Internet i Innovació digital a Catalunya
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Authors: David Cassany <david.cassany@i2cat.net> 
 *          
 */

#ifndef _FRAME_HH
#define _FRAME_HH

#include <cstddef>
#include <chrono>

class Frame {
    
public:
    Frame();
    
    virtual ~Frame();
    
    unsigned char* getDataBuffer() {return frameBuff;};
    size_t getDataLength() {return frameLen;};

    void setDataBuffer(unsigned char *buff, size_t length);
    
    void setPresentationTime(std::chrono::milliseconds pTime);
    std::chrono::milliseconds getPresentationTime() {return presentationTime;};
    
    virtual void clearFrame() = 0;
    
protected:
    std::chrono::milliseconds presentationTime; 
    unsigned char *frameBuff;
    size_t frameLen;
};

class AVCCFrame : public Frame {
    
public:
    AVCCFrame();
    
    ~AVCCFrame();
    
    void setVideoSize(int width, int height);
    
    unsigned char* getHdrBuffer() {return frameHBuff;};
    size_t getHdrLength() {return frameHLen;};
    
    void setHdrBuffer(unsigned char *buff, size_t length);
    
    int getWidth() {return width;};
    int getHeight() {return height;};
    
    void clearFrame();
    
private:
    int width, height;
    
    unsigned char *frameHBuff;
    size_t frameHLen;
};

class AACFrame : public Frame {
    
public:
    AACFrame();
    
    ~AACFrame();
    
    unsigned char* getHdrBuffer() {return frameHBuff;};
    size_t getHdrLength() {return frameHLen;};
    
    void setHdrBuffer(unsigned char *buff, size_t length);
    
    void clearFrame();
    
private:
    unsigned char *frameHBuff;
    size_t frameHLen;
};

#endif