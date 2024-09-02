
#define PI 3.14159265359
#define RAD(a) ((a)*PI/180)

class cAngle{
private:
	double angle;
	
	double cap() {
	    while(angle > PI) angle -= 2*PI;
	    while(angle < -PI) angle += 2*PI;
	    return angle;
	}
public:
    //== Construstors
	cAngle(double value) : angle(value) {
	    cap();
	}
	cAngle(): angle(0) {}
	//== Operators
	operator double() const {
	    return cAngle(angle).cap();
	}
	cAngle& operator= (const double& value) {
	    this->angle = value;
	    cap();
	    return *this; 
	}
	cAngle& operator+= (const double& value) {
	    this->angle += value;
	    cap();
	    return *this; 
	}
	cAngle& operator-= (const double& value) {
	    this->angle -= value;
	    cap();
	    return *this; 
	}
	//== Functions
	double deg() const {
	    return angle *180/PI;
	}
};

class cVector {
private:
    double _x, _y;
    cAngle _angle;
    void compute_angle(){
        _angle = std::atan2(_y,_x);
    }
public:
    //== Constructors
    cVector(): _x(0), _y(0), _angle(0) {}
    cVector(double x_, double y_): _x(x_), _y(y_) {
        compute_angle();
    }
    cVector(const cVector lhs, const cVector rhs) {
        _x = rhs._x - lhs._x;
        _y = rhs._y - lhs._y;
        compute_angle();
    }
    cVector(cAngle angle, double mag){
        _x = std::cos(angle)*mag;
        _y = std::sin(angle)*mag;
        _angle = angle;
    }
    //== Operators
    cVector& operator+=(const cVector& rhs){
        _x+=rhs._x;
        _y+=rhs._y;
        compute_angle();
        return *this;
    }
    cVector& operator+=(const cAngle& rhs){
        //*this=cVector(this->angle()+rhs, this->mag());
        cVector vect((cAngle)(this->angle()+rhs), this->mag());
        *this = vect;
        return *this;
    }
    cVector operator+(const cVector& rhs){
        cVector res(_x+rhs._x, _y+rhs._y);
        return res;
    }
    cVector& operator-=(const cVector& rhs){
        _x-=rhs._x;
        _y-=rhs._y;
        compute_angle();
        return *this;
    }
    cVector& operator-=(const cAngle& rhs){
        *this=cVector((cAngle)(this->angle()-rhs), this->mag());
        return *this;
    }
    cVector operator-(const cVector& rhs){
        cVector res(_x-rhs._x, _y-rhs._y);
        return res;
    }
    template <typename Scalar>
    cVector& operator*=(const Scalar scalar){
        _x*=scalar;
        _y*=scalar;
        return *this;
    }
    cVector& operator=(const double mag){
        *this=cVector(angle(), mag);
        return *this;
    }
    //== Functions
    double x() const { return _x;}
    double y() const { return _y;}
    cAngle angle() const {
        return _angle; //std::atan2(_y,_x);
    }
    const double mag(){
        return std::sqrt(_x*_x + _y*_y);
    }
    inline const double mag2(){
        return (_x*_x + _y*_y);
    }
    inline const double dot(const cVector& rhs){
        return _x*rhs._x + _y*rhs._y;
    }
    void set_x(double x){
        _x = x;
        compute_angle();
    }
    void set_y(double y){
        _y = y;
        compute_angle();
    }
    void set_angle(cAngle angle){
        *this = cVector(angle, mag());
    }
    void set_mag(double mag){
        *this = cVector(angle(), mag);
        if(mag < 0) _angle += PI;
    }
    const cAngle angle_to(cVector rhs){
        return rhs.angle()-this->angle();
    }
    const cVector proj_to(cVector rhs){
        double factor= dot(rhs)/rhs.mag2();
        return cVector(rhs._x*factor, rhs._y*factor);
    }
};

template <typename Scalar>
cVector operator*(const cVector& vect, const Scalar& scalar){
    return cVector(vect.x()*scalar, vect.y()*scalar);
}
template <typename Scalar>
cVector operator*(const Scalar& scalar, cVector& vect){
    return cVector(vect.x()*scalar, vect.y()*scalar);
    //return cVector(vect._x*scalar, vect._y*scalar);
}
