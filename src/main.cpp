#include "wpicker.hpp"
#include <cstdlib>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

int main() {

  WPicker::WallpaperPicker wpicker = WPicker::WallpaperPicker();


  std::thread t(&WPicker::WallpaperPicker::preload, &wpicker);
  t.detach();

  while (1) {

    wpicker.render();

    while (1) {
      int k = cv::waitKey(0);
      if (k == 13) {
        wpicker.setWallpaper();
        break;
      } else if (k == (int)'l') {
        wpicker.leftShift();
        break;
      } else if (k == (int)'h') {
        wpicker.rightShift();
        break;
      } else if (k == (int)'q') {
        exit(0);
      }
      break;
    }
  }

  cv::destroyAllWindows();

  return 0;
}
