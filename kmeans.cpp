#include "kmeans.h"

using namespace std;

float point::distanceTo(point b) {
    return sqrt(pow(this->x - b.x, 2) + pow(this->y - b.y, 2) + pow(this->z - b.z, 2));
}

float kmeans::clusters::recenter() {
    float x0 = 0;
    float y0 = 0;
    float z0 = 0;
    point o_center = this->center;
    for(int i=0; i<pts.size(); i++) {
        x0 += pts[i].x;
        y0 += pts[i].y;
        z0 += pts[i].z;
    }
    x0 /= pts.size();
    y0 /= pts.size();
    z0 /= pts.size();

    point new_cent = point();
    new_cent.x = (int)x0;
    new_cent.y = (int)y0;
    new_cent.z = (int)z0;
    center = new_cent;
    return o_center.distanceTo(center);
}

kmeans::kmeans(int*** map, int k) {
    this->map = map;
    this->k = k;
}

vector<point> kmeans::cluster() {
	vector<point> palette;
	
    int width = 256;
    int height = 256;
    int depth = 256;
    float delta = 0.001;
    vector<clusters> centers;
    point temp = point();
    clusters t_c;
	
	int i = 0;
    while(i < k) {
        temp.x = (int)rand()%width;
        temp.y = (int)rand()%height;
        temp.z = (int)rand()%depth;
        if(map[(int)temp.x][(int)temp.y][(int)temp.z] > 0){
			i++;
			t_c.center = temp;
			centers.push_back(t_c);
		}
	}
	
    while(true) {
        for(int i=0; i < width; i++) {
            for(int j=0; j < height; j++) {
                for(int k=0; k < depth; k++) {
                    if(map[i][j][k] > 0) {
                        float min_distance = 9999999;
                        int q;
                        point temp_pt = point();
                        temp_pt.x = i;
                        temp_pt.y = j;
                        temp_pt.z = k;
                        for(int p=0; p < centers.size(); p++) {
                            float distance = temp_pt.distanceTo(centers[p].center);
                            if(distance < min_distance) {
                                min_distance = distance;
                                q = p;
                            }
                        }
                        centers[q].pts.push_back(temp_pt);
                    }
                }
            }
        }
        float max_delta = -9999999;
        for(int p=0; p < centers.size(); p++) {
            float dist_moved;
            dist_moved = centers[p].recenter(); 
            if(dist_moved > max_delta) {
                max_delta = dist_moved;
            }
        }
        if(max_delta < delta) {
            for(int p=0; p < centers.size(); p++) {
                cout << "RGB: (" << centers[p].center.x << "," << centers[p].center.y << "," << centers[p].center.z << ") ------- ";
                printf("#%02x%02x%02x\n", (int)centers[p].center.x,(int)centers[p].center.y,(int)centers[p].center.z);
                palette.push_back(centers[p].center);
            }
            
            return palette;
        }
        for(int p=0; p<centers.size(); p++) {
            centers[p].pts.clear();
        }
    }
}