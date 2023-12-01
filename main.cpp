#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
using namespace std;


const double pi = 3.14;

class Figure {
public:
    Figure(double hauteur) : hauteur(hauteur) {}


    virtual Figure * copy() const = 0;

    string toString() const {
        stringstream ss;
        ss << doToString();
        ss << "Hauteur:" << hauteur << endl;
        ss << "Volume:" << volume() << endl;
        ss << "surface = " << surface() << endl;
        ss << "perimetre = " << perimetre() << endl;
        return ss.str();
    }
    double volume() const { 
        return hauteur * surface();
    } 

    virtual double surface() const = 0;
    virtual double perimetre() const = 0;

protected:
    virtual string doToString() const = 0;

private:
    double hauteur;
};

ostream& operator<<(ostream& out, const Figure & f) {
    out << f.toString();
    return out;
}

class Rectangle : public Figure {
public:
    Rectangle(double hauteur, double longueur, double largeur)
    : Figure(hauteur), longueur(longueur), largeur(largeur)
    {
    }

    
    Figure * copy() const override {
        return new Rectangle(*this);
    }

    
    string doToString() const override {
        stringstream ss;
        ss << "Rectangle:" << endl;
        ss << "longueur = " << longueur << endl;
        ss << "largeur = " << largeur << endl;
        return ss.str();
    }

    double surface() const {
        return longueur * largeur;
    }
    
    double perimetre() const {
        return (longueur + largeur) * 2;
    }


    
private:
    double longueur;
    double largeur;
};



class Cercle : public Figure {
public:
    Cercle(double hauteur, double rayon)
    : Figure(hauteur), rayon(rayon)
    {
    }

    Figure * copy() const override {
        return new Cercle(*this);
    }
    
    string doToString() const override {
        stringstream ss;
        ss << "Cercle:" << endl;
        ss << "rayon = " << rayon << endl;
        return ss.str();
    }

    double surface() const {
        return pi * rayon * rayon;
    }
    
    double perimetre() const {
        return 2 * pi * rayon;
    }
    
private:
    double rayon;
};

class Canvas {
public:

    Canvas() = default;
    Canvas  (const Canvas & canvas) {
        for(auto f : canvas.figures) {
            figures.push_back(f->copy());
        }
    }

    Canvas& operator= (Canvas c) {
        swap(*this, c);
        return *this;
    }

    void add(const Figure & f) {
        figures.push_back(f.copy());
    }

    string toString() const {
        stringstream ss;
        for(auto f : figures) {
            ss << *f << endl;
        }
        return ss.str();
    }

    ~Canvas() {
        for(auto f : figures) {
            delete f;
        }
    }
private:
    vector<const Figure *> figures;

    friend void swap(Canvas & c1, Canvas & c2);

};

void swap(Canvas & c1, Canvas & c2) {
    using std::swap;
    swap(c1.figures, c2.figures);
}

ostream& operator<<(ostream& out, const Canvas & c) {
    out << c.toString();
    return out;
}

void ajouterCercle (Canvas & canvas) {
    Cercle c(100,10);
    canvas.add(c);
}

int main() {
    Canvas canvas;
    ajouterCercle(canvas);
    Rectangle r(10, 7, 3);
    canvas.add(r);

    Canvas canvasCopy;
    canvasCopy = canvas;

    Rectangle r2(100, 70, 30);
    canvas.add(r2);

    cout << "Canvas Copy:" << endl;
    cout << "==============" << endl;
    cout << canvasCopy << endl;

    cout << "Original Canvas:" << endl;
    cout << "==============" << endl;
    cout << canvas << endl;

    ofstream of("TestStdOut.txt");
    of << canvas << endl;
    of.close();

    return 0;
}


// 