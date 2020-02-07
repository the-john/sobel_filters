#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void gradientSobel()
{
    // TODO: Based on the image gradients in both x and y, compute an image 
    // which contains the gradient magnitude according to the equation at the 
    // beginning of this section for every pixel position. Also, apply different 
    // levels of Gaussian blurring before applying the Sobel operator and compare the results.
    
    // Pull in an image and make it gray scale
    cv::Mat img;
    img = cv::imread("../images/img1gray.png");

    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // Gaussian blurring
    cv::Mat blurred = imgGray.clone();
    int filterSize = 5;
    int stdDev = 2;
    cv::GaussianBlur(imgGray, blurred, cv::Size(filterSize, filterSize), stdDev);

    // Filter kernels
    float sobel_x[9] = {-1, 0, 1, 
                        -2, 0, 2, 
                        -1, 0, 1};
    cv::Mat kernel_x = cv::Mat(3, 3, CV_32F, sobel_x);
    float sobel_y[9] = {-1, -2, -1, 
                         0, 0, 0, 
                         1, 2, 1};
    cv::Mat kernel_y = cv::Mat(3, 3, CV_32F, sobel_y);

    // Use filters
    cv::Mat result_x;
    cv::Mat result_y;

    cv::filter2D(blurred, result_x, -1, kernel_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::filter2D(blurred, result_y, -1, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    // Let's see what we got now
    string windowName01 = "Gradient x Sobel";
    cv::namedWindow(windowName01, 1);  // create the window
    cv::imshow(windowName01, result_x);

    string windowName02 = "Gradient y Sobel";
    cv::namedWindow(windowName02, 1);  // create the window
    cv::imshow(windowName02, result_y);
    
    cv::waitKey(0);  // wait for keyboard input before continuing
    
}

int main()
{
    gradientSobel();
}