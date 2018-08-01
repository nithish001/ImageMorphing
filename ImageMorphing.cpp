




/**
---Read Me -----

Name :Mattela Nithish.
Entry Number:2016csb1042

-----Compilation------
$ g++ -ggdb ImageMorphing.cpp `pkg-config --cflags --libs opencv`
$./a.out

-----about------
  This has 2 functions, first one is to transform one image where affine transform matrix is given,
second one is changing from image1 to image2 where tie points are given using delaunay trianglulation technique.
This program generates multiple intermediate images. You can generate GIF by saving all the images in a folder
and write this command in shell
$ sudo apt-get install imagemagick
$ convert -resize 50% -delay 10 -loop 0 image_{0..n}.jpg output.gif //where n is number images.
*/










#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace cv;
using namespace std;


/*
This is from input image to final image where points are given as text file

text file points format:
  <x-coordinate> <y-coordinate>

*/
void func1()
{
    //string win_delaunay = "Delaunay Triangulation";
    //bool animate = true;
    Scalar delaunay_color(255,255,255), points_color(0, 0, 255);
    string inp_string,out_string;
    cout << "enter input image path:";
    cin >> inp_string;
    cout << "enter output image path:";
    cin >> out_string;
    Mat input_img = imread(inp_string,0);
    Mat output_img = imread(out_string,0);
   // //cout << "output_img" << " " << output_img.rows << " " << output_img.cols << endl;
    Mat img_orig = input_img.clone();
    Size size = input_img.size();
    Rect rect(0, 0,  size.height,size.width);
    Mat inter_img(size.height,size.width,CV_8U,0.0);
    Subdiv2D subdiv(rect),subdiv_out(rect);
    vector<Point2f> points_inp,points_out;
    cout << "enter tie points file path of input image";
    string inp_file;
    cin >> inp_file;
    ifstream ifs(inp_file.c_str());
    int x, y;
    ////cout << "donald\n";
    while(ifs >> y >> x)
    {
    	//cout << "asdfsa"
        points_inp.push_back(Point2f(x,y));
        ////cout << x << " " << y << endl;
    }
    ifs.close();
    cout << "enter tie points file path of output iamge";
    string out_file;
    cin >> out_file;

    ifs.open(out_file.c_str());
    ////cout << "hilary\n";
    while(ifs >> y >> x){
    	//cout << "asfsa"
    	points_out.push_back(Point2f(x,y));
    	////cout << x << " " << y << endl;
    }
    for( vector<Point2f>::iterator it = points_inp.begin(); it != points_inp.end(); it++){
        subdiv.insert(*it);
    }

    for( vector<Point2f>::iterator it = points_out.begin(); it != points_out.end(); it++){
        subdiv_out.insert(*it);
    }

    vector<Vec6f>trianglelist1;
    subdiv.getTriangleList(trianglelist1);


    vector<Point2f> trianglelist[trianglelist1.size()];

    for(int iter=0;iter<trianglelist1.size();iter++){
	   	vector<Point>pt(3);

	   	pt[0] = Point(cvRound(trianglelist1[iter][0]), cvRound(trianglelist1[iter][1]));
	   	pt[1] = Point(cvRound(trianglelist1[iter][2]), cvRound(trianglelist1[iter][3]));
	   	pt[2] = Point(cvRound(trianglelist1[iter][4]), cvRound(trianglelist1[iter][5]));

		trianglelist[iter].push_back(pt[0]);
	   	trianglelist[iter].push_back(pt[1]);
	   	trianglelist[iter].push_back(pt[2]);

	}


    vector<Vec6f>trianglelist1out;
    subdiv_out.getTriangleList(trianglelist1out);


    vector<Point2f> trianglelistout[trianglelist1out.size()];

    for(int iter=0;iter<trianglelist1out.size();iter++){
	   	vector<Point>pt(3);

	   	pt[0] = Point(cvRound(trianglelist1out[iter][0]), cvRound(trianglelist1out[iter][1]));
	   	pt[1] = Point(cvRound(trianglelist1out[iter][2]), cvRound(trianglelist1out[iter][3]));
	   	pt[2] = Point(cvRound(trianglelist1out[iter][4]), cvRound(trianglelist1out[iter][5]));

		trianglelistout[iter].push_back(pt[0]);
	   	trianglelistout[iter].push_back(pt[1]);
	   	trianglelistout[iter].push_back(pt[2]);

	}
	//observation:negative vertices and the coordinates are very large sometimes
	////cout << trianglelist[1] << "\n" << trianglelistout[1] << endl;
	int nf=10;
    for(int i=0;i<=nf;i++){
    	////cout << "start loop\n";
    	for(int li = 0;li<inter_img.rows;li++){
    		for(int lj=0;lj<inter_img.cols;lj++){
    			int colorse = 0;
    			inter_img.at<uchar>(li,lj) = colorse;
    		}
    	}
    	//imshow("adsf",inter_img);
    	//waitKey(0);
    	vector<Point2f> points_inter;

    	Subdiv2D subdiv_inter(rect);

    	for(int j=0;j<points_inp.size();j++){
    		int x1 = (1-(double)i/nf)*points_inp[j].x + ((double)i/nf)*points_out[j].x;
    		int y1 = (1-(double)i/nf)*points_inp[j].y + ((double)i/nf)*points_out[j].y;

    		points_inter.push_back(Point2f(x1,y1));

    		//draw_point(inter_img,(Point2f(x1,y1)),points_color);
    	}
    	////cout << "2\n";
    	for( vector<Point2f>::iterator it = points_inter.begin(); it != points_inter.end(); it++){
        	subdiv_inter.insert(*it);
    	}
    	//vector<Vec6f>trianglelist_inter;


    	vector<Vec6f>trianglelist2;
    	subdiv_inter.getTriangleList(trianglelist2);

    	vector<Point2f>trianglelist_inter[trianglelist2.size()];

		for(int iter=0;iter<trianglelist2.size();iter++){
		   	vector<Point>pt1(3);

		   	pt1[0] = Point(cvRound(trianglelist2[iter][0]), cvRound(trianglelist2[iter][1]));
		   	pt1[1] = Point(cvRound(trianglelist2[iter][2]), cvRound(trianglelist2[iter][3]));
		   	pt1[2] = Point(cvRound(trianglelist2[iter][4]), cvRound(trianglelist2[iter][5]));


		   	trianglelist_inter[iter].push_back(pt1[0]);
		   	trianglelist_inter[iter].push_back(pt1[1]);
		   	trianglelist_inter[iter].push_back(pt1[2]);


		}
		////cout << "4\n";

    	for(int li = 0;li<inter_img.rows;li++){
    		for(int lj=0;lj<inter_img.cols;lj++){
    			//inter_img.at<Vec3b>(li,lj) = input_img.at<Vec3b>(li,lj);
    			//int req_tri1 = 0;
    			//int req_tri2 = 0;

    			////cout << "start start start start start\n";
    			for(int lk=0;lk<trianglelist2.size();lk++){

    				float xA = trianglelist2[lk][0];
    				float yA = trianglelist2[lk][1];
    				float xB = trianglelist2[lk][2];
    				float yB = trianglelist2[lk][3];
    				float xC = trianglelist2[lk][4];
    				float yC = trianglelist2[lk][5];
    				////cout << "value of lk is "<<lk<<endl;
    				////cout << xA << " " << yA << " "<<xB << " "<<yB << " " <<xC << " " << yC << endl;
    				////cout << "here lk value is "<<lk<<" "<<trianglelist2[lk] << endl;
    				////cout << "pls no\n";
    				float xM = li;
    				float yM = lj;
    				////cout << "triangle points are:\n"<<xA << " " <<yA <<" "<<xB << " " << yB << " " << xC << " " << yC << "\n\n\n";
    				if((xA < input_img.rows && yA < input_img.cols && xB < output_img.rows && yB < output_img.cols && xC < output_img.rows && yC < output_img.cols) &&xA >=0 && yA>=0&& xB >= 0&& yB >= 0 && xC >= 0&& yC >= 0){
						float area1 = (0.5)*(abs((xA-xC)*(yB-yA)-(xA-xB)*(yC-yA)));
						float area2 = (0.5)*(abs((xA-xC)*(yM-yA)-(xA-xM)*(yC-yA)));
						float area3 = (0.5)*(abs((xM-xC)*(yB-yM)-(xM-xB)*(yC-yM)));
						float area4 = (0.5)*(abs((xA-xM)*(yB-yA)-(xA-xB)*(yM-yA)));
						////cout  << lk << " "<< area1 << " " << area2 << " " << area3 << " " << area4 << "\n\n\n\n";

						if(abs(area1-area2-area3-area4)<=0.01){
							vector<Point2f>inter_tri;
							inter_tri.push_back(Point2f(cvRound(xA),cvRound(yA)));
							inter_tri.push_back(Point2f(cvRound(xB),cvRound(yB)));
							inter_tri.push_back(Point2f(cvRound(xC),cvRound(yC)));


							vector<Point2f>init_tri[3];
							vector<Point2f>fin_tri[3];
							////cout << "found triangle\n";

							//cout << xA << " " << yA << " " << xB << " " << yB << " "<< xC << " " << yC << endl;
							int count = 0;
							for( int g=0;g<points_inter.size();g++){
								////cout << points_inter[g].x << " " << points_inter[g].y << endl;
		    					if(points_inter[g].x==xA && points_inter[g].y==yA){
									init_tri[0].push_back(points_inp[g]);
									fin_tri[0].push_back(points_out[g]);
		    					}
		    					if(points_inter[g].x==(xB)&&points_inter[g].y==(yB)){
									init_tri[1].push_back(points_inp[g]);
									fin_tri[1].push_back(points_out[g]);
		    					}
		    					if(points_inter[g].x==xC&&points_inter[g].y==yC){
									init_tri[2].push_back(points_inp[g]);
									fin_tri[2].push_back(points_out[g]);
		    					}
		    					count++;
							}
							////cout << "calculated points\n";
							////cout << count << endl;

							//3*2 input points
							vector<Point2f>in_tri;
							in_tri.push_back(init_tri[0][0]);
							in_tri.push_back(init_tri[1][0]);
							in_tri.push_back(init_tri[2][0]);


							//3*2 final points
							vector<Point2f>fi_tri;
							fi_tri.push_back(fin_tri[0][0]);
							fi_tri.push_back(fin_tri[1][0]);
							fi_tri.push_back(fin_tri[2][0]);

							////cout << "mad the points\n";

							Mat affine1 = getAffineTransform(inter_tri,in_tri);
							Mat affine2 = getAffineTransform(inter_tri,fi_tri);
							int X_1,Y_1,X_2,Y_2;

							X_1 = affine1.at<double>(0,0)*(double)li + affine1.at<double>(0,1)*(double)lj + affine1.at<double>(0,2);
    						Y_1 = affine1.at<double>(1,0)*(double)li + affine1.at<double>(1,1)*(double)lj + affine1.at<double>(1,2);

    						X_2 = affine2.at<double>(0,0)*(double)li + affine2.at<double>(0,1)*(double)lj + affine2.at<double>(0,2);
    						Y_2 = affine2.at<double>(1,0)*(double)li + affine2.at<double>(1,1)*(double)lj + affine2.at<double>(1,2);

    						//if((X_1 < input_img.rows && Y_1 < input_img.cols && X_2 < output_img.rows && Y_2 < output_img.rows) && X_1 >=0 && Y_1>=0&& X_2 >= 0&& Y_2 >= 0){

    							inter_img.at<uchar>(li,lj) = (1-(float)i/nf)*input_img.at<uchar>(X_1,Y_1) + ((float)i/nf)*output_img.at<uchar>(X_2,Y_2);

    						//}

							break;
						}
					}
					    						//cout << X_2 << " " <<Y_2<< " next " <<X_1<<" " <<Y_1 << endl;
    			}
    			////cout<<"end end end end\n";
    		}
    	}
    	//draw_delaunay( inter_img,subdiv_inter);

    	////cout << "asda\n";
    	ostringstream str1;
    	str1 << i;
    	imshow("Morphed_image",inter_img);
    	//string file_out = "./image6/" + str1.str()+".jpg";
    	//cout << file_out << endl;
    	//imwrite(file_out,inter_img);
    	waitKey(20);



    	////cout << "after\n";
    }
}


