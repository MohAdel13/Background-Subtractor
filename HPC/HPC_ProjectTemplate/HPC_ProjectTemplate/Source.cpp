#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<msclr\marshal_cppstd.h>
#include<mpi.h>
#include<stdio.h>
#include <ctime>// include this header 
#pragma once

#using <mscorlib.dll>
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
using namespace std;
using namespace msclr::interop;

int* inputImage(int* w, int* h, System::String^ imagePath) //put the size of image in w & h
{
	int* input;


	int OriginalImageWidth, OriginalImageHeight;

	//********************************************************* Read Image and save it to local arrays *************************	
	//Read Image and save it to local arrays

	System::Drawing::Bitmap BM(imagePath);

	OriginalImageWidth = BM.Width;
	OriginalImageHeight = BM.Height;
	*w = BM.Width;
	*h = BM.Height;
	int *Red = new int[BM.Height * BM.Width];
	int *Green = new int[BM.Height * BM.Width];
	int *Blue = new int[BM.Height * BM.Width];
	input = new int[BM.Height*BM.Width];
	for (int i = 0; i < BM.Height; i++)
	{
		for (int j = 0; j < BM.Width; j++)
		{
			System::Drawing::Color c = BM.GetPixel(j, i);

			Red[i * BM.Width + j] = c.R;
			Blue[i * BM.Width + j] = c.B;
			Green[i * BM.Width + j] = c.G;

			input[i*BM.Width + j] = ((c.R + c.B + c.G) / 3); //gray scale value equals the average of RGB values

		}

	}
	return input;
}


vector<int> inputImage2(int* w, int* h, System::String^ imagePath) //put the size of image in w & h
{


	int OriginalImageWidth, OriginalImageHeight;

	//*********************************************************Read Image and save it to local arrayss*************************	
	//Read Image and save it to local arrayss

	System::Drawing::Bitmap BM(imagePath);

	OriginalImageWidth = BM.Width;
	OriginalImageHeight = BM.Height;
	*w = BM.Width;
	*h = BM.Height;
	vector<int> input(BM.Width*BM.Height);
	for (int i = 0; i < BM.Height; i++)
	{
		for (int j = 0; j < BM.Width; j++)
		{
			System::Drawing::Color c = BM.GetPixel(j, i);
			input[i * BM.Width + j] = ((c.R + c.B + c.G) / 3); //gray scale value equals the average of RGB values
		}

	}
	return input;
}

void createImage(int* image, int width, int height, int index)
{
	System::Drawing::Bitmap MyNewImage(width, height);


	for (int i = 0; i < MyNewImage.Height; i++)
	{
		for (int j = 0; j < MyNewImage.Width; j++)
		{
			//i * OriginalImageWidth + j
			if (image[i*width + j] < 0)
			{
				image[i*width + j] = 0;
			}
			if (image[i*width + j] > 255)
			{
				image[i*width + j] = 255;
			}
			System::Drawing::Color c = System::Drawing::Color::FromArgb(image[i*MyNewImage.Width + j], image[i*MyNewImage.Width + j], image[i*MyNewImage.Width + j]);
			MyNewImage.SetPixel(j, i, c);
		}
	}
	if (index==0)
	{
		MyNewImage.Save("..//Data//Output//Background" + ".png");
	}
	else
	{
		MyNewImage.Save("..//Data//Output//Forground" + ".png");
	}
	cout << "result Image Saved " << index << endl;
}

vector<vector<int>> getimage(int *ImageWidth,int* ImageHeight)
{
	vector<string> paths(492);
	System::String^ imagePath;
	vector<vector<int>>imageData(492);
	for (int i = 0; i < 492; i++)
	{
		if (i < 9)
		{
			paths[i] = (string)"..//Data//Input//in000"+(string)"00"+ to_string(i+1) + (string)".jpg";
		}
		else if (i < 99)
		{
			paths[i] = (string)"..//Data//Input//in000" + (string)"0" + to_string(i+1) + (string)".jpg";
		}
		else
		{
			paths[i] = (string)"..//Data//Input//in000"+ to_string(i+1) + (string)".jpg";
		}

	}
	for (int i = 0; i < 492; i++)
	{
		imagePath = marshal_as<System::String^>(paths[i]);
		imageData[i] = inputImage2(ImageWidth, ImageHeight, imagePath);
	}
	return imageData;
}


