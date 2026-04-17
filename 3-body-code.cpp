//newtons cannon?? maybe?
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <fstream>


using namespace std;

class vector2D
{
    
        double x, y;

        
    public:
        
        vector2D()
        {
            x = 0;
            y = 0;
        }

        vector2D(double x_, double y_)
        {
            x = x_;
            y = y_;
        }
    double get_x()
    {
        return x;
    }
    double get_y()
    {
        return y;
    }
    vector2D operator-(const vector2D &rhs)
    {
        return vector2D(this->x - rhs.x, this->y - rhs.y);
    }

    double operator*(const vector2D &rhs)
    {
        return (this->x*rhs.x + this->y*rhs.y);
    }

    vector2D operator*(double val)
    {
        return vector2D(this->x*val, this->y*val);
    }
    vector2D operator=(const vector2D &rhs)
    {
        return vector2D(x = rhs.x, y = rhs.y);
    }

    vector2D operator/(double val)
    {
        if(val==0){
        cout << "Not defined" << endl;
        return vector2D(this->x, this->y);
        }
        else{
        return vector2D(this->x/val, this->y/val);
        }
    }
    

    vector2D operator^(const vector2D &rhs)
    {
        return vector2D(this->x*rhs.y, this->y*rhs.x);
    }

    vector2D operator+(const vector2D &rhs)
    {
        return vector2D(x+rhs.x, y+rhs.y);
    }

    double distance(const vector2D &rhs)
    {
        return sqrt(pow(this->x - rhs.x, 2) + pow(this->y - rhs.y, 2));
    }

    double magnitude()
    {
        return sqrt(x*x + y*y);
    }

    vector2D normalise()
    {
        double mag = sqrt(x*x + y*y);
        return vector2D(this->x/mag, this->y/mag);
    }

    void print_vector()
    {
        cout << "X = " << x << ", Y = " << y <<endl;
    }

    friend ostream& operator<<(ostream &out, const vector2D &v);

    
};

ostream& operator<<(ostream &out, const vector2D &v)
    {
        out << "X = " << v.x << ", Y = " << v.y <<endl;

        return out;
    }

class particle
{
    double radius;
    double rho;
    vector2D V;
    vector2D Pos;
    
   

    public:
        particle(double r, double d, double u_x, double u_y, double x, double y)
        {
            radius = r;
            rho = d;
            V = vector2D(u_x, u_y);
            Pos = vector2D(x, y);
        }

    double volume()
    {
        return (4*3.14*(pow(radius,3))/3);
    }

    double mass()
    {
        return (rho*4*3.14*(pow(radius,3))/3);
    }
    
    void Physics(double dt, vector2D G) // the idea is as there are private variable we need to make physics run in the loop by calling a function
    {
        V = V + (G*dt);

        Pos = Pos + (V * dt);

    }
    
    void collision(particle &other_par)
    {
        vector2D n = vector2D(Pos.get_x()-other_par.Pos.get_x(), Pos.get_y()-other_par.Pos.get_y());
        double mag = n.magnitude();
        vector2D n_unit = n/mag;

        vector2D relative_V = vector2D(V.get_x() - other_par.V.get_x(), V.get_y() - other_par.V.get_y());
        if((relative_V * n) >= 0) 
        {
            return; 
        }

        vector2D t_unit = vector2D(n_unit.get_y(), -n_unit.get_x());
        //now i gotta split the velocites into normal and tangential
        double n1 = n_unit*V;
        double n2 = n_unit*other_par.V;

        double t1 = t_unit*V;
        double t2 = t_unit*other_par.V;

        double m1 = mass();
        double m2 = other_par.mass();

        double v1 = ((m1 - m2) * n1 + 2 * m2 * n2) / (m1 + m2);
        double v2 = ((m2 - m1) * n2 + 2 * m1 * n1) / (m1 + m2);

        V = (n_unit*v1) + (t_unit*t1);
        other_par.V = (n_unit*v2) + (t_unit*t2);
    }

    //the idea is making the particle be attracted towards the planet... and i think the best way would be to make the planet and the projectiles both particle class. we just have to make the planet extramly dense and large
    //then we just have to use the universal law of gravitation -> force -> acceleration -> velocity (change) -> position ! lets hope this works
    void Gravity(particle &other_par,double dt)
    {
        vector2D a;
        double G = 1;
        double dx = GetXpos() - other_par.GetXpos();
        double dy = GetYpos() - other_par.GetYpos();
        double r_mag = sqrt((dx * dx) + (dy * dy));
        if(r_mag < 1.0) { r_mag = 1.0; }
        
        vector2D r = Pos - other_par.Pos;
        double m1 = mass();
        double m2 = other_par.mass();
        vector2D F = r*(G*(m1*m2)/(pow(r_mag, 3)));

        vector2D a1 = (F*(-1))/m1; 
        vector2D a2 = (F/m2)*(1);
        
        V = V + a1*dt;
        other_par.V = other_par.V + a2*dt;

        
        
    }

