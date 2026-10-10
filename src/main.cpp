#include "wpicker.hpp"
#include <cstdlib>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

int main() {

  WPicker::WallpaperPicker wpicker = WPicker::WallpaperPicker();

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
      } else if (k == (int)'/') {
        wpicker.showFilterBox(); 
        cv::waitKey(0);
        break;
      }
      else if (k == (int)'q') {
        exit(0);
      }
      break;
    }
  }

  cv::destroyAllWindows();

  return 0;
}