//-------------------------------------------------------------------------------
//*******************************Sequential**************************************
//-------------------------------------------------------------------------------

//int main()
//{
//	int ImageWidth = 4, ImageHeight = 4;
//
//	int start_s, stop_s, TotalTime = 0;
//	start_s = clock();
//	System::String^ imagePath;
//	std::string img[495]={};
//	//string BackImg,ForImg;
//	for (int i = 0; i < 495; i++)
//	{
//		if (i < 9)
//		{
//			img[i] = (string)"..//Data//Input//in000"+(string)"00"+ to_string(i+1) + (string)".jpg";
//		}
//		else if (i < 99)
//		{
//			img[i] = (string)"..//Data//Input//in000" + (string)"0" + to_string(i+1) + (string)".jpg";
//		}
//		else
//		{
//			img[i] = (string)"..//Data//Input//in000"+ to_string(i+1) + (string)".jpg";
//		}
//	}
//	int* imageData[495];
//	for (int i = 0; i < 495; i++)
//	{
//		imagePath = marshal_as<System::String^>(img[i]);
//		imageData[i] = inputImage(&ImageWidth, &ImageHeight, imagePath);
//	}
//
//	int* BackImage=new int[ImageWidth * ImageHeight];
//	int* ForImage = new int[ImageWidth * ImageHeight];
//
//	for (int i = 0; i < ImageWidth* ImageHeight; i++)
//	{
//		BackImage[i] = 0;
//		for (int j = 0; j < 495; j++)
//		{
//			BackImage[i] += imageData[j][i];
//		}
//		BackImage[i] /= 495;
//	}
//
//	for (int i = 0; i < ImageWidth * ImageHeight; i++)
//	{
//		ForImage[i] = 0;
//		if (abs(imageData[280][i] - BackImage[i])>30)
//		{
//			ForImage[i] = 255;
//		}
//		else
//		{
//			ForImage[i] = 0;
//		}
//	}
//	createImage(BackImage, ImageWidth, ImageHeight, 0);
//	createImage(ForImage, ImageWidth, ImageHeight, 1);
//	stop_s = clock();
//	TotalTime += (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
//	cout << "time: " << TotalTime << endl;
//
//	return 0;
//
//}


//-------------------------------------------------------------------------------
//*******************************Parallel****************************************
//-------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	System::String^ imagePath="..//Data//Input//in000282.jpg";
	int ImageWidth = 4, ImageHeight = 4;
	int start_s, stop_s, TotalTime = 0;
	start_s = clock();
	int size, rank;
	int* Data=new int;
	int myimage[123*320*240];
	int mybackground[320 * 240];
	int backimage[4*76800];
	int *sampleimage;
	MPI_Init(NULL, NULL);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{

		vector<vector<int>> imageData = getimage(&ImageWidth, &ImageHeight);
		Data=new int[492 * ImageWidth * ImageHeight];
		for (int i = 0; i <imageData.size(); i++)
		{
			for (int j = 0; j < imageData[i].size(); j++)
			{
				Data[i * imageData[i].size() + j] = imageData[i][j];
			}
		}
	}
	MPI_Scatter(Data, 123 * 76800, MPI_INT, myimage, 123 * 76800, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < 76800; i++)
	{
		int sum = 0;
		for (int j = 0; j < 123; j++)
		{
			sum += myimage[i+j*76800];
		}
		mybackground[i] = sum / 123;
	}
	MPI_Gather(mybackground, 76800, MPI_INT, backimage, 76800, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank==0)
	{
		int newback[76800];
		int newfor[76800];
		for (int i = 0; i < 76800; i++)
		{
			int sum = 0;
			for (int j = 0; j < 4; j++)
			{
				sum += backimage[i + j * 76800];
			}
			newback[i] = sum / 4;
		}
		sampleimage = inputImage(&ImageWidth, &ImageHeight, imagePath);
		for (int i = 0; i < 76800; i++)
		{
			if (abs(sampleimage[i]-newback[i])>30)
			{
				newfor[i] = 255;
			}
			else
			{
				newfor[i] = 0;
			}
		}
		createImage(newback, ImageWidth, ImageHeight, 0);
		createImage(newfor, ImageWidth, ImageHeight, 1);
	}
	stop_s = clock();
	TotalTime += (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
	cout << "time: " << TotalTime << endl;
	MPI_Finalize();
	return 0;
}



