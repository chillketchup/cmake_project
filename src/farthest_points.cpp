#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct point{double x, y, z;};

std::vector <point> points;
const int thread_count = 4;

// calculate distance between two points
double find_distance(point a, point b){
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

// find farthest pair of points
std::pair <point, point> find_farthest_points(int start, int end){
    double farthest_dist = 0;
    std::pair <point, point> farthest_points;

    // iterate through every pair of points
    for(int i = start; i < end; i++){
        int index;

        if(i % 2 == 0) index = i/2;
        else index = points.size() - i/2;

        for(int j = index+1; j < points.size(); j++){

            // find distance between pair of points
            double dist = find_distance(points[index], points[j]);

            // check if distance is greatest so far
            if(dist > farthest_dist){
                farthest_dist = dist;
                farthest_points = std::make_pair(points[index], points[j]);
            }
        }
    }

    return farthest_points;
}

int main(){
    /*
    std::string file_name;

    // 
    std::cout << "enter file name (include extension):" << std::endl;
    std::cin >> file_name;

    // take input from file
    std::ifstream input_file(file_name);
    */

    point p;

    while(std::cin >> p.x >> p.y >> p.z){
        points.push_back(p);
    }

    int chunk_size = points.size() / thread_count;
    double farthest_dist = 0;
    std::pair <point, point> farthest_points;

    for(int i = 0; i < thread_count; i++){
        int start = i * chunk_size;
        int end = std::min(start + chunk_size, int(points.size()));

        std::pair <point, point> thread_farthest = find_farthest_points(start, end);
        double thread_dist = find_distance(thread_farthest.first, thread_farthest.second);

        if(thread_dist > farthest_dist){
            farthest_dist = thread_dist;
            farthest_points = thread_farthest;
        }
    }

    // output coordinates of the farthest pair of points
    std::cout << "coordinates of the farthest pair of points: " << std::endl;
    std::cout << farthest_points.first.x << " " << farthest_points.first.y << " " << farthest_points.first.z << std::endl;
    std::cout << farthest_points.second.x << " " << farthest_points.second.y << " " << farthest_points.second.z << std::endl;
}