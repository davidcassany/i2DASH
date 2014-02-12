#include "i2libisoff.h"

int main(){
	byte *source_data;
	byte *destination_data;

	uint32_t size_source_data;

	FILE *output_video_i, *output_audio_i, *output_segment_v, *output_segment_a;

	i2ctx *context = (i2ctx *) malloc(sizeof(i2ctx));
	context->ctxaudio = (i2ctx_audio *) malloc(sizeof(i2ctx_audio));
	context->ctxvideo = (i2ctx_video *) malloc(sizeof(i2ctx_video));

	i2ctx_audio *ctxAudio = context->ctxaudio; 
	i2ctx_video *ctxVideo = context->ctxvideo;
	//i2ctx_sample *ctxASample = ctxAudio->ctxsample;
	ctxVideo->width = 854;
	ctxVideo->height = 480;

	ctxAudio->channels = 2;
	ctxAudio->sample_size = 2; // write_mp4a --> sample_size * 8
	ctxAudio->sample_rate = 48000;

	//uint32_t initVideo, initAudio;

	/*// En este caso es el SPS/PPS, etc
	source_data = (byte *) calloc (100, sizeof(byte*));
	source_data[0] = 0x01;
	source_data[1] = 0x42;
	source_data[2] = 0xC0;
	source_data[3] = 0x1E;
	source_data[4] = 0xFF;
	source_data[5] = 0xE1;
	source_data[6] = 0x00;
	source_data[7] = 0x18;
	source_data[8] = 0x67;
	source_data[9] = 0x42;
	source_data[10] = 0xC0;
	source_data[11] = 0x1E;
	source_data[12] = 0xD9;
	source_data[13] = 0x00;
	source_data[14] = 0xD8;
	source_data[15] = 0x3D;
	source_data[16] = 0xE6;
	source_data[17] = 0xE1;
	source_data[18] = 0x00;
	source_data[19] = 0x00;
	source_data[20] = 0x03;
	source_data[21] = 0x00;
	source_data[22] = 0x01;
	source_data[23] = 0x00;
	source_data[24] = 0x00;
	source_data[25] = 0x03;
	source_data[26] = 0x00;
	source_data[27] = 0x30;
	source_data[28] = 0x0F;
	source_data[29] = 0x16;
	source_data[30] = 0x2E;
	source_data[31] = 0x48;
	source_data[32] = 0x01;
	source_data[33] = 0x00;
	source_data[34] = 0x05;
	source_data[35] = 0x68;
	source_data[36] = 0xCB;
	source_data[37] = 0x81;
	source_data[38] = 0x32;
	source_data[39] = 0xC8;

	size_source_data = 40;

	destination_data = (byte *) calloc (MAX_MDAT_SAMPLE, sizeof(byte*));

	initVideo = initVideoGenerator(source_data, size_source_data, destination_data, context);

	if(initVideo != I2ERROR) {
		printf("OK!\n");
		output_video_i = fopen("/home/dovahkiin/dash_rtmp_segments/output_i2.m4v", "w");
		int i = 0;
		// int fputc(int c, FILE *stream);
		for(i = 0; i < initVideo; i++) {
			fputc(destination_data[i], output_video_i);
		}
		fclose(output_video_i);
	}
	
	//free(source_data);
	//free(destination_data);

	source_data = (byte *) calloc (100, sizeof(byte*));
	source_data[0] = 0xaf;
	source_data[1] = 0x00;
	source_data[2] = 0x11;
	source_data[3] = 0x90;

	size_source_data = 4;

	destination_data = (byte *) calloc (MAX_MDAT_SAMPLE, sizeof(byte*));

	initAudio = initAudioGenerator(source_data, size_source_data, destination_data, context);

	if(initAudio != I2ERROR) {
		printf("OK!\n");
		output_audio_i = fopen("/home/dovahkiin/dash_rtmp_segments/output_i2.m4a", "w");
		int i = 0;
		// int fputc(int c, FILE *stream);
		for(i = 0; i < initAudio; i++) {
			fputc(destination_data[i], output_audio_i);
		}
		fclose(output_audio_i);
	}*/

	uint32_t seg_gen_video, seg_gen_audio;

	uint32_t media_type = VIDEO_TYPE;
	// Segments params 1st segment
	// sidx
	ctxVideo->earliest_presentation_time = 42; // 0x002a
	ctxVideo->latest_presentation_time = 8823; // 0x2257 + 0x002a
	context->reference_size = 705284; //0x000ac304

	// moof
	// mfhd
	ctxVideo->sequence_number = 0;
	//trun
	ctxVideo->ctxsample = (i2ctx_sample *) malloc(sizeof(i2ctx_sample));
	i2ctx_sample *ctxVSample = ctxVideo->ctxsample;

	ctxVSample->box_flags = 3841; // 0x0f01
	ctxVSample->mdat_sample_length = 2; //0x00d4
	int i = 0;
	// Los pongo todos igual menos el primero para probar el tema intra
	ctxVSample->mdat[0].duration_ms = 41; // 0x0029
	ctxVSample->mdat[0].size = 1868; // 0x074c
	ctxVSample->mdat[0].key = 1; // 1 si key
	ctxVSample->mdat[0].delay = 0;
	for (i = 1; i < ctxVSample->mdat_sample_length; ++i)
	{
		ctxVSample->mdat[i].duration_ms = 42; // 0x002a
		ctxVSample->mdat[i].size = 12; // 0x000c
		ctxVSample->mdat[i].key = 0; // 0x00010000 check
		ctxVSample->mdat[i].delay = 0;
	}
	// mdat
	source_data = (byte *) calloc (100, sizeof(byte*));
	source_data[0] = 0x0;
	source_data[1] = 0x0;
	source_data[2] = 0x02;
	source_data[3] = 0x6E;
	source_data[4] = 0x06;
	source_data[5] = 0x05;
	source_data[6] = 0xFF;
	source_data[7] = 0xFF;
	source_data[8] = 0x6A;
	source_data[9] = 0xDC;
	source_data[10] = 0x45;
	source_data[11] = 0xE9;
	source_data[12] = 0xBD;
	source_data[13] = 0xE6;
	source_data[14] = 0xD9;
	source_data[15] = 0x48;
	source_data[16] = 0xB7;
	source_data[17] = 0x96;
	source_data[18] = 0x2C;
	source_data[19] = 0xD8;
	source_data[20] = 0x20;
	source_data[21] = 0xD9;
	source_data[22] = 0x23;
	source_data[23] = 0xEE;
	source_data[24] = 0xEF;
	source_data[25] = 0x78;
	source_data[26] = 0x32;
	source_data[27] = 0x36;
	source_data[28] = 0x34;
	source_data[29] = 0x20;
	source_data[30] = 0x2D;
	source_data[31] = 0x20;
	source_data[32] = 0x43;
	source_data[33] = 0x6F;
	source_data[34] = 0x70;
	source_data[35] = 0x79;
	source_data[36] = 0x6C;
	source_data[37] = 0x65;
	source_data[38] = 0x66;
	source_data[39] = 0x75;

	size_source_data = 40;

	destination_data = (byte *) calloc (MAX_MDAT_SAMPLE, sizeof(byte*));

	seg_gen_video = segmentGenerator(source_data, size_source_data, destination_data, media_type, context);
	if(seg_gen_video != I2ERROR) {
		printf("OK!\n");
		output_segment_v = fopen("/home/dovahkiin/dash_rtmp_segments/video_segment.m4v", "w");
		int i = 0;
		// int fputc(int c, FILE *stream);
		for(i = 0; i < seg_gen_video; i++) {
			fputc(destination_data[i], output_segment_v);
		}
		fclose(output_segment_v);
	}

	media_type = AUDIO_TYPE;

	// sidx
	ctxAudio->earliest_presentation_time = 0; // 0x0
	ctxAudio->latest_presentation_time = 8853; // 0x2295 + 0x0
	context->reference_size = 145645; //0x000238ED
	// mfhd
	ctxAudio->sequence_number = 0;
	//trun
	ctxAudio->ctxsample = (i2ctx_sample *) malloc(sizeof(i2ctx_sample));
	i2ctx_sample *ctxASample = ctxAudio->ctxsample;

	ctxASample->box_flags = 769; // 0x0301
	ctxASample->mdat_sample_length = 2; //0x01a0
	i = 0;
	// Los pongo todos igual menos el primero para probar el tema intra
	ctxASample->mdat[0].duration_ms = 21; // 0x0015
	ctxASample->mdat[0].size = 341; // 0x0155
	for (i = 1; i < ctxASample->mdat_sample_length; ++i)
	{
		ctxASample->mdat[i].duration_ms = 21; // 0x002a
		ctxASample->mdat[i].size = 341; // 0x000c
	}
	// mdat
	source_data = (byte *) calloc (100, sizeof(byte*));
	source_data[0] = 0x21;
	source_data[1] = 011;
	source_data[2] = 0x45;
	source_data[3] = 0x00;
	source_data[4] = 0x14;
	source_data[5] = 0x50;
	source_data[6] = 0x01;
	source_data[7] = 0x46;
	source_data[8] = 0xFF;
	source_data[9] = 0xF1;
	source_data[10] = 0x0A;
	source_data[11] = 0x5A;
	source_data[12] = 0x5A;
	source_data[13] = 0x5A;
	source_data[14] = 0x5A;
	source_data[15] = 0x5A;
	source_data[16] = 0x5A;
	source_data[17] = 0x5A;
	source_data[18] = 0x5A;
	source_data[19] = 0x5A;
	source_data[20] = 0x5A;
	source_data[21] = 0x5D;
	source_data[22] = 0xE5;
	source_data[23] = 0xC2;
	source_data[24] = 0x14;
	source_data[25] = 0xB4;
	source_data[26] = 0xB4;
	source_data[27] = 0xB4;
	source_data[28] = 0xB4;
	source_data[29] = 0xB4;
	source_data[30] = 0xB4;
	source_data[31] = 0xBC;
	source_data[32] = 0x21;
	source_data[33] = 0x1A;
	source_data[34] = 0x13;
	source_data[35] = 0xA5;
	source_data[36] = 0x9C;
	source_data[37] = 0x86;
	source_data[38] = 0x04;
	source_data[39] = 0x20;

	size_source_data = 40;

	destination_data = (byte *) calloc (MAX_MDAT_SAMPLE, sizeof(byte*));

	seg_gen_audio = segmentGenerator(source_data, size_source_data, destination_data, media_type, context);
	if(seg_gen_audio != I2ERROR) {
		printf("OK!\n");
		output_segment_a = fopen("/home/dovahkiin/dash_rtmp_segments/video_segment.m4a", "w");
		int i = 0;
		// int fputc(int c, FILE *stream);
		for(i = 0; i < seg_gen_audio; i++) {
			fputc(destination_data[i], output_segment_a);
		}
		fclose(output_segment_a);
	}

	return 0;
}