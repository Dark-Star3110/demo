/*Nhập vào danh sách những người bạn của từng người trong file

===================
An: Hoa, Hong, Dung, Tien, Tung, Toan
Hong: Hoa, An, Dung, Tien
Dung: Tien, An, Hoa, Minh
Tien: An, Minh
Tung: Hung, Dung, An
Toan: Linh, An, Dung
Ly: Minh, Lam, Linh
Linh: Hoan, Hai
========================
Mỗi dòng là 1 người và những người bạn thân của người đó
Giả sử không có tên bị trùng

Với file trên, 
1.nhập vào tên 2 người, hỏi xem hai người đó có phải là bạn thân hay không
2.Nếu hai người là bạn thân, hãy liệt kê bạn chung của cả 2 người này 

*/
#include<iostream>
#include<fstream>
#include"jrbgraph.hpp"

int main(){
    Graph g= createGraph();
    fstream file;
    string file_name;
    cout << "Nhap ten file: ";
    cin >> file_name;
    file.open(file_name,ios::in);
    cout << "HelloWorld" ;
}