void func2(){
	double affine_trans[2][3];
	cout << "enter the affine transformation:";
	for(int i=0;i<2;i++){
		for(int j=0;j<3;j++){
			cin >> affine_trans[i][j];
		}
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<3;j++){
			cout << affine_trans[i][j] << " ";
		}
		cout << endl;
	}


	cout << "enter the path of input image:";
	string inp_path;
	cin >> inp_path;
	Mat inp_img = imread(inp_path,0.0);

	double inp_points[4][2];
	inp_points[0][0] = 0 - inp_img.rows/2;
	inp_points[0][1] = 0 - inp_img.cols/2;
	inp_points[1][0] = inp_img.rows-1-inp_img.rows/2;
	inp_points[1][1] = 0-inp_img.cols/2;
	inp_points[2][0] = 0-inp_img.rows/2;
	inp_points[2][1] = inp_img.cols-1-inp_img.cols/2;
	inp_points[3][0] = inp_img.rows-1-inp_img.rows/2;
	inp_points[3][1] = inp_img.cols-1-inp_img.cols/2;

	double out_points[4][2];
	for(int i=0;i<4;i++){
		out_points[i][0] = (inp_points[i][0])*affine_trans[0][0] + (inp_points[i][1])*affine_trans[0][1] + affine_trans[0][2];
		out_points[i][1] = (inp_points[i][0])*affine_trans[1][0] + (inp_points[i][1])*affine_trans[1][1] + affine_trans[1][2];

	}

	vector<Point2f>inp_tri;
	inp_tri.push_back(Point2f(inp_points[0][0],inp_points[0][1]));
	inp_tri.push_back(Point2f(inp_points[1][0],inp_points[1][1]));
	inp_tri.push_back(Point2f(inp_points[2][0],inp_points[2][1]));
	cout << "enter number of frames:";
	int nf;
	cin >> nf;


	imshow("input",inp_img);
	waitKey(0);

	for(int i=0;i<=nf;i++){
		double morf_points[4][2];
		//cout << "morph\n";
		for(int li=0;li<4;li++){
			morf_points[li][0] = (1-(double)i/nf)*inp_points[li][0] + ((double)i/nf) * out_points[li][0];
			morf_points[li][1] = (1-(double)i/nf)*inp_points[li][1] + ((double)i/nf) * out_points[li][1];
			//cout << inp_points[li][0] <<" "<< inp_points[li][1] <<" "<< morf_points[li][0] <<" "<< morf_points[li][1] << endl;
		}
		double morf_rows_min=100000,morf_rows_max=0,morf_cols_min=100000,morf_cols_max=0;

		for(int li=0;li<4;li++){
			if(morf_rows_max<morf_points[li][0]){
				morf_rows_max = morf_points[li][0];
			}

			if(morf_rows_min>morf_points[li][0]){
				morf_rows_min = morf_points[li][0];
			}


			if(morf_cols_max<morf_points[li][1]){
				morf_cols_max = morf_points[li][1];
			}

			if(morf_cols_min>morf_points[li][1]){
				morf_cols_min = morf_points[li][1];
			}
		}

		vector<Point2f>morf_tri;
		morf_tri.push_back(Point2f(morf_points[0][0],morf_points[0][1]));
		morf_tri.push_back(Point2f(morf_points[1][0],morf_points[1][1]));
		morf_tri.push_back(Point2f(morf_points[2][0],morf_points[2][1]));

		Mat morf_img(morf_rows_max-morf_rows_min,morf_cols_max-morf_cols_min,CV_8U,0.0);

		//cout << morf_img.rows << " " << morf_img.cols << "FAKJF" << endl;

		Mat affine_temp = getAffineTransform(morf_tri,inp_tri);

		//cout << affine_temp << endl;

		for(int li=0;li<morf_img.rows;li++){
			for(int lj=0;lj<morf_img.cols;lj++){
				int inp_x,inp_y;
				inp_x = (li-morf_img.rows/2)*affine_temp.at<double>(0,0) + (lj-morf_img.cols/2)*affine_temp.at<double>(0,1) + affine_temp.at<double>(0,2);
				inp_y = (li-morf_img.rows/2)*affine_temp.at<double>(1,0) + (lj-morf_img.cols/2)*affine_temp.at<double>(1,1) + affine_temp.at<double>(1,2);
				//cout << inp_x << " " << inp_y << endl;
				if((inp_x+inp_img.rows/2)>=0 && (inp_x+inp_img.rows/2)<inp_img.rows && (inp_y+inp_img.cols/2)>=0 && (inp_y+inp_img.cols/2) < inp_img.cols){
					//cout << inp_x
					morf_img.at<uchar>(li,lj) = inp_img.at<uchar>(inp_x + inp_img.rows/2,inp_y + inp_img.cols/2);
				}
			}
		}

    	imshow("Morphed_image",morf_img);
    	waitKey(20);
	}

	/*for(int i=0;i<nf;i++){
		imshow("Morfing",morf_img[i]);
		waitKey(0);
	}*/

}

int main(){
	while(1){
		int choice;
		cout << "1 for affine transformation\n";
		cout << "2 for image morphing\n";
		cin >> choice;
		if(choice==1){
			func2();
		}
		else{
			func1();
		}
	}
}
