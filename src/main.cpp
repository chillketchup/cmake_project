#include <iostream>
#include <cctype> // tolower
#include <glm/vec3.hpp> // vec3
#include <glm/mat4x4.hpp> // mat4
#include <glm/ext/matrix_transform.hpp> // translate, rotate, scale

using namespace std;
using namespace glm;

void print_matrix(mat4 matrix){
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // initiate matrix
    cout << "matrix transformation" << endl;
    mat4 matrix = mat4(1.0f);
    
    string command;
    
    while(true){
        // input
        cout << "commands: translate, rotate, scale, print, exit" << endl;
        
        cin >> command;
        
        for(int i = 0; i < command.length(); i++){
            command[i] = tolower(command[i]);
        }
        
        // process
        if(command == "exit"){
            break;
        }
        else if(command == "translate"){
            float x, y, z;
            
            cout << "enter x y z values to translate by, seperated by a single space: ";
            cin >> x >> y >> z;
            
            translate(matrix, vec3(x, y, z));
        }
        else if(command == "rotate"){
            float rot; char axis;
            
            cout << "enter degree to rotate by: ";
            cin >> rot;
            cout << "enter axis of rotation (x, y, or z): ";
            cin >> axis;
            
            axis = tolower(axis);
            
            if(axis == 'x') rotate(matrix, radians(rot), vec3(1.0f, 0.0f, 0.0f));
            else if(axis == 'y') rotate(matrix, radians(rot), vec3(0.0f, 1.0f, 0.0f));
            else if(axis == 'z') rotate(matrix, radians(rot), vec3(0.0f, 0.0f, 1.0f));
            else cout << "invalid axis" << endl;
        }
        else if(command == "scale"){
            float mult;
            
            cout << "enter scale multiplier: ";
            cin >> mult;
            
            matrix = scale(matrix, vec3(mult));
        }
        else if(command == "print"){
            print_matrix(matrix);
        }
        else{
            cout << "invalid command" << endl;
        }
    }
    
    return 0;
}
