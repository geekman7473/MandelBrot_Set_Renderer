#include <iostream>
#include "EasyBMP\EasyBMP.h"
#include <stdio.h>
#include <assert.h>
#include<cstdlib>
#include<string>
#include<sstream>
#include "gmp.h"

using namespace std;

#define iterMax 10000

string intToString(long long int val);
string doubleToString(long double val);

int main()
{
    mpz_t a,b,c;
mpz_init2(a,NULL);
mpz_init2(b,NULL);
mpz_init2(c,NULL);

mpz_set_str(a, "1234",10);
mpz_set_str(b,"-5678",10); //Decimal base

mpz_add(c,a,b);

cout<<"\nThe exact result is:";
mpz_out_str(stdout,10,c);
cout<<endl;

mpz_abs(c,c);
cout<<"The absolute value result is:";
mpz_out_str(stdout,10,c);
cout<<endl;

//cin.get();

    mpf_t x, y, z;

    mpf_init2(x, NULL);
    mpf_init2(y, NULL);
    mpf_init2(z, NULL);

    //mpf_set()

    long long int totalIters = 0;
    long long max_iteration = iterMax;
    BMP test;
    test.SetSize(1920, 1080);
    long double zoomFactor =1;
    long long int totalZooms = 1;
    long double totalZoomFactNum = 0;
while (zoomFactor < 100000000000000000000000000000000000){

    long double xPan = -1.74006238257933990522084416706582563829664172043617;
    long double yPan = 0;//0.02817533977921104899241152114431950968753907674299;
    //cout << xPan << endl << yPan << endl;
    //system("PAUSE");
    for(long double i = 0; i < test.TellWidth(); i++){
        for(long double j = 0; j < test.TellHeight(); j++){

                long double x0 = (i / ((long double) test.TellWidth() / (3.5/zoomFactor))) -(2.5/zoomFactor) + xPan;
                long double y0 = (j /  ((long double)test.TellHeight()/ (2.0/zoomFactor))) - (1/zoomFactor) + yPan;
                //cout << i << " " << x0 << " " << j << " " << y0 << endl;
                //system("PAUSE");
                long double x = 0;
                long double y =0;

                long long iteration = 0;

                while((x*x) + (y*y) < 4 && iteration < max_iteration){
                    long double xtemp = (x*x) - (y*y) + x0;
                    y = (2*x*y) + y0;

                    x = xtemp;
                    totalIters++;
                    iteration++;
                }
                //cout << iteration << " " << max_iteration << endl << 255 - (iteration / ((max_iteration/2) / 255)) << endl;
                //system("PAUSE");
                if (iteration >= max_iteration){
                    test(i, j)->Red = 0;
                    test(i, j)->Green = 0;
                    test(i, j)->Blue = 0;
                } else {

                    long temp = iteration * (16777216 / max_iteration);
                    test(i, j)->Red = temp / 65025;
                    temp -= test(i, j)->Red;
                    test(i, j)->Green = temp / 255;
                    temp -= test(i, j)->Green;
                    test(i, j)->Blue = temp;
                }
                /*} else if (iteration < max_iteration/2) {
                    test(i, j)->Red = iteration / ((max_iteration/2) / 255);
                    test(i, j)->Green = 0;
                    test(i, j)->Blue = 255 - (iteration / ((max_iteration/2) / 255));
                } else {
                    test(i, j)->Red = iteration / ((max_iteration/2) / 255);
                    test(i, j)->Green = iteration / ((max_iteration/2) / 255);
                    test(i, j)->Blue = 255;// - (iteration / ((max_iteration/2) / 255));
                }*/
        }
        if ((long long)i % 500 == 0){
            cout << i << "/" << test.TellWidth() << endl;
        }
    }
    string filename = intToString(totalZooms) + " " + doubleToString((double)xPan) + "," + doubleToString((double)yPan) + " AT " + doubleToString((double)zoomFactor) + " " +  intToString(test.TellWidth()) + "x" + intToString(test.TellHeight()) + "@" + intToString(max_iteration) + ".bmp";
    cout <<endl << filename;
    test.WriteToFile(filename.c_str());
    //zoomFactor += (pow(2,floor(log2((double)zoomFactor))) / 30);

    //cout << endl << totalIters;
    //cout << endl << ((pow(2,floor(log2((double)zoomFactor))) / 30) * .75) << endl << totalZooms << " " << totalZooms % 30 << " "<< (double)(totalZooms % 30) / 29 << " " << ((pow(2,floor(log2((double)zoomFactor))) / 30) * .75) * (1 + ((double)(totalZooms % 30) / 30)) << endl;
    //system("PAUSE");
    zoomFactor  += ((pow(2,floor(log2((double)zoomFactor))) / 30) * .75) * (1 + ((double)((totalZooms +0) % 30) / 30));
    totalZoomFactNum += ((pow(2,floor(log2((double)zoomFactor))) / 30) * .75) * (1 + ((double)(totalZooms % 30) / 30));
    //cout <<endl <<totalZoomFactNum / totalZooms << endl;
    totalZooms++;
}
    return 0;
}

string intToString(long long int val){
    stringstream ss;
    ss << val;
    return  ss.str();
}
string doubleToString(long double val){
    stringstream ss;
    ss << val;
    return  ss.str();
}
