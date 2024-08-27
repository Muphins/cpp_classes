#include <cmath>

#define PI 3.14159265359
#define RAD(a) (a*PI/180)
class cAngle{
private:
	float angle;
	
	float cap() {
	    while(angle > PI) angle -= 2*PI;
	    while(angle < -PI) angle += 2*PI;
	    return angle;
	}
public:
    //== Construstors
	cAngle(const float value) : angle(value) {
	    cap();
	}
	cAngle(): angle(0) {}
	//== Operators
	operator float() const {
	    return cAngle(angle).cap();
	}
	cAngle& operator= (const float& value) {
	    this->angle = value;
	    cap();
	    return *this; 
	}
	cAngle& operator+= (const float& value) {
	    this->angle += value;
	    cap();
	    return *this; 
	}
	cAngle& operator-= (const float& value) {
	    this->angle -= value;
	    cap();
	    return *this; 
	}
	//== Functions
	float deg() const {
	    return angle *180/PI;
	}
};

class cVector {
private:
    float x, y;

public:
    //== Constructors
    cVector(): x(0), y(0) {}
    cVector(float x_, float y_): x(x_), y(y_) {}
    cVector(cAngle angle, float mag){
        x = std::cos(angle)*mag;
        y = std::sin(angle)*mag;
    }
    //== Operators
    cVector& operator+=(const cVector& rhs){
        x+=rhs.x;
        y+=rhs.y;
        return *this;
    }
    cVector& operator-=(const cVector& rhs){
        x-=rhs.x;
        y-=rhs.y;
        return *this;
    }
    template <typename Scalar>
    cVector& operator*=(const Scalar scalar){
        x*=scalar;
        y*=scalar;
        return *this;
    }
    //== Functions
    cAngle angleto(cVector rhs){
        return rhs.angle()-this->angle();
    }
    cAngle angle(){
        return std::atan2(y,x);
    }
    float mag(){
        return std::sqrt(x*x + y*y);
    }
};
