/*
 *  DashVideoSegmenter - Video DASH segmenter for H264 AVCC format
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
 *  Authors: Marc Palau <marc.palau@i2cat.net> 
 */

#ifndef _DASH_VIDEO_SEGMENTER_HH
#define _DASH_VIDEO_SEGMENTER_HH

#include "i2libdash.h"
#include "Frame.hh"
#include "DashSegment.hh"

class DashVideoSegmenter {
    
public:
    DashVideoSegmenter();
    ~DashVideoSegmenter();

    bool init(size_t segmentDuration, size_t timeBase, size_t sampleDuration, size_t width, size_t height, size_t framerate); 
    bool generateInit(unsigned char* metadata, size_t metadataSize, DashSegment* segment);
    bool addToSegment(AVCCFrame* frame, DashSegment* segment);
    bool finishSegment(DashSegment* segment);
    size_t getMaxSegmentLength(){return MAX_DAT;}; 

    
private:
    i2ctx* dashContext;
    size_t width;
    size_t height;
    size_t framerate;

};


#endif
