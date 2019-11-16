class Vect
{
public:
	float x, y;

	Vect()
	{
		this->x = 0;
		this->y = 0;
	}

	Vect(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float abs()
	{
		return sqrt(pow(this->x, 2) + pow(this->y, 2));
	}

	Vect operator+(Vect v)
	{
		float x = this->x + v.x;
		float y = this->y + v.y;
		return Vect(x,y);
	}

	Vect operator+=(Vect v)
	{
		this->x += v.x;
		this->y += v.y;
	}

	Vect operator-(Vect &v)
	{
		float x = this->x - v.x;
		float y = this->y - v.y;
		return Vect(x,y);
	}

	float operator*(Vect &v)
	{
		return this->x*v.x + this->y*v.y;
	}

	Vect operator*(float number)
	{
		float x = this->x * number;
		float y = this->y * number;
		return Vect(x,y);
	}

	float operator*=(float number)
	{
		this->x *= number;
		this->y *= number;
	}
};

