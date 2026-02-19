#include "wpicker.hpp"
#include <filesystem>
#include <fstream>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>

WPicker::WallpaperPicker::WallpaperPicker() {

  std::string home = std::getenv("HOME");
  std::string dir;
  std::ifstream file(home + CONF);

  std::string line;
  for (int i = 0; i < 2; i++) {
    std::getline(file, line);
    if (i == 0) {
      dir = line;
    } else {
      std::string hex = line;

      int r = std::stoi(hex.substr(1, 2), nullptr, 16);
      int g = std::stoi(hex.substr(3, 2), nullptr, 16);
      int b = std::stoi(hex.substr(5, 2), nullptr, 16);

      background = cv::Scalar(b, g, r);
    }
  }

  file.close();

  for (const auto &entry : std::filesystem::directory_iterator(dir)) {
    if (entry.is_regular_file()) {
      auto ext = entry.path().extension().string();
      if (ext == ".jpg" || ext == ".png" || ext == ".jpeg") {
        this->imgPaths.push_back(entry.path());
        cv::Mat obj;
        this->imgObjs.push_back(obj);
      }
    }
  }

  for (int i = 0; i < std::min(3, (int)imgPaths.size()); i++) {
    imgObjs[i] = cv::imread(imgPaths[i]);
  }

  this->active = 1;
  this->canvas = cv::Mat(CANVAS_HEIGHT, CANVAS_WIDTH, CV_8UC3, background);
}

void WPicker::WallpaperPicker::render() {

  canvas.setTo(background);

  cv::Mat img;
  cv::resize(imgObjs[active], img, ActiveImageSize);
  cv::Rect roi1(CANVAS_X_CENTER - ActiveImageSize.width / 2,
                CANVAS_Y_CENTER - ActiveImageSize.height / 2, img.cols,
                img.rows);

  img.copyTo(canvas(roi1));

  if (active - 1 >= 0) {
    imgObjs[active - 1] = imgObjs[active - 1].empty()
                              ? cv::imread(imgPaths[active - 1])
                              : imgObjs[active - 1];
    cv::Mat img;
    cv::resize(imgObjs[active - 1], img, NotActiveImageSize);
    cv::Rect roi2(CANVAS_X_CENTER - ActiveImageSize.width / 2 -
                      NotActiveImageSize.width - 30,
                  CANVAS_HEIGHT / 2 - NotActiveImageSize.height / 2, img.cols,
                  img.rows);
    img.copyTo(canvas(roi2));
  }

  if (active + 1 < (int)imgObjs.size()) {
    imgObjs[active + 1] = imgObjs[active + 1].empty()
                              ? cv::imread(imgPaths[active + 1])
                              : imgObjs[active + 1];
    cv::Mat img;
    cv::resize(imgObjs[active + 1], img, NotActiveImageSize);
    cv::Rect roi3(CANVAS_X_CENTER + ActiveImageSize.width / 2 + 30,
                  CANVAS_HEIGHT / 2 - NotActiveImageSize.height / 2, img.cols,
                  img.rows);
    img.copyTo(canvas(roi3));
  }

  cv::imshow("WallpaperPicker", canvas);
}

void WPicker::WallpaperPicker::preload() {
  for (int i = active + 2; i < (int)imgPaths.size(); i++) {
    if (imgObjs[i].empty()) {
      imgObjs[i] = cv::imread(imgPaths[i]);
    }
  }
}

void WPicker::WallpaperPicker::setWallpaper() {
  pid_t pid = fork();

  std::string script =
      (std::string)std::getenv("HOME") + CONFDIR + "/setWal.sh";

  if (pid == 0) {
    execl("/bin/bash", "bash", script.c_str(), imgPaths[active].c_str(),
          nullptr);
  } else {
    std::cout << "failed to create fork process" << std::endl;
  }
}

void WPicker::WallpaperPicker::leftShift() {
  active = std::min((int)imgObjs.size() - 1, active + 1);
}

void WPicker::WallpaperPicker::rightShift() {
  active = std::max(0, active - 1);
}
