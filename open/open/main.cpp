
#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;
/*
void creatAlpMat(Mat &mat)
{


	for (int i = 0; i < mat.rows; i++)
	{
		
		for (int j = 0; j < mat.cols; j++)
		{
			Vec4b &rgba = mat.at<Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);
			rgba[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);
			rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));


		}



	}




}
//图片叠加
void rongheImage(){

	Mat bigImg = imread("pic.jpg");
	Mat smallImg = imread("透明Alpha值图.png");
	Mat imagIO = bigImg(Rect(10, 10, smallImg.cols, smallImg.rows));

	addWeighted(imagIO, 0.5, smallImg, 0.5, 0, imagIO);

	imshow("lal", bigImg);

}
//改变图片的对比度和 亮度 
double alpha; < 控制对比度 
int beta;  < 控制亮度 
void changeImageHL() {

	/// 读入用户提供的图像
	Mat image = imread("pic.jpg");
	Mat new_image = Mat::zeros(image.size(), image.type());

	/// 初始化
	cout << " Basic Linear Transforms " << endl;
	cout << "-------------------------" << endl;
	cout << "* Enter the alpha value [1.0-3.0]: ";
	cin >> alpha;
	cout << "* Enter the beta value [0-100]: ";
	cin >> beta;

	/// 执行运算 new_image(i,j) = alpha*image(i,j) + beta
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	/// 创建窗口
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	/// 显示图像
	imshow("Original Image", image);
	imshow("New Image", new_image);

}

int main(){
	
at mat(400,400,CV_8UC4);
	creatAlpMat(mat);
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	//cout << "M = " << endl << " " << mat << endl << endl;
	
		imwrite("透明Alpha值图.png", mat, compression_params);
	
	fprintf(stdout, "PNG图片文件的alpha数据保存完毕~\n");
	
	Mat img = imread("pic.jpg");
	Mat newImg;
	
	// blur(img, newImg, Size(2,2));
	//GaussianBlur(img,newImg,Size(2,2),2,2);
	medianBlur(img, newImg, 2);
	/// 创建窗口
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	/// 显示图像
	imshow("Original Image", img);
	imshow("New Image", newImg);


	waitKey();



	return 0;
	//addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);
}
*/

/// 全局变量
Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

/** Function Headers */
void Erosion(int, void*);
void Dilation(int, void*);

/** @function main */
int main()
{
	/// Load 图像
	src = imread("pic.jpg");

	if (!src.data)
	{
		return -1;
	}

	/// 创建显示窗口
	namedWindow("Erosion Demo", CV_WINDOW_AUTOSIZE);
	namedWindow("Dilation Demo", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Dilation Demo", src.cols, 0);

	/// 创建腐蚀 Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
		&erosion_elem, max_elem,
		Erosion);

	createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
		&erosion_size, max_kernel_size,
		Erosion);

	/// 创建膨胀 Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
		&dilation_elem, max_elem,
		Dilation);

	createTrackbar("Kernel size:\n 2n +1", "Dilation Demo",
		&dilation_size, max_kernel_size,
		Dilation);

	/// Default start
	Erosion(0, 0);
	Dilation(0, 0);

	waitKey(0);
	return 0;
}

/**  @function Erosion  */
void Erosion(int, void*)
{
	int erosion_type;
	if (erosion_elem == 0) { erosion_type = MORPH_RECT; }
	else if (erosion_elem == 1) { erosion_type = MORPH_CROSS; }
	else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	/// 腐蚀操作
	erode(src, erosion_dst, element);
	imshow("Erosion Demo", erosion_dst);
}

/** @function Dilation */
void Dilation(int, void*)
{
	int dilation_type;
	if (dilation_elem == 0) { dilation_type = MORPH_RECT; }
	else if (dilation_elem == 1) { dilation_type = MORPH_CROSS; }
	else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));
	///膨胀操作
	dilate(src, dilation_dst, element);
	imshow("Dilation Demo", dilation_dst);
}


