#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Shape {
protected:
    vector<string> v;  
    virtual void insert() = 0;
public:
    Shape() { v.clear(); }
    void del(int n) { v.erase(v.begin() + n); }
    void show() {
        for(int i = 0; i < v.size(); i++)
            cout << i << ": " << v[i] << endl;
    }
    void add(Shape *s) { s->insert(); }
};

class Line : public Shape {
public:
    virtual void insert() { v.push_back("Line"); }
};

class Circle : public Shape {
public:
    virtual void insert() { v.push_back("Circle"); }
};

class Rect : public Shape {
public:
    virtual void insert() { v.push_back("Rectangle"); }
};

class UI {
public:
    static int select() {
        int n;
        cout << "삽입:1, 삭제:2, 모두보기:3, 종료:4 >> ";
        cin >> n;
        return n;
    }
    static int insert() {
        int n;
        cout << "선:1, 원:2, 사각형:3 >> ";
        cin >> n;
        return n;
    }
    static int erase() {
        int n;
        cout << "삭제하고자 하는 도형의 인덱스 >> ";
        cin >> n;
        return n;
    }
};

class GraphicEditor {
    static Shape *s;
public:
    GraphicEditor() { s = NULL; }
    static void selInsert() {
        int shape_n = UI::insert();
        Shape *t;
        switch (shape_n) {
        case 1:
            t = new Line();
            break;
        case 2:
            t = new Circle();
            break;
        case 3:
            t = new Rect();
            break;
        default:
            break;
        }
        s->add(t);
    }

    static void selDelete() {
        int shape_i = UI::erase();
        s->del(shape_i);
    }

    static void start() { 
        cout << "그래픽 에디터입니다." << endl;
        while(1) {
            int n = UI::select();
            switch(n) {
            case 1:
                selInsert();
                break;
            case 2:
                selDelete();
                break;
            case 3:
                s->show();
                break;
            default:
                return;
            }
        }
     }
};

int main() {
    GraphicEditor* g = new GraphicEditor;
    g->start();
    delete g;
}
