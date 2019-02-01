# 零、 流程图
```flow
st=>start: 开始
e=>end: 结束
op1=>operation: 收集多帧激光
st->op1
cond=>condition: 完成?
op1->cond
cond(no)->op1
op2=>operation: 多帧激光叠加成图像，该点有激光值加1， 没有则不加
cond(yes)->op2
op3=>operation: 图像二值化
op2->op3
op4=>operation: 二值化图像膨胀
op3->op4
op5=>operation: 高斯模糊
op4->op5
op6=>operation: 生成高斯金字塔
op5->op6
op7=>operation: 粗匹配
op6->op7
op8=>operation: 精匹配
op7->op8
cond1=>condition: 是否大于阈值?
op8->cond1
op9=>operation: 匹配成功
op10=>operation: 匹配失败
cond1(yes)->op9
cond1(no)->op10
op9->e
op10->e
```

# 一、 关键步骤
## 1. 图像分辨率
```
#define TEMPLATE_RESOLUTION 0.002
```
该值的选择对精度会有影响

```
resolution_ratio_ = TEMPLATE_RESOLUTION / resolution_;
```
该值可以将模板生成与模板匹配分开来，即也许模板是用TEMPLATE_RESOLUTION生成的，但是在模板匹配时，会改动resolution_，为了不重新生成模板，会对使用TEMPLATE_RESOLUTION的模板进行resolution_ratio_倍缩放操作。
## 2. 形态学处理
```
 element_ = getStructuringElement(
        MORPH_ELLIPSE, Size(2 * dilate_size + 1, 2 * dilate_size + 1),
        Point(dilate_size, dilate_size));
```
选择圆形形态学核

## 3. 多帧激光叠加减少激光跳动对精度的影响
```
 for (int cnt = 0; cnt < laserScans_.size(); cnt++)
  {
    sensor_msgs::LaserScan scan = laserScans_[cnt];
    int rangesSize = scan.ranges.size();
    float angleIncrement = scan.angle_increment;
    float angleMin = scan.angle_min;

    for (int i = 0; i < rangesSize; i++)
    {
      float range = scan.ranges[i];
      float angle = i * angleIncrement + angleMin;

      float x = range * cos(angle) - x_offset_;
      float y = range * sin(angle) - y_offset_;

      int xd = x * resolution_inv_ + 0.5;
      int yd = y * resolution_inv_ + 0.5;

      // Add results of 20 frames to one picture
      if (xd >= 0 && xd < roi_x && yd >= 0 && yd < roi_y)
        // img.at<uchar>(yd, xd) = 255;
        img.at<uchar>(yd, xd) += 1;
    }
  }
  
  // delete points that appears lower than twice.
  Mat img_vote;
  int threshold_value = 1;			// 可配置参数
  cv::threshold(img, img_vote, threshold_value, 255, THRESH_BINARY);
```

## 4. 搜索操作
```
// 获得变换矩阵
getRotationMatrix2D( Point2f center, double angle, double scale );

// 模板旋转后的图像大小
cv::Rect bbox =
 cv::RotatedRect(center_, templ_.size(), degree).boundingRect();

// 旋转后的图像中心平移
// bbox 只有大小，旋转后，必须把图像平移，才能让图像居中
M.at<double>(0, 2) += bbox.width / 2.0 - center_.x;
M.at<double>(1, 2) += bbox.height / 2.0 - center_.y;

// 仿射变换
Mat templ_warpped;
warpAffine(templ_, templ_warpped, M, bbox.size()); // change



/// 通过函数 minMaxLoc 定位最匹配的位置
/// 创建输出结果的矩阵
int result_cols = img.cols - templ.cols + 1;
int result_rows = img.rows - templ.rows + 1;
Mat result = Mat::zeros(result_cols, result_rows, CV_32FC1);
matchTemplate(img, templ, result, match_method);
Mat result_show;
normalize(result, result_show, 0, 1, NORM_MINMAX, -1, Mat());
```

# 二、几种需要考虑的情况

## 1. 框选范围小于模板大小
```
 if ((x_length_ * resolution_inv_ + 0.5 < templ_.cols) ||
      (y_length_ * resolution_inv_ + 0.5 < templ_.rows))
  {
    const std::string error_string = "36002 | Too small roi!";
    ROS_WARN_THROTTLE(1, "%s", error_string.c_str());
    response.error_message = error_string;
    return true;
  }
```