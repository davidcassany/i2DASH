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

#include "DashVideoSegmenter.hh"
#include <iostream>

DashVideoSegmenter::DashVideoSegmenter() 
: dashContext(NULL), width(0), height(0), framerate(0)
{
}

bool DashVideoSegmenter::init(size_t segmentDuration, size_t timeBase, size_t sampleDuration, size_t width, size_t height, size_t framerate) 
{
    uint8_t i2error;

    this->width = width;
    this->height = height;
    this->framerate = framerate;

    i2error = generate_context(&dashContext, VIDEO_TYPE);

    if (i2error != I2OK) {
        return false;
    }

    i2error = fill_video_context(&dashContext, width, height, framerate, timeBase, sampleDuration);

    if (i2error != I2OK) {
        return false;
    }

    set_segment_duration(segmentDuration, &dashContext);
    return true;
}

DashVideoSegmenter::~DashVideoSegmenter()
{
}

bool DashVideoSegmenter::generateInit(unsigned char *metadata, size_t metadataSize, DashSegment* segment) 
{
    size_t initSize = 0;

    if (!dashContext) {
        return false;
    }

    initSize = new_init_video_handler(metadata, metadataSize, segment->getDataBuffer(), &dashContext);

    if (initSize == 0) {
        return false;
    }

    segment->setDataLength(initSize);

    return true;
}

bool DashVideoSegmenter::addToSegment(AVCCFrame* frame, DashSegment* segment) 
{
    size_t segmentSize = 0;

    if (!frame || !segment || !dashContext || frame->getDataLength() <= 0 || frame->getDuration() <= 0) {
        return false;
    }

    segmentSize = add_sample(frame->getDataBuffer(), frame->getDataLength(), frame->getDuration(), frame->getPresentationTime(), 
                             frame->getDecodeTime(), segment->getSeqNumber(), VIDEO_TYPE, segment->getDataBuffer(), frame->isIntra(), &dashContext);

    if (segmentSize <= I2ERROR_MAX) {
        return false;
    }

    segment->setTimestamp(dashContext->ctxvideo->earliest_presentation_time);
    segment->setDataLength(segmentSize);
    return true;
}

bool DashVideoSegmenter::finishSegment(DashSegment* segment) 
{
    size_t segmentSize = 0;

    if (!dashContext || !dashContext->ctxvideo || dashContext->ctxvideo->segment_data_size <= 0) {
        return false;
    }

    segment->setTimestamp(dashContext->ctxvideo->earliest_presentation_time);
    segmentSize = finish_segment(VIDEO_TYPE, segment->getDataBuffer(), &dashContext);

    if (segmentSize <= I2ERROR_MAX) {
        return false;
    }

    segment->setDataLength(segmentSize);
    return true;
}