    void move(double dt)
    {
        Pos = Pos + (V*dt);
    }
    void Bottom_Bounce( double B)
    {
        V = vector2D(V.get_x(), V.get_y()*B);
    }
    void Top_bounce(double B)
    {
        V = vector2D(V.get_x(), V.get_y()*B);
    }
    void LHS_bounce(double D)
    {
        V = vector2D(V.get_x()*D, V.get_y()); //i gave the left and roght side perfectly elastic collision collision (well you could change the value anytime u want!!)
    }
    
    void RHS_bounce(double D)
    {
        V = vector2D(V.get_x()*D, V.get_y());
    }

    void fix_pos_bot()
    {
        Pos = vector2D(Pos.get_x(), 3.00001);
    }
    void fix_pos_top()
    {
        Pos = vector2D(Pos.get_x(), 96.9999);
    }

    void fix_pos_RHS()
    {
        Pos = vector2D(96.9999, Pos.get_y()); //to make the ball not go out of the box i use fix position 
    }

    void fix_pos_LHS()
    {
        Pos = vector2D(3.00001, Pos.get_y());
    }

    double Energy(vector2D G,  vector2D make_y) //I just need to calculate the energy per mass...so not gonna use the mass term!
    {
        return (0.5*(V*make_y)*(V*make_y))-(G*Pos); // i put thr negative sign next to potential energy because G is negative 
    }

    double Velo_mag()
    {
        return  V.magnitude();
    }

    double GetXpos()
    {
        return Pos.get_x();
    }
    double GetYpos()
    {
        return Pos.get_y();
    }
    double GetRad()
    {
        return radius;
    }

    friend ostream& operator<<(ostream &out, const particle &P);

};

ostream& operator<<(ostream &out, const particle &P)
    {
        out << "Radius = " << P.radius << ", Density = " << P.rho << "\n" <<"Position " << P.Pos  << "Velocity componets " << P.V  ; //i removed the endl at the end because i caused output to have to line spaced at the end (sortof like having (\n twice))..nothing major!!
        //also explaining the code here P.Pos and P.v are vector so the << overloading we did earlier will be enough for them    
        return out;
    }


int main()
{
    double dt = 0.01;
    double t = 0;

    particle p1(1, 50, 200, 70,-1500 , -1300); 
    particle p2(100, 2, 20, 50, -1500, -1500);
    particle p3(1,50, 170,50, -1500, -1750);

    ofstream outfile("gravity.txt");
    outfile << "planet radius = " << p2.GetRad()<< endl; 
    outfile << "Time, p1_X, p1_Y, p2_X, p2_Y, p3_X, p3_Y " << endl;
    while(t <= 200)
    {

        p1.Gravity(p2, dt);
        p1.Gravity(p3, dt);
        p2.Gravity(p3, dt);
        

        
        double dx1 = p1.GetXpos() - p2.GetXpos();
        double dy1 = p1.GetYpos() - p2.GetYpos();
        double dist1 = sqrt((dx1 * dx1) + (dy1 * dy1));

        double dx2 = p1.GetXpos() - p3.GetXpos();
        double dy2 = p1.GetYpos() - p3.GetYpos();
        double dist2 = sqrt((dx2 * dx2) + (dy2 * dy2));

        double dx3 = p2.GetXpos() - p3.GetXpos();
        double dy3 = p2.GetYpos() - p3.GetYpos();
        double dist3 = sqrt((dx3 * dx3) + (dy3 * dy3));

        if(dist1 < (0.1+p1.GetRad()+p2.GetRad()))
        {
            p1.collision(p2);
        }

        if(dist2 < (0.1+p1.GetRad()+p3.GetRad()))
        {
            p1.collision(p3);
        }

        if(dist3 < (0.1+p2.GetRad()+p3.GetRad()))
        {
            p2.collision(p3);
        }
        
        p1.move(dt);
        p2.move(dt);
        p3.move(dt);

        outfile << t << ", " << p1.GetXpos() << ", " << p1.GetYpos() << ", " << p2.GetXpos() << ", " << p2.GetYpos() << ", "<< p3.GetXpos()<<", " << p3.GetYpos() << endl;
        t = t + dt;

    }
    outfile.close();
    cout << "output in gravity.txt!!" << endl;
}