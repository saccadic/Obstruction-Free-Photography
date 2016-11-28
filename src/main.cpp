#include <bits/stdc++.h>

extern "C" {
#include <libavutil/imgutils.h>
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libswscale/swscale.h>
}

#include "pipeline.h"
#include "diff_blur.h"
#include "cuda.h"
using namespace std;


int main(int argc, char * argv[]) {
  if (argc != 3) {
    printf("Usage: %s [input file] [output file]\n", argv[0]);
    return 1;
  }
  Pipeline * pipeline = new DiffBlur(640, 480);
  VideoProcessor * processor = new VideoProcessor(pipeline, argv[1], argv[2]);
	auto startTime = chrono::high_resolution_clock::now();
  while (processor->processFrame() >= 0) {
		if (processor->getFrameCounter() % 100 == 0) {
			auto curTime = chrono::high_resolution_clock::now();
			chrono::duration<float> diff = curTime - startTime;
			float secs = diff.count();
			printf("FPS: %f\n", (float) processor->getFrameCounter() / secs);
		}
		if (processor->getFrameCounter() == 300) {
			break;
		}
	}
  return 0;
}
