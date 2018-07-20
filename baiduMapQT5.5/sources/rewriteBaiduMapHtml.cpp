#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#define MARKER_NUM 200
#define MARKER_WIDTH 0
#define MARKER_HEIGHT 3

using namespace std;

double lat[MARKER_NUM] = {39.978006};
double lng[MARKER_NUM] = {116.360846};

int main()
{
    ifstream in("/home/hirain/baidumap/baidumap.html");
    ofstream out("/home/hirain/baidumap/baidumap_1.html");
    string line;
    string mapCenter = "map.centerAndZoom";
    string markers = "var markers";

    for(int i = 1; i < MARKER_NUM; i++)
    {
        lat[i] = lat[0] + 0.001*i;
        lng[i] = lng[0];
    }


    if(in) // 有该文件
    {
        while (getline (in, line)) // line中不包括每行的换行符
        { 
            string::size_type idx = line.find(mapCenter);
            string::size_type idy = line.find(markers);

            if(idx != string::npos) //find
            {
                ostringstream center;
                center.precision(9);
                center << "\t\t\tmap.centerAndZoom(new BMap.Point(";
                center << lng[0] << ","<<lat[0]<<"),19)";
                out << center.str() << endl;
                continue;

            }

            if(idy != string::npos)// find
            {
                //cout << line << endl;
                out << line << endl;
                for(int i = 0; i < MARKER_NUM; i++)
                {
                    ostringstream new_marker;
                    new_marker.precision(9);
                    new_marker <<"\t\t\t\t{content:\"\",title:\"\",imageOffset: {width:" << MARKER_WIDTH;
                    new_marker <<",height:" << MARKER_HEIGHT;
                    new_marker <<"},position:{lat:" << lat[i];
                    if(i == MARKER_NUM  - 1)
                        new_marker <<",lng:" << lng[i] <<"}}";
                    else
                        new_marker <<",lng:" << lng[i] <<"}},";

                    out << new_marker.str() << endl;
                }
            }
            else
            {
                out << line << endl;
                //cout << "no markers in this file" <<endl;
            }
            
            
        }
    }
    else // 没有该文件
    {
        cout <<"no such file" << endl;
    }

    return 0;
}