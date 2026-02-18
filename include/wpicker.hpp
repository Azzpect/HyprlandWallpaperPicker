#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#define CONFDIR "/.config/picker"
#define CONF CONFDIR + "/config.conf"

#define CANVAS_WIDTH 1100
#define CANVAS_HEIGHT 250
#define CANVAS_X_CENTER CANVAS_WIDTH / 2
#define CANVAS_Y_CENTER CANVAS_HEIGHT / 2


namespace WPicker {

  class WallpaperPicker {
    private:
    int active;
    cv::Mat canvas;
    cv::Scalar background = cv::Scalar(255, 255, 255);
    cv::Size ActiveImageSize = cv::Size(355, 200);
    cv::Size NotActiveImageSize = cv::Size(355 * 0.7, 200 * 0.7);
    std::vector<std::string> imgPaths;
    std::vector<cv::Mat> imgObjs;

    public:
    WallpaperPicker();
    ~WallpaperPicker() = default;

    void render();
    void preload();
    void leftShift();
    void rightShift();
    void setWallpaper();
  };

} // namespace WPicker
